#include "Ball.hpp"

#include "Common.hpp"

#include <allegro5/allegro_primitives.h>

Ball::Ball(const Vector2f _position, const Vector2f _direction, const float _speed): GameObject(
    _position, _direction, _speed) {
}

Vector2f Ball::get_bounce_direction(const Vector2f init_direction, const Vector2f normal) {
    return Vector2f{
        init_direction.x - 2.0f * (init_direction.x * normal.x + init_direction.y * normal.y) * normal.x,
        init_direction.y - 2.0f * (init_direction.x * normal.x + init_direction.y * normal.y) * normal.y
    };
}
