#include "Plate.hpp"


Plate::Plate(ALLEGRO_BITMAP *_bitmap, const Position _position, const Direction _direction, const float _speed): GameObject(
    {
        {position.x - static_cast<float>(plate_width) / 2, position.y + static_cast<float>(plate_height) / 2},
        {position.x + static_cast<float>(plate_width) / 2, position.y + static_cast<float>(plate_height) / 2},
        {position.x + static_cast<float>(plate_width) / 2, position.y - static_cast<float>(plate_height) / 2},
        {position.x - static_cast<float>(plate_width) / 2, position.y - static_cast<float>(plate_height) / 2}
    }
    , _position
    ,_direction
    , _speed), bitmap(_bitmap) {
}

void Plate::move(const bool direction) {
    if (direction == 0 && position.x - 10 > 0) {
        position.x -= 10;
    } else if (direction == 1 && position.x + 10 < 130) {
        position.x += 10;
    }
}
