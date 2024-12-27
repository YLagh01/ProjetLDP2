#include "Brick.hpp"

#include <allegro5/allegro_primitives.h>

Brick::Brick(const ALLEGRO_COLOR _color, const Position _position, const Direction _direction, const float _speed): GameObject(
        {
            {_position.x - 20, _position.y + 15},
            {_position.x + 20, _position.y + 15},
            {_position.x + 20, _position.y - 15},
            {_position.x - 20, _position.y - 15}
        }
        , _position
        , _direction
        , _speed)
    , color(_color) {
}

void Brick::draw_vertices() const {
    for (auto &vertex: vertices) {
        al_draw_filled_circle(vertex[0], vertex[1], 2, al_map_rgb(0, 0, 255));
    }
}
