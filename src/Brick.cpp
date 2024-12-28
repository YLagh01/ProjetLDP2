#include "Brick.hpp"

#include "Common.hpp"

#include <allegro5/allegro_primitives.h>

Brick::Brick(const ALLEGRO_COLOR _color, const Vector2f _position, const Vector2f _direction, const float _speed,
             const int _points_reward): GameObject(_position, _direction, _speed), color(_color),
                                        points_reward(_points_reward) {
}

void Brick::draw() const {
    al_draw_filled_rectangle(position.x, position.y, position.x + BRICK_WIDTH, position.y + BRICK_HEIGHT, color);
}

int Brick::get_points_reward() const {
    return points_reward;
}
