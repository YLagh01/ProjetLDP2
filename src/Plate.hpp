#ifndef PLATE_HPP
#define PLATE_HPP

#include "GameObject.hpp"

class Plate : public GameObject {
public:
    Plate(ALLEGRO_BITMAP *_bitmap, Vector2f _position, Vector2f _direction, float _speed);

    bool check_collision_walls() const;

    ALLEGRO_BITMAP *get_bitmap() const;

private:
    ALLEGRO_BITMAP *bitmap;
};

#endif
