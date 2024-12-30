#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include "../Common.hpp"

#include <allegro5/allegro_font.h>

#include <vector>

class GameObject {
public:
    GameObject(Vector2f _position, Vector2f _direction, Vector2f _size, float _speed);

    Vector2f get_position() const;

    void set_position(Vector2f _position);

    Vector2f get_direction() const;

    void set_direction(Vector2f);

    Vector2f get_size() const;

    void set_size(Vector2f _size);

    float get_speed() const;

    void set_speed(float);

    void move();

    void draw(ALLEGRO_BITMAP *) const;

protected:
    Vector2f position;

    Vector2f direction;

    Vector2f size;

    float speed;
};

#endif
