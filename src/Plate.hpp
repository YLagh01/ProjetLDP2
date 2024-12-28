#ifndef PLATE_HPP
#define PLATE_HPP

#include "GameObject.hpp"

class Plate : public GameObject {
public:
    Plate(ALLEGRO_BITMAP *_bitmap, Vector2f _position, Vector2f _direction, float _speed);

    ALLEGRO_BITMAP *get_bitmap() const;

    void set_bitmap(ALLEGRO_BITMAP *);

    bool check_collision_walls() const;

    bool get_moving_left() const;

    void set_moving_left(bool);

    bool get_moving_right() const;

    void set_moving_right(bool);

private:
    ALLEGRO_BITMAP *bitmap;

    bool moving_left;
    bool moving_right;
};

#endif
