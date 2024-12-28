#include "Plate.hpp"

#include "Common.hpp"

#include <allegro5/allegro_primitives.h>

Plate::Plate(ALLEGRO_BITMAP *_bitmap, const Vector2f _position, const Vector2f _direction,
             const float _speed): GameObject(_position, _direction, _speed), bitmap(_bitmap) {
    moving_left  = false;
    moving_right = false;
}

ALLEGRO_BITMAP *Plate::get_bitmap() const {
    return bitmap;
}

void Plate::set_bitmap(ALLEGRO_BITMAP *_bitmap) {
    bitmap = _bitmap;
}

bool Plate::get_moving_left() const {
    return moving_left;
}

void Plate::set_moving_left(const bool _moving_left) {
    moving_left = _moving_left;
}

bool Plate::get_moving_right() const {
    return moving_right;
}

void Plate::set_moving_right(const bool _moving_right) {
    moving_right = _moving_right;
}

bool Plate::check_collision_walls() const {
    return (direction.x == -1 && position.x - speed <= BORDERS_SIZE) ||
           (direction.x == 1 && position.x + speed + PLATE_WIDTH > WINDOW_WIDTH - BORDERS_SIZE);
}
