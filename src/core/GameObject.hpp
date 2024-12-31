/*
 * INFO-F202 (2024 - 2025)
 * Written with ❤︎ by Yassir Laghmouchi & Nabil El Muhur @ ULB
 */

#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include "../Common.hpp"

#include <allegro5/bitmap.h>

class GameObject {
public:
    GameObject(ALLEGRO_BITMAP *_bitmap, Vector2f _position, Vector2f _direction, Vector2f _size, float _speed);

    ALLEGRO_BITMAP *get_bitmap() const;

    void set_bitmap(ALLEGRO_BITMAP *);

    Vector2f get_position() const;

    void set_position(Vector2f _position);

    Vector2f get_direction() const;

    void set_direction(Vector2f);

    Vector2f get_size() const;

    void set_size(Vector2f _size);

    float get_speed() const;

    void set_speed(float);

    void move();

    void draw() const;

protected:
    ALLEGRO_BITMAP *bitmap;

    Vector2f position;

    Vector2f direction;

    Vector2f size;

    float speed;
};

#endif
