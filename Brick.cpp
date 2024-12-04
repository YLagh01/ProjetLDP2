#include "Brick.hpp"

Brick::Brick(ALLEGRO_COLOR _color, Position _position, Direction _direction, float _speed):GameObject(
    {
      {_position.x - 20, _position.y + 15},
      {_position.x + 20, _position.y + 15},
      {_position.x + 20, _position.y - 15},
      {_position.x - 20, _position.y - 15}
    }
    , _position
    , _direction
    ,_speed)
    , color(_color){}

void Brick::draw_vertexes(){
    for(auto& vertex:vertexes){
      al_draw_filled_circle(vertex[0], vertex[1], 2 , al_map_rgb(0,0,255));
    }
  }