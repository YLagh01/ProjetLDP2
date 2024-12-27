#include "Ball.hpp"

#include "Main.hpp"

#include <allegro5/allegro_primitives.h>
#include <cmath>

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

Direction Ball::get_bounce_direction(const Direction init_direction, std::vector<float> normal) {
    const float length = std::sqrt(normal[0] * normal[0] + normal[1] * normal[1]);
    normal[0] /= length;
    normal[1] /= length;
    return Direction{
        init_direction.x - 2 * (init_direction.x * normal[0] + init_direction.y * normal[1]) * normal[0],
        init_direction.y - 2 * (init_direction.x * normal[0] + init_direction.y * normal[1]) * normal[1]
    };
}
