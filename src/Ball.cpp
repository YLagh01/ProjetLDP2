#include "Ball.hpp"

#include <allegro5/allegro_primitives.h>

Ball::Ball(const Position _position, const Direction _direction, const float _speed): GameObject(
    {
        {_position.x + 0.0f, _position.y + 10.0f},
        {_position.x + 8.66f, _position.y + 5.0f},
        {_position.x + 8.66f, _position.y + -5.0f},
        {_position.x + 0.0f, _position.y + -10.0f},
        {_position.x + -8.67f, _position.y + -5.01f},
        {_position.x + -8.67f, _position.y + 4.99f},
    }
    , _position
    , _direction
    , _speed) {
}

void Ball::draw() const {
    al_draw_filled_circle(position.x, position.y, 10, al_map_rgb(0, 0, 255));
}
