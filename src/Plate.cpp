
#include "Plate.hpp"


Plate::Plate(ALLEGRO_BITMAP* _bitmap, Position _position, Direction _direction, float _speed):bitmap(_bitmap), GameObject(
    {
    {position.x - plate_width/2, position.y + plate_height/2},
    {position.x + plate_width/2, position.y + plate_height/2},
    {position.x + plate_width/2, position.y - plate_height/2},
    {position.x - plate_width/2, position.y - plate_height/2}
    }
    , _position
    ,_direction
    , _speed){}

 
void Plate::move(bool direction) {
    if (direction == 0 && position.x - 10 > 0){
      position.x -= 10;
    }
    else if (direction == 1 && position.x +10 < 130){
      position.x += 10;
    }
  }