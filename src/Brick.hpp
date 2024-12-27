#ifndef BRICK_HPP
#define BRICK_HPP

#include "GameObject.hpp"

class Brick : public GameObject {
public:
    Brick(ALLEGRO_COLOR _color, Position _position, Direction _direction, float _speed);

    void draw_vertices() const;

private:
    ALLEGRO_COLOR color;
};

#endif
