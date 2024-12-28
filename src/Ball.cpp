#include "Ball.hpp"

#include "Common.hpp"

#include <allegro5/allegro_primitives.h>

Ball::Ball(const Vector2f _position, const Vector2f _direction, const float _speed): GameObject(
    _position, _direction, _speed) {
}

void Ball::draw() const {
    al_draw_filled_circle(position.x, position.y, BALL_RADIUS, al_map_rgb(0, 0, 255));
}

Vector2f Ball::get_bounce_direction(const Vector2f init_direction, const Vector2f normal) {
    return Vector2f{
        init_direction.x - 2.0f * (init_direction.x * normal.x + init_direction.y * normal.y) * normal.x,
        init_direction.y - 2.0f * (init_direction.x * normal.x + init_direction.y * normal.y) * normal.y
    };
}
