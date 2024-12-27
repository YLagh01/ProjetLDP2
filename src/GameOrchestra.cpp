#include "GameOrchestra.hpp"

bool plate_moving_left  = false;
bool plate_moving_right = false;

GameOrchestra::GameOrchestra() {
    init_bricks();
}

void GameOrchestra::update() {
    if (!plate.check_collision_walls()) {
        plate.move();
    }

    if (!plate_moving_left && !plate_moving_right) {
        plate.set_direction(Direction{0, 0});
    }

    check_ball_collisions();

    ball.move();
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
    al_draw_bitmap(al_load_bitmap("../res/origbig.png"), 0, 0, ALLEGRO_FLIP_HORIZONTAL & ALLEGRO_FLIP_VERTICAL);

    plate.draw(al_load_bitmap("../res/plate.png"));
    ball.draw();
    for (auto &brick: bricks) {
        brick.draw(al_map_rgb(0, 0, 0));
    }

    ball.draw_vertices();
    plate.draw_vertices();

    for (const auto &brick: bricks) {
        brick.draw_vertices();
    }

    al_flip_display();
}

void GameOrchestra::init_bricks() {
    for (int i = 0; i < BRICK_ROWS; i++) {
        for (int j = 0; j < BRICK_COLUMNS; j++) {
            Position position{};
            position.x = static_cast<float>(BRICK_WIDTH  * j + BRICK_WIDTH * 0.5);
            position.y = static_cast<float>(BRICK_HEIGHT * (i + 1));
            Brick brick{al_map_rgb(255, 0, 0), position, {0, 0}, 0};
            bricks.push_back(brick);
        }
    }
}

void GameOrchestra::check_ball_collisions() {
    // Checking for collisions with the bricks
    for (long unsigned int i = 0; i < bricks.size(); i++) {
        std::vector<float> brick_collision = ball.get_collision_normal_vector(bricks[i]);
        if (brick_collision[0] != 0 || brick_collision[1] != 0) {
            bricks.erase(bricks.begin() + static_cast<long>(i));
            const Direction direction = Ball::get_bounce_direction(ball.get_direction(), brick_collision);
            ball.set_direction(direction);
        }
    }

    // Checking for collisions with the plate
    const std::vector<float> plate_collision = ball.get_collision_normal_vector(plate);
    if (plate_collision[0] != 0 || plate_collision[1] != 0) {
        const Direction direction = Ball::get_bounce_direction(ball.get_direction(), plate_collision);
        ball.set_direction(direction);
    }

    // Checking for collisions with the walls
    const Position  ball_position  = ball.get_position();
    const Direction ball_direction = ball.get_direction();
    constexpr float size = 5;

    if (ball_position.x - size < 0) {
        ball.set_direction(Ball::get_bounce_direction(ball_direction, {1, 0}));
    }
    else if (ball_position.x + size > WINDOW_WIDTH) {
        ball.set_direction(Ball::get_bounce_direction(ball_direction, {-1, 0}));
    }
    else if (ball_position.y + size < 0) {
        ball.set_direction(Ball::get_bounce_direction(ball_direction, {0, 1}));
    }
    else if (ball_position.y - size > WINDOW_HEIGHT) {
        ball.set_direction(Ball::get_bounce_direction(ball_direction, {0, -1}));
    }
}

// Key codes are documented here: https://www.allegro.cc/manual/5/keyboard.html
void GameOrchestra::key_down(const int keyCode) {
    // Called when a key is pressed
    switch (keyCode) {
        case ALLEGRO_KEY_1:
            /* Code for key 1 pressed */
                break;
        case ALLEGRO_KEY_SPACE:
            /* Code for space pressed */
                break;
        case ALLEGRO_KEY_Q:
            plate.set_direction(Direction{-1, 0});
        plate_moving_left = true;
        break;
        case ALLEGRO_KEY_D:
            plate.set_direction(Direction{1, 0});
        plate_moving_right = true;
        break;
        default:
            break;
    }
}

void GameOrchestra::key_up(const int keyCode) {
    // Called when a key is released
    switch (keyCode) {
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
