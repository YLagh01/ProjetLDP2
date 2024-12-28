#include "GameOrchestra.hpp"

#include "Common.hpp"

#include <allegro5/allegro_primitives.h>

#include <string>
#include <cmath>
#include <iostream>

bool plate_moving_left  = false;
bool plate_moving_right = false;

GameOrchestra::GameOrchestra()
    : ball(Vector2f{WINDOW_WIDTH * 0.5, 750}, Vector2f{0, -1}, BALL_SPEED),
      plate(al_load_bitmap("../res/plate.png"), Vector2f{(WINDOW_WIDTH - PLATE_WIDTH) * 0.5, 800}, Vector2f{0, 0}, PLATE_SPEED) {
    init_bricks();
}

void GameOrchestra::init_bricks() {
    for (int i = 0; i < BRICK_ROWS; i++) {
        for (int j = 0; j < BRICK_COLUMNS; j++) {
            Vector2f position{};
            position.x = static_cast<float>(BRICK_WIDTH * j);
            position.y = static_cast<float>(BRICK_HEIGHT * i + BRICKS_Y_PADDING);
            Brick brick{al_map_rgb(255, 0, 0), position, {0, 0}, 0, 100};
            bricks.push_back(brick);
        }
    }
}

void GameOrchestra::update() {
    check_ball_collisions();

    ball.move();

    if (!plate.check_collision_walls()) {
        plate.move();
    }

    if (!plate_moving_left && !plate_moving_right) {
        plate.set_direction(Vector2f{0, 0});
    }
}

void GameOrchestra::input(const ALLEGRO_EVENT_TYPE event, const int keycode) {
    // See key handling functions further down the file
    if (event == ALLEGRO_EVENT_KEY_DOWN) {
        key_down(keycode);
    } else if (event == ALLEGRO_EVENT_KEY_UP) {
        key_up(keycode);
    }
}

void GameOrchestra::render() const {
    al_clear_to_color(al_map_rgb(255, 255, 255));

    // Drawing the background image
    //al_draw_bitmap(al_load_bitmap("../res/origbig.png"), 0, 0, ALLEGRO_FLIP_HORIZONTAL & ALLEGRO_FLIP_VERTICAL);

    plate.draw(plate.get_bitmap());
    ball.draw();

    for (auto &brick: bricks) {
        brick.draw();
    }

    for (const auto &brick: bricks) {
        al_draw_rectangle(brick.get_position().x, brick.get_position().y, brick.get_position().x + BRICK_WIDTH,
                          brick.get_position().y + BRICK_HEIGHT, al_map_rgb(0, 255, 0), 2);
    }

    // Drawing the player score
    static constexpr int score_font_size = 16;

    // Loading the TTF font
    const ALLEGRO_FONT *score_font = al_load_font("../res/fonts/press_start_2p.ttf", score_font_size, 0);
    constexpr float padding_x = WINDOW_WIDTH * 0.5f;
    constexpr float padding_y = 10.0f;

    const auto score_text_string = "Score ";
    const char *score_value_string = std::to_string(score).c_str();

    // Calculating the total width of the two strings combined
    const int score_text_width = al_get_text_width(score_font, score_text_string);
    const int score_value_width = al_get_text_width(score_font, score_value_string);
    const int score_total_width = score_text_width + score_value_width;

    // Calculating the resulting padding of the score text for the X axis
    const float final_padding_x = padding_x - static_cast<float>(score_total_width * 0.5);

    // Drawing the score label and value
    al_draw_text(score_font, al_map_rgb(0, 0, 0), final_padding_x, padding_y, ALLEGRO_ALIGN_LEFT, score_text_string);
    al_draw_text(score_font, al_map_rgb(255, 0, 0), final_padding_x + static_cast<float>(score_text_width), padding_y,
                 ALLEGRO_ALIGN_LEFT, score_value_string);

    al_draw_rectangle(plate.get_position().x, plate.get_position().y, plate.get_position().x + PLATE_WIDTH,
                      plate.get_position().y + PLATE_HEIGHT, al_map_rgb(0, 255, 0), 2);

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
            // Calculating the ball's bounce direction
            const Vector2f direction = Ball::get_bounce_direction(ball.get_direction(), brick_collision_normal);
            ball.set_direction(direction);
            // Updating the player score
            score += bricks[i].get_points_reward();
        }
    }

    // Checking for collisions with the plate
    Vector2f plate_collision_normal{};
    const bool intersect_plate = intersect_circle_AABB(ball.get_position(), BALL_RADIUS, plate.get_position(),
                                                       PLATE_WIDTH, PLATE_HEIGHT, plate_collision_normal);
    if (intersect_plate) {
        const float alpha_radians = (360 - (30 + 120 * (1 - (ball.get_position().x - plate.get_position().x) / PLATE_WIDTH))) * static_cast<float>(M_PI / 180.0f);
        ball.set_direction(Vector2f{std::cos(alpha_radians), std::sin(alpha_radians)});
    }

    // Checking for collisions with the walls
    const Vector2f ball_position  = ball.get_position();
    const Vector2f ball_direction = ball.get_direction();

    if (ball_position.x - BALL_RADIUS < 0) {
        ball.set_direction(Ball::get_bounce_direction(ball_direction, {1, 0}));
    } else if (ball_position.x + BALL_RADIUS > WINDOW_WIDTH) {
        ball.set_direction(Ball::get_bounce_direction(ball_direction, {-1, 0}));
    } else if (ball_position.y + BALL_RADIUS < 0) {
        ball.set_direction(Ball::get_bounce_direction(ball_direction, {0, 1}));
    } else if (ball_position.y - BALL_RADIUS > WINDOW_HEIGHT) {
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
        case ALLEGRO_KEY_Q:
            plate.set_direction(Vector2f{-1, 0});
            plate_moving_left = true;
            break;
        case ALLEGRO_KEY_D:
            plate.set_direction(Vector2f{1, 0});
            plate_moving_right = true;
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
        case ALLEGRO_KEY_Q:
            plate_moving_left = false;
            break;
        case ALLEGRO_KEY_D:
            plate_moving_right = false;
            break;
        default:
            break;
    }
}
