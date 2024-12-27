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
    al_draw_filled_circle(vertices[0][0], vertices[0][1], 2, al_map_rgb(255, 0, 0));
    al_draw_filled_circle(vertices[1][0], vertices[1][1], 2, al_map_rgb(0, 255, 0));
    al_draw_filled_circle(vertices[2][0], vertices[2][1], 2, al_map_rgb(0, 0, 255));
    al_draw_filled_circle(vertices[3][0], vertices[3][1], 2, al_map_rgb(0, 0, 0));
}
