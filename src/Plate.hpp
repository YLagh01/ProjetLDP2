#ifndef PLATE_HPP
#define PLATE_HPP

#include "GameObject.hpp"



class Plate:public GameObject{
    public:
    Plate(ALLEGRO_BITMAP* _bitmap, Position _position, Direction _direction, float _speed);
    
    void move(bool direction);

    private:
    ALLEGRO_BITMAP *bitmap;

};

const int plate_width = 130;
const int plate_height = 34;

#endif