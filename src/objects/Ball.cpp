/*
 * INFO-F202 (2024 - 2025)
 * Written with ❤︎ by Yassir Laghmouchi & Nabil El Muhur @ ULB
 */

#include "Ball.hpp"

Ball::Ball(ALLEGRO_BITMAP *_bitmap, const Vector2f _position, const Vector2f _direction,
           const float _speed): GameObject(_bitmap, _position, _direction, Vector2f{BALL_DIAMETER, BALL_DIAMETER}, _speed) {
}

Vector2f Ball::get_bounce_direction(const Vector2f init_direction, const Vector2f normal) {
    // Using the reflection formula to calculate the bounce direction of the ball (V - 2 * dot(N, V) * N)
    return Vector2f{
        init_direction.x - 2.0f * (init_direction.x * normal.x + init_direction.y * normal.y) * normal.x,
        init_direction.y - 2.0f * (init_direction.x * normal.x + init_direction.y * normal.y) * normal.y
    };
}
