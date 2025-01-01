/*
 * INFO-F202 (2024 - 2025)
 * Written with ❤︎ by Yassir Laghmouchi & Nabil El Muhur @ ULB
 */

#include "Laser.hpp"

#include <allegro5/allegro_primitives.h>

Laser::Laser(ALLEGRO_BITMAP *_bitmap, const Vector2f _position): GameObject(
    _bitmap, _position, Vector2f{}, Vector2f{}, LASER_SPEED) {
    direction = UP_VECTOR;
    size      = Vector2f{15, 25};
}

void Laser::draw() const {
    al_draw_filled_rectangle(position.x, position.y, position.x + size.x, position.y + size.y, al_map_rgb(3, 223, 252));
}

void Laser::spawn_laser(std::vector<std::shared_ptr<Laser> > &lasers, const Plate &plate) {
    Laser laser{nullptr, Vector2f{}};

    laser.set_position(Vector2f{
        plate.get_position().x + (plate.get_size().x - laser.get_size().x) / 2,
        plate.get_position().y - laser.get_size().y
    });

    lasers.push_back(std::make_shared<Laser>(laser));
}
