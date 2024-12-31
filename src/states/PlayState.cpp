/*
 * INFO-F202 (2024 - 2025)
 * Written with ❤︎ by Yassir Laghmouchi & Nabil El Muhur @ ULB
 */

#include "PlayState.hpp"

#include "GameStateManager.hpp"
#include "GameOverState.hpp"

#include <allegro5/allegro_primitives.h>

#include <algorithm>
#include <iostream>
#include <fstream>
#include <cmath>

PlayState::PlayState(GameStateManager *_game_state_manager, const SpriteManager &_sprite_manager)
    : GameState(_game_state_manager, _sprite_manager),
      ball(sprite_manager.ball_bitmap        , Vector2f{}, Vector2f{}, BALL_SPEED),
      plate(sprite_manager.plate_small_bitmap, Vector2f{}, Vector2f{}, PLATE_SPEED) {
    // Setting up the plate and ball
    setup_plate_and_ball();

    // Initialising the bricks vector
    init_bricks();

    // Reading the high score from the player data file
    high_score = read_high_score();
}

void PlayState::setup_plate_and_ball() {
    // Setting the plate's size to match its sprite
    plate.set_size(Vector2f{
        static_cast<float>(al_get_bitmap_width(plate.get_bitmap())),
        static_cast<float>(al_get_bitmap_height(plate.get_bitmap()))
    });

    // Setting the plate's initial position
    plate.set_position(Vector2f{(WINDOW_WIDTH - plate.get_size().x) / 2, 750});

    // Setting the ball's initial position and direction
    ball.set_position(Vector2f{static_cast<float>((WINDOW_WIDTH - ball.get_size().x) * 0.5), plate.get_position().y - ball.get_size().y});
    ball.set_direction(Vector2f{0, -1});
}

void PlayState::init_bricks() {
    // Iterating rows and columns to define bricks and push them into the vector
    for (int i = BRICK_ROWS; i > 0; i--) {
        for (int j = 0; j < BRICK_COLUMNS; j++) {
            Vector2f position{};
            position.x = BRICK_WIDTH  * static_cast<float>(j)              + BORDERS_SIZE;
            position.y = BRICK_HEIGHT * static_cast<float>(BRICK_ROWS - i) + BRICKS_Y_PADDING;

            Brick brick{sprite_manager, position, Brick::get_brick_type_from_index(8)};
            bricks.push_back(std::make_shared<Brick>(brick));
        }
    }
}

void PlayState::update() {
    // If the game hasn't started yet (if the player hasn't moved the plate), don't update game objects
    if (!game_started) {
        return;
    }

    // Moving the ball and plate and checking for collisions respectively
    check_ball_collisions();
    ball.move();

    if (!plate.check_collision_walls() && !mouse_control_mode) {
        plate.move();
    }

    // Resetting the plate's direction if the inputs are neutral
    if (!plate.get_moving_left() && !plate.get_moving_right()) {
        plate.set_direction(Vector2f{0, 0});
    }

    // If the ball goes below the plate height
    if (ball.get_position().y > plate.get_position().y + plate.get_size().y) {
        lives_remaining--;

        if (lives_remaining <= 0) {
            // Game over, defeat (no lives remaining)
            write_high_score(false);
            game_state_manager->update_state(std::make_unique<GameOverState>(game_state_manager, sprite_manager, false, score));
        }
        else {
            // Lost one life, resetting the plate and ball
            setup_plate_and_ball();
            game_started = false;
        }
    }

    // If all the bricks have been destroyed
    if (bricks.empty()) {
        // Game over, victory
        write_high_score(false);
        game_state_manager->update_state(std::make_unique<GameOverState>(game_state_manager, sprite_manager, true, score));
    }

    // Updating the high score if the current score is greater
    if (score > high_score) {
        high_score = score;
    }
}

void PlayState::input(const ALLEGRO_MOUSE_STATE &mouse_state, const ALLEGRO_EVENT_TYPE event, const int keycode) {
    if (al_mouse_button_down(&mouse_state, 1) && !mouse_control_mode) {
        // Enter mouse plate control with left click
        mouse_control_mode = true;
    }
    else if (al_mouse_button_down(&mouse_state, 2) && mouse_control_mode) {
        // Leave mouse plate control with right click (back to keyboard inputs)
        mouse_control_mode = false;
    }

    // If the user is in mouse plate control mode, set the plate X position to the mouse's
    if (mouse_control_mode) {
        plate.set_position(Vector2f{
            static_cast<float>(mouse_state.x - plate.get_size().x * 0.5), plate.get_position().y
        });
    }

    // Handling keyboard inputs if not in mouse control mode
    if (!mouse_control_mode) {
        if (event == ALLEGRO_EVENT_KEY_DOWN) {
            key_down(keycode);
        }
        else if (event == ALLEGRO_EVENT_KEY_UP) {
            key_up(keycode);
        }
    }
}

void PlayState::draw_health_bar() const {
    ALLEGRO_BITMAP *health_bar_bitmap = nullptr;

    // Switching the health bar sprite depending on the remaining lives
    switch (lives_remaining) {
        case 3: health_bar_bitmap = sprite_manager.health_bar_full; break;
        case 2: health_bar_bitmap = sprite_manager.health_bar_two_left; break;
        case 1: health_bar_bitmap = sprite_manager.health_bar_one_left; break;
        default: break;
    }
    // Drawing the health bar if it's properly defined
    if (health_bar_bitmap != nullptr) {
        al_draw_bitmap(health_bar_bitmap, 0, static_cast<float>(WINDOW_HEIGHT - al_get_bitmap_height(health_bar_bitmap)), 0);
    }
}

void PlayState::render(const FontManager &font_manager) const {
    // Drawing the background image
    al_draw_bitmap(sprite_manager.background_bitmap, 0, 0, ALLEGRO_FLIP_HORIZONTAL & ALLEGRO_FLIP_VERTICAL);

    // Drawing the plate and the ball
    plate.draw();
    ball.draw();

    // Drawing the bricks
    for (auto &brick: bricks) {
        brick->draw();

        // If the brick is silver, if it needs 1 hit to be destroyed and if it doesn't have the appropriate sprite yet, set it to the appropriate sprite
        if (brick->get_brick_type() == BRICK_TYPE::SILVER && brick->get_hits_needed() == 1 && brick->get_bitmap() != sprite_manager.brick_silver_low_bitmap) {
            brick->set_bitmap(sprite_manager.brick_silver_low_bitmap);
        }
    }

    // Drawing the health bar
    draw_health_bar();

    // Drawing the current score
    draw_score(font_manager, score, Vector2f{BORDERS_SIZE * 4, BORDERS_SIZE + MAIN_FONT_SIZE_SMALL}, "SCORE", false);

    // Drawing the high score
    draw_score(font_manager, high_score, Vector2f{WINDOW_WIDTH - BORDERS_SIZE * 4, BORDERS_SIZE + MAIN_FONT_SIZE_SMALL}, "HIGHSCORE", false);
}

void PlayState::check_ball_collisions() {
    // Checking for collisions with the bricks
    std::shared_ptr<Brick> intersected_brick = nullptr;
    Vector2f brick_intersection_normal{};

    // Finding the first intersected brick
    for (const auto & brick : bricks) {
        const bool intersect_brick = intersect_AABB_AABB(ball.get_position(), ball.get_size(), brick->get_position(),
                                              brick->get_size(), brick_intersection_normal);
        // Found an intersection
        if (intersect_brick) {
            intersected_brick = brick;
            break;
        }
    }

    // If a brick was intersected
    if (intersected_brick != nullptr) {
        // Removing the brick if the hits needed to destroy it are equal to 1
        if (intersected_brick->get_hits_needed() == 1) {
            // Removing the brick from the vector by fetching its index
            const long brick_index = std::distance(bricks.begin(), std::find(bricks.begin(), bricks.end(), intersected_brick));
            bricks.erase(bricks.begin() + brick_index);

            // Updating the player score
            score += intersected_brick->get_brick_type_data().points_bonus;
        }
        // If the hits needed to remove the brick are over 1
        else if (intersected_brick->get_hits_needed() > 1) {
            // Decrementing the hits needed to destroy the brick
            intersected_brick->set_hits_needed(intersected_brick->get_hits_needed() - 1);
        }

        // Resolving the ball's position after intersecting to prevent clipping inside the bricks
        ball.set_position(Vector2f{
            ball.get_position().x - ball.get_speed() * ball.get_direction().x,
            ball.get_position().y - ball.get_speed() * ball.get_direction().y
        });

        // Calculating the ball's bounce direction after hitting the bricks (reflection formula)
        const Vector2f direction = Ball::get_bounce_direction(ball.get_direction(), brick_intersection_normal);
        ball.set_direction(direction);
    }

    // Checking for collisions with the plate
    Vector2f   plate_collision_normal{};
    const bool intersect_plate = intersect_AABB_AABB(ball.get_position(), ball.get_size(), plate.get_position(),
                                                     plate.get_size(), plate_collision_normal);
    if (intersect_plate) {
        // Calculating the ball's bounce direction after hitting the plate
        const float alpha_radians = (360 - (30 + 120 * (1 - (ball.get_position().x - plate.get_position().x) / PLATE_WIDTH))) * static_cast<float>(M_PI / 180.0f);
        ball.set_direction(Vector2f{std::cos(alpha_radians), std::sin(alpha_radians)});
    }

    // Checking for collisions with the walls
    const Vector2f ball_position  = ball.get_position();
    const Vector2f ball_direction = ball.get_direction();
    const Vector2f ball_size      = ball.get_size();

    // Left side
    if (ball_position.x <= BORDERS_SIZE) {
        ball.set_direction(Ball::get_bounce_direction(ball_direction, {1, 0}));
    }
    // Right side
    else if (ball_position.x + ball_size.x >= WINDOW_WIDTH - BORDERS_SIZE) {
        ball.set_direction(Ball::get_bounce_direction(ball_direction, {-1, 0}));
    }
    // Top side
    else if (ball_position.y <= BORDERS_SIZE) { // Top side
        ball.set_direction(Ball::get_bounce_direction(ball_direction, {0, 1}));
    }
}

// Key codes are documented here: https://www.allegro.cc/manual/5/keyboard.html
void PlayState::key_down(const int keycode) {
    // Starting the game on the first plate movement
    if (keycode == ALLEGRO_KEY_A || keycode == ALLEGRO_KEY_Q ||
        keycode == ALLEGRO_KEY_P || keycode == ALLEGRO_KEY_D) {
        if (!game_started) {
            game_started = true;
        }
    }

    // Called when a key is pressed
    switch (keycode) {
        // F1 key (reset high score)
        case ALLEGRO_KEY_F1:
            high_score = 0;
            write_high_score(true);
            break;
        // Left key (move plate to the left)
        case ALLEGRO_KEY_A:
        case ALLEGRO_KEY_Q:
            plate.set_direction(Vector2f{-1, 0});
            plate.set_moving_left(true);
            break;
        // Right key (move plate to the right)
        case ALLEGRO_KEY_P:
        case ALLEGRO_KEY_D:
            plate.set_direction(Vector2f{1, 0});
            plate.set_moving_right(true);
            break;
        default:
            break;
    }
}

void PlayState::key_up(const int keycode) {
    // Called when a key is released
    switch (keycode) {
        // Left key (move plate to the left)
        case ALLEGRO_KEY_A:
        case ALLEGRO_KEY_Q:
            plate.set_moving_left(false);
            break;
        // Right key (move plate to the right)
        case ALLEGRO_KEY_P:
        case ALLEGRO_KEY_D:
            plate.set_moving_right(false);
            break;
        default:
            break;
    }
}

int PlayState::read_high_score() {
    int high_score = 0;

    // Opening the input file stream
    std::ifstream input_high_score(HIGH_SCORE_PATH);

    // Checking if the high score file is open
    if (!input_high_score) {
        std::cerr << "Error: Could not open the high score data file" << std::endl;
        exit(1);
    }

    // Reading the first line of the file
    std::string high_score_string;
    if (std::getline(input_high_score, high_score_string)) {
        high_score = std::stoi(high_score_string);
    }

    // Closing the input file stream
    input_high_score.close();
    return high_score;
}

void PlayState::write_high_score(const bool force) const {
    // Writing the high score to the file only if the current score is greater or equal and if the writing isn't forced
    if (score < high_score && !force) return;

    // Opening the output file stream
    std::ofstream output_high_score(HIGH_SCORE_PATH);

    // Checking if the high score file is open
    if (!output_high_score) {
        std::cerr << "Error: Could not open the high score data file" << std::endl;
        exit(1);
    }

    // Writing the new high score to the file
    output_high_score << score;

    // Closing the input file stream
    output_high_score.close();
}
