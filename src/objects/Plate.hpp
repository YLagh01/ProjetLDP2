/*
 * INFO-F202 (2024 - 2025)
 * Written with ❤︎ by Yassir Laghmouchi & Nabil El Muhur @ ULB
 */

#ifndef PLATE_HPP
#define PLATE_HPP

#include "../core/GameObject.hpp"

class Plate : public GameObject {
public:
    Plate(ALLEGRO_BITMAP *_bitmap, Vector2f _position, Vector2f _direction, float _speed);

    bool check_collision_walls() const;

    bool get_moving_left() const;

    void set_moving_left(bool);

    bool get_moving_right() const;

    void set_moving_right(bool);

private:
    bool moving_left;
    bool moving_right;
};

#endif
