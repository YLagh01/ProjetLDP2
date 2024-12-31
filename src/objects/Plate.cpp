/*
 * INFO-F202 (2024 - 2025)
 * Written with ❤︎ by Yassir Laghmouchi & Nabil El Muhur @ ULB
 */

#include "Plate.hpp"

Plate::Plate(ALLEGRO_BITMAP *_bitmap, const Vector2f _position, const Vector2f _direction,
             const float _speed): GameObject(_bitmap, _position, _direction, Vector2f{PLATE_WIDTH, PLATE_HEIGHT}, _speed) {
    moving_left  = false;
    moving_right = false;
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
    return (static_cast<int>(direction.x) == -1 && position.x - speed <= BORDERS_SIZE) ||
           (static_cast<int>(direction.x) == 1 && position.x + speed + PLATE_WIDTH > WINDOW_WIDTH - BORDERS_SIZE);
}
