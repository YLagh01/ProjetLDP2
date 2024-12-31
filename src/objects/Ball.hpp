/*
 * INFO-F202 (2024 - 2025)
 * Written with ❤︎ by Yassir Laghmouchi & Nabil El Muhur @ ULB
 */

#ifndef BALL_HPP
#define BALL_HPP

#include "../core/GameObject.hpp"

class Ball : public GameObject {
public:
    Ball(ALLEGRO_BITMAP *_bitmap, Vector2f _position, Vector2f _direction, float _speed);

    static Vector2f get_bounce_direction(Vector2f, Vector2f);
};

#endif
