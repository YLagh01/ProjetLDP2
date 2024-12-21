#ifndef BALL_HPP
#define BALL_HPP

#include "GameObject.hpp"

class Ball:public GameObject{

public:

    Ball(Position _position, Direction _direction, float _speed);

    void draw();
};

#endif