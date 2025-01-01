/*
 * INFO-F202 (2024 - 2025)
 * Written with ❤︎ by Yassir Laghmouchi & Nabil El Muhur @ ULB
 */

#include "Plate.hpp"

Plate::Plate(ALLEGRO_BITMAP *_bitmap, const Vector2f _position, const Vector2f _direction,
             const float _speed): GameObject(_bitmap, _position, _direction, Vector2f{}, _speed) {
    size = Vector2f{
        static_cast<float>(al_get_bitmap_width(bitmap)),
        static_cast<float>(al_get_bitmap_height(bitmap))
    };

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

bool Plate::check_collisions_walls() const {
    // Checking if the plate's coordinates exceed the stage's bounds
    return (static_cast<int>(direction.x) == -1 && position.x - speed <= BORDERS_SIZE) ||
           (static_cast<int>(direction.x) == 1 && position.x + speed + size.x > WINDOW_WIDTH - BORDERS_SIZE);
}

void Plate::change_sprite(ALLEGRO_BITMAP *new_sprite) {
    const float previous_size_x = size.x;

    bitmap = new_sprite;

    size = Vector2f{
        static_cast<float>(al_get_bitmap_width(new_sprite)),
        static_cast<float>(al_get_bitmap_height(new_sprite))
    };

    // Re-centering the plate on the X axis after the size changed
    position = Vector2f{
        position.x - std::abs(previous_size_x - size.x) / 2,
        position.y
    };
}
