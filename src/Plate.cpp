#include "Plate.hpp"

#include "Main.hpp"

#include <allegro5/allegro_primitives.h>

Plate::Plate(ALLEGRO_BITMAP *_bitmap, const Position _position, const Direction _direction, const float _speed): GameObject(
    {
        {_position.x, _position.y + static_cast<float>(plate_height)}, // Bottom left vertex
        {_position.x + static_cast<float>(plate_width), _position.y + static_cast<float>(plate_height)}, // Bottom right vertex
        {_position.x + static_cast<float>(plate_width), _position.y},  // Top right vertex
        {_position.x, _position.y} // Top left vertex
    }
    , _position
    ,_direction
    , _speed), bitmap(_bitmap) {
}

void Plate::draw_vertices() const {
    al_draw_filled_circle(vertices[0][0], vertices[0][1], 2, al_map_rgb(255, 0, 0));
    al_draw_filled_circle(vertices[1][0], vertices[1][1], 2, al_map_rgb(0, 255, 0));
    al_draw_filled_circle(vertices[2][0], vertices[2][1], 2, al_map_rgb(0, 0, 255));
    al_draw_filled_circle(vertices[3][0], vertices[3][1], 2, al_map_rgb(0, 0, 0));
}

bool Plate::check_collision_walls() const {
    return (get_direction().x == -1 && get_position().x <= 0) ||
        (get_direction().x == 1 && get_position().x + get_speed() + plate_width > WINDOW_WIDTH);
}
