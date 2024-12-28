#include "Plate.hpp"

#include "Common.hpp"

#include <allegro5/allegro_primitives.h>

Plate::Plate(ALLEGRO_BITMAP *_bitmap, const Vector2f _position, const Vector2f _direction,
             const float _speed): GameObject(_position, _direction, _speed), bitmap(_bitmap) {
}

ALLEGRO_BITMAP *Plate::get_bitmap() const {
    return bitmap;
}

bool Plate::check_collision_walls() const {
    return (direction.x == -1 && position.x <= BORDERS_SIZE) ||
           (direction.x == 1 && position.x + PLATE_WIDTH > WINDOW_WIDTH - BORDERS_SIZE);
}
