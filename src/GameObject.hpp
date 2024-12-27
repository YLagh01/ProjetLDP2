#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include <allegro5/allegro_font.h>
#include <allegro5/color.h>

#include <vector>

using namespace std;

struct Position {
    float x;
    float y;
};

struct Direction {
    float x;
    float y;
};

class GameObject {
public:
    GameObject(const vector<vector<float> > &_vertices, Position _position, Direction _direction, float _speed);

    vector<float> get_collision_normal_vector(const GameObject &) const;

    void draw(ALLEGRO_COLOR) const;

    void draw(ALLEGRO_BITMAP *) const;

    void set_direction(Direction);

    Direction get_direction() const;

    Position get_position() const;

    void move();

    void draw_vertices();

protected:
    vector<vector<float> > vertices;

    Position position;

    Direction direction;

    float speed = 0;

private:
    static float get_maximum(vector<float>);

    static float get_minimum(vector<float>);

    static float get_vector_size(const vector<float> &);

    vector<float> MTV(const vector<vector<float> > &, const vector<vector<float> > &) const;
};

#endif
