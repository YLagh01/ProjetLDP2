#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>

#include <allegro5/color.h>

#include <cmath>
#include <iostream>
#include <vector>
#include <unordered_map>

#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP


using namespace std;

struct Position{
  float x;
  float y;
};

struct Direction{
  float x;
  float y;
};

class GameObject{

public:
    GameObject(vector<vector<float>> _vertexes, Position _position, Direction _direction, float _speed);

    vector<float> get_collision_normal_vector(GameObject other);

    void draw(ALLEGRO_COLOR color);

    void draw(ALLEGRO_BITMAP* bitmap);

    void set_direction(Direction direction);

    Direction get_direction();

    Position get_position();

    void move();

    void draw_vertexes();

protected:

    vector<vector<float>> vertexes;
    
    Position position;
    
    Direction direction;

    float speed = 0;



private:

    float get_maximum(vector<float> values);

    float get_minimum(vector<float> values);

    float get_vector_size(vector<float> vector);

    vector<float> MTV(vector<vector<float>> this_vertexes, vector<vector<float>> other_vertexes);



};

#endif
