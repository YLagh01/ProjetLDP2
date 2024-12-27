#include "GameOrchestra.hpp"

#include <cmath>

GameOrchestra::GameOrchestra() {
    init_bricks();
}


void GameOrchestra::check_collisions() {
    for (long unsigned int i = 0; i < Bricks.size(); i++) {
        vector<float> collision = ball.get_collision_normal_vector(Bricks[i]);
        if (collision[0] != 0 || collision[1] != 0) {
            Bricks.erase(Bricks.begin() + static_cast<long>(i));
            const Direction direction = get_reflected_direction(ball.get_direction(), collision);
            ball.set_direction(direction);
        }
    }

    //Check collision with the plate


    const vector<float> plate_collision = ball.get_collision_normal_vector(plate);
    if (plate_collision[0] != 0 && plate_collision[1] != 0) {
        const float alpha = 30 + 120 * (1 - plate.get_position().x / plate_width);
        ball.set_direction(Direction{1, std::tan(alpha)});
    }


    //Check collision with the wall

    check_collision_wall();
}

void GameOrchestra::draw() const {
    plate.draw(al_load_bitmap("../res/plate.png"));
    ball.draw();
    for (auto &brick: Bricks) {
        brick.draw(al_map_rgb(255, 0, 0));
    }
}

void GameOrchestra::move_plate(const bool direction) {
    plate.move(direction);
}

void GameOrchestra::move_ball() {
    ball.move();
}

void GameOrchestra::draw_ball() {
    ball.draw_vertices();
}

void GameOrchestra::draw_plate() {
    plate.draw_vertices();
}

void GameOrchestra::draw_bricks() const {
    for (const auto &brick: Bricks) {
        brick.draw_vertices();
    }
}


Direction GameOrchestra::get_reflected_direction(const Direction init_direction, vector<float> normal) {
    const float length = std::sqrt(normal[0] * normal[0] + normal[1] * normal[1]);
    normal[0] /= length;
    normal[1] /= length;
    return Direction{
        init_direction.x - 2 * (init_direction.x * normal[0] + init_direction.y * normal[1]) * normal[0],
        init_direction.y - 2 * (init_direction.x * normal[0] + init_direction.y * normal[1]) * normal[1]
    };
}


void GameOrchestra::init_bricks() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 14; j++) {
            Position position{};
            position.x = static_cast<float>(40 * j + 20);
            position.y = static_cast<float>(50 * (i + 1));
            Brick brick{al_map_rgb(255, 0, 0), position, {0, 0}, 0};
            Bricks.push_back(brick);
        }
    }
}

void GameOrchestra::check_collision_wall() {
    const Position ball_position = ball.get_position();

    if (ball_position.x - 5 < 0) {
        ball.set_direction(get_reflected_direction(ball.get_direction(), {1, 0}));
    }
    if (ball_position.x + 5 > 560) {
        ball.set_direction(get_reflected_direction(ball.get_direction(), {-1, 0}));
    }
    if (ball_position.y + 5 < 0) {
        ball.set_direction(get_reflected_direction(ball.get_direction(), {0, 1}));
    }
    if (ball_position.y - 5 > 900) {
        ball.set_direction(get_reflected_direction(ball.get_direction(), {0, -1}));
    }
}
