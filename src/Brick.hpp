#ifndef BRICK_HPP
#define BRICK_HPP

#include "GameObject.hpp"

class Brick : public GameObject {
public:
    Brick(ALLEGRO_COLOR _color, Vector2f _position, Vector2f _direction, float _speed, int _points_reward);

    void draw() const;

    int get_points_reward() const;

private:
    ALLEGRO_COLOR color;

    int points_reward;
};

#endif
