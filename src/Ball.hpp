#ifndef BALL_HPP
#define BALL_HPP

#include "GameObject.hpp"

class Ball : public GameObject {
public:
    Ball(Vector2f _position, Vector2f _direction, float _speed);

    void draw() const;

    static Vector2f get_bounce_direction(Vector2f, Vector2f) ;
};

#endif
