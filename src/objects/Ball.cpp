/*
 * INFO-F202 (2024 - 2025)
 * Written with ❤︎ by Yassir Laghmouchi & Nabil El Muhur @ ULB
 */

#include "Ball.hpp"

#include <cmath>

Ball::Ball(const SpriteManager &_sprite_manager, const Vector2f _position, const Vector2f _direction,
           const float _speed): GameObject(_sprite_manager.ball_bitmap, _position, _direction, Vector2f{}, _speed),
                                sprite_manager(_sprite_manager) {
    size = Vector2f{
        static_cast<float>(al_get_bitmap_width(bitmap)),
        static_cast<float>(al_get_bitmap_height(bitmap))
    };
    caught      = false;
    caught_time = 0;
}

Vector2f Ball::get_bounce_direction(const Vector2f init_direction, const Vector2f normal) {
    // Using the reflection formula to calculate the bounce direction of the ball (V - 2 * dot(N, V) * N)
    return Vector2f{
        init_direction.x - 2.0f * (init_direction.x * normal.x + init_direction.y * normal.y) * normal.x,
        init_direction.y - 2.0f * (init_direction.x * normal.x + init_direction.y * normal.y) * normal.y
    };
}

void Ball::handle_collisions_bricks(std::vector<std::shared_ptr<Brick> > &  bricks,
                                    std::vector<std::shared_ptr<Powerup> > &powerups,
                                    const std::shared_ptr<Powerup> &active_powerup, int &score) {
    // Checking for collisions with the bricks
    Vector2f                     brick_intersection_normal{};
    const std::shared_ptr<Brick> intersected_brick = Brick::intersects_brick(bricks, this, brick_intersection_normal);

    // If a brick was intersected
    if (intersected_brick != nullptr) {
        // Updating the ball's direction to bounce after hitting the brick (reflection formula)
        direction = get_bounce_direction(direction, brick_intersection_normal);

        // Handling what happens when a brick is destroyed
        intersected_brick->on_destroy(bricks, powerups, active_powerup, score);
    }
}

void Ball::handle_collisions_plate(const Plate &plate, const std::shared_ptr<Powerup> &active_powerup) {
    // Checking for collisions with the plate
    Vector2f   plate_collision_normal{};
    const bool intersects_plate = intersects(plate.get_position(), plate.get_size(), plate_collision_normal);

    // Only handling intersections with the plate when the ball wasn't caught
    if (intersects_plate && !caught) {
        // Calculating the ball's bounce direction after hitting the plate
        const float alpha_radians = (360 - (30 + 120 * (1 - (position.x - plate.get_position().x) / plate.get_size().x))) * static_cast<float>(M_PI / 180.0f);
        // Updating the ball's direction to the bounce direction
        direction = Vector2f{std::cos(alpha_radians), std::sin(alpha_radians)};

        // Catching the ball if the catch powerup is active
        if (active_powerup != nullptr && active_powerup->has_type(POWERUP_TYPE::CATCH)) {
            catch_ball(plate);
        }
    }
}

void Ball::handle_collisions_walls() {
    // Checking for collisions with the walls if the ball wasn't caught
    if (!caught) {
        // Left side
        if (position.x <= BORDERS_SIZE) {
            direction = get_bounce_direction(direction, RIGHT_VECTOR);
        }
        // Right side
        else if (position.x + size.x >= WINDOW_WIDTH - BORDERS_SIZE) {
            direction = get_bounce_direction(direction, LEFT_VECTOR);
        }
        // Top side
        else if (position.y <= BORDERS_SIZE) {
            // Top side
            direction = get_bounce_direction(direction, BOTTOM_VECTOR);
        }
    }
}

void Ball::handle_collisions(std::vector<std::shared_ptr<Brick> > &  bricks, const Plate &plate,
                             std::vector<std::shared_ptr<Powerup> > &powerups,
                             const std::shared_ptr<Powerup> &active_powerup, int &score) {
    handle_collisions_bricks(bricks, powerups, active_powerup, score);
    handle_collisions_plate(plate, active_powerup);
    handle_collisions_walls();
}

void Ball::catch_ball(const Plate &plate) {
    // Resolving the ball's position to make it stick only on the surface of the plate
    position = Vector2f{
        std::min(plate.get_position().x + plate.get_size().x - size.x, std::max(position.x, plate.get_position().x)),
        std::min(position.y, plate.get_position().y - size.y)
    };

    caught      = true;
    caught_time = current_time_milliseconds();
}
