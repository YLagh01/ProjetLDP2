#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include <allegro5/allegro_font.h>
#include <allegro5/color.h>

#include <vector>

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
    GameObject(const std::vector<std::vector<float> > &_vertices, Position _position, Direction _direction, float _speed);

    std::vector<float> get_collision_normal_vector(const GameObject &) const;

    Position get_position() const;

    Direction get_direction() const;

    void set_direction(Direction);

    float get_speed() const;

    void set_speed(float);

    void move();

    void draw(ALLEGRO_COLOR) const;

    void draw(ALLEGRO_BITMAP *) const;

    void draw_vertices() const;

protected:
    std::vector<std::vector<float> > vertices;

    Position position;

    Direction direction;

    float speed = 0;

private:
    static float get_maximum(std::vector<float>);

    static float get_minimum(std::vector<float>);

    static float get_vector_size(const std::vector<float> &);

    std::vector<float> MTV(const std::vector<std::vector<float> > &, const std::vector<std::vector<float> > &) const;
};

#endif
