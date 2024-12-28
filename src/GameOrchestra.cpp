#include "GameOrchestra.hpp"

#include "Common.hpp"

#include <allegro5/allegro_primitives.h>

#include <string>
#include <cmath>
#include <iostream>

GameOrchestra::GameOrchestra()
    : ball(Vector2f{WINDOW_WIDTH * 0.5, 750}, Vector2f{0, -1}, BALL_SPEED),
      plate(nullptr, Vector2f{(WINDOW_WIDTH - PLATE_WIDTH) * 0.5, 800}, Vector2f{0, 0}, PLATE_SPEED) {

    init_bricks();

    // Preloading all the assets to save memory
    background_bitmap = al_load_bitmap("../res/sprites/background.png");
    brick_bitmap      = al_load_bitmap("../res/sprites/brick.png");
    plate_bitmap      = al_load_bitmap("../res/sprites/plate_small.png");
    ball_bitmap       = al_load_bitmap("../res/sprites/ball.png");

    plate.set_bitmap(plate_bitmap);

    main_font = al_load_font("../res/fonts/press_start_2p.ttf", MAIN_FONT_SIZE, 0);
}

void GameOrchestra::init_bricks() {
    for (int i = BRICK_ROWS; i > 0; i--) {
        for (int j = 0; j < BRICK_COLUMNS; j++) {
            Vector2f position{};
            position.x = BRICK_WIDTH  * static_cast<float>(j)              + BORDERS_SIZE;
            position.y = BRICK_HEIGHT * static_cast<float>(BRICK_ROWS - i) + BRICKS_Y_PADDING;
            Brick brick{position, {0, 0}, 0, Brick::get_brick_type_from_index(i - 1)};
            bricks.push_back(brick);
        }
    }
}

void GameOrchestra::update() {
    ball.move();

    check_ball_collisions();

    if (!plate.check_collision_walls() && !mouse_control_mode) {
        plate.move();
    }

    if (!plate.get_moving_left() && !plate.get_moving_right()) {
        plate.set_direction(Vector2f{0, 0});
    }
}

void GameOrchestra::input(const ALLEGRO_MOUSE_STATE &current_mouse_state, const ALLEGRO_MOUSE_STATE &previous_mouse_state, const ALLEGRO_EVENT_TYPE event, const int keycode) {
    if (al_mouse_button_down(&current_mouse_state, 1) && !mouse_control_mode) { // Enter mouse plate control with left click
        mouse_control_mode = true;
    }
    else if (al_mouse_button_down(&current_mouse_state, 2) && mouse_control_mode) { // Leave mouse plate control with right click (back to keyboard inputs)
        mouse_control_mode = false;
    }

    // If the user is in mouse plate control mode, set the plate X position to the mouse's
    if (mouse_control_mode) {
        plate.set_position(Vector2f{static_cast<float>(current_mouse_state.x - PLATE_WIDTH * 0.5), plate.get_position().y});
    }

    if (!mouse_control_mode) {
        if (event == ALLEGRO_EVENT_KEY_DOWN) {
            key_down(keycode);
        } else if (event == ALLEGRO_EVENT_KEY_UP) {
            key_up(keycode);
        }
    }
}

void GameOrchestra::render() const {
    al_clear_to_color(al_map_rgb(255, 255, 255));

    // Drawing the background image
    al_draw_bitmap(background_bitmap, 0, 0, ALLEGRO_FLIP_HORIZONTAL & ALLEGRO_FLIP_VERTICAL);

    // Drawing the plate and the ball
    plate.draw(plate_bitmap);
    al_draw_bitmap(ball_bitmap, ball.get_position().x - BALL_RADIUS, ball.get_position().y - BALL_RADIUS, 0);

    for (auto &brick: bricks) {
        al_draw_tinted_bitmap(brick_bitmap, brick.get_brick_type_data().color, brick.get_position().x, brick.get_position().y, 0);

        //al_draw_rectangle(brick.get_position().x, brick.get_position().y, brick.get_position().x + BRICK_WIDTH,
        //                  brick.get_position().y + BRICK_HEIGHT, al_map_rgb(0, 255, 0), 2);
    }

    // Drawing the player score
    constexpr float padding_x = WINDOW_WIDTH * 0.5f;
    constexpr float padding_y = BRICKS_Y_PADDING * 0.5;

    const auto  score_text_string  = "SCORE ";
    const char *score_value_string = std::to_string(score).c_str();

    // Calculating the total width of the two strings combined
    const int score_text_width  = al_get_text_width(main_font, score_text_string);
    const int score_value_width = al_get_text_width(main_font, score_value_string);
    const int score_total_width = score_text_width + score_value_width;

    // Calculating the resulting padding of the score text for the X axis
    const float final_padding_x = padding_x - static_cast<float>(score_total_width * 0.5);

    // Drawing the score label and value
    al_draw_text(main_font, al_map_rgb(255, 255, 255), final_padding_x, padding_y, ALLEGRO_ALIGN_LEFT, score_text_string);
    al_draw_text(main_font, al_map_rgb(255, 0, 0), final_padding_x + static_cast<float>(score_text_width), padding_y,
                 ALLEGRO_ALIGN_LEFT, score_value_string);

    //al_draw_rectangle(plate.get_position().x, plate.get_position().y, plate.get_position().x + PLATE_WIDTH,
    //                  plate.get_position().y + PLATE_HEIGHT, al_map_rgb(0, 255, 0), 2);

    al_flip_display();
}

void GameOrchestra::check_ball_collisions() {
    // Checking for collisions with the bricks
    for (long unsigned int i = 0; i < bricks.size(); i++) {
        // On collision
        Vector2f brick_collision_normal{};
        const bool intersect_brick = intersect_circle_AABB(ball.get_position(), BALL_RADIUS, bricks[i].get_position(),
                                                           BRICK_WIDTH, BRICK_HEIGHT, brick_collision_normal);
        if (intersect_brick) {
            // Removing the brick from the vector
            bricks.erase(bricks.begin() + static_cast<long>(i));
            // Calculating the ball's bounce direction after hitting the bricks (reflection formula)
            const Vector2f direction = Ball::get_bounce_direction(ball.get_direction(), brick_collision_normal);
            ball.set_direction(direction);
            // Updating the player score
            score += bricks[i].get_brick_type_data().points_bonus;
        }
    }

    // Checking for collisions with the plate
    Vector2f plate_collision_normal{};
    const bool intersect_plate = intersect_circle_AABB(ball.get_position(), BALL_RADIUS, plate.get_position(),
                                                       PLATE_WIDTH, PLATE_HEIGHT, plate_collision_normal);
    if (intersect_plate) {
        // Calculating the ball's bounce direction after hitting the plate
        const float alpha_radians = (360 - (30 + 120 * (1 - (ball.get_position().x - plate.get_position().x) / PLATE_WIDTH))) * static_cast<float>(M_PI / 180.0f);
        ball.set_direction(Vector2f{std::cos(alpha_radians), std::sin(alpha_radians)});
    }

    // Checking for collisions with the walls
    const Vector2f ball_position  = ball.get_position();
    const Vector2f ball_direction = ball.get_direction();

    if (ball_position.x - BALL_RADIUS <= BORDERS_SIZE) {
        ball.set_direction(Ball::get_bounce_direction(ball_direction, {1, 0}));
    } else if (ball_position.x + BALL_RADIUS >= WINDOW_WIDTH - BORDERS_SIZE) {
        ball.set_direction(Ball::get_bounce_direction(ball_direction, {-1, 0}));
    } else if (ball_position.y - BALL_RADIUS <= BORDERS_SIZE) {
        ball.set_direction(Ball::get_bounce_direction(ball_direction, {0, 1}));
    } else if (ball_position.y + BALL_RADIUS >= WINDOW_HEIGHT) {
        ball.set_direction(Ball::get_bounce_direction(ball_direction, {0, -1}));
    }
}

// Key codes are documented here: https://www.allegro.cc/manual/5/keyboard.html
void GameOrchestra::key_down(const int keycode) {
    // Called when a key is pressed
    switch (keycode) {
        case ALLEGRO_KEY_1:
            /* Code for key 1 pressed */
            break;
        case ALLEGRO_KEY_SPACE:
            /* Code for space pressed */
            break;
        case ALLEGRO_KEY_A: case ALLEGRO_KEY_Q: // Left key
            plate.set_direction(Vector2f{-1, 0});
            plate.set_moving_left(true);
            break;
        case ALLEGRO_KEY_P: case ALLEGRO_KEY_D: // Right key
            plate.set_direction(Vector2f{1, 0});
            plate.set_moving_right(true);
            break;
        default:
            break;
    }
}

void GameOrchestra::key_up(const int keycode) {
    // Called when a key is released
    switch (keycode) {
        case ALLEGRO_KEY_1:
            /* Code for key 1 pressed */
            break;
        case ALLEGRO_KEY_SPACE:
            /* Code for space pressed */
            break;
        case ALLEGRO_KEY_A: case ALLEGRO_KEY_Q: // Left key
            plate.set_moving_left(false);
            break;
        case ALLEGRO_KEY_P: case ALLEGRO_KEY_D: // Right key
            plate.set_moving_right(false);
            break;
        default:
            break;
    }
}
