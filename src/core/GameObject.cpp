/*
 * INFO-F202 (2024 - 2025)
 * Written with ❤︎ by Yassir Laghmouchi & Nabil El Muhur @ ULB
 */

#include "GameObject.hpp"

#include <allegro5/allegro_primitives.h>

GameObject::GameObject(ALLEGRO_BITMAP *_bitmap, const Vector2f _position, const Vector2f _direction, const Vector2f _size,
                       const float _speed): bitmap(_bitmap), position(_position), direction(_direction), size(_size), speed(_speed) {
}

ALLEGRO_BITMAP *GameObject::get_bitmap() const {
    return bitmap;
}

void GameObject::set_bitmap(ALLEGRO_BITMAP *_bitmap) {
    bitmap = _bitmap;
}

Vector2f GameObject::get_position() const {
    return position;
}

void GameObject::set_position(const Vector2f _position) {
    position = _position;
}

Vector2f GameObject::get_direction() const {
    return direction;
}

void GameObject::set_direction(const Vector2f _direction) {
    direction = _direction;
}

Vector2f GameObject::get_size() const {
    return size;
}

void GameObject::set_size(const Vector2f _size) {
    position = _size;
}

float GameObject::get_speed() const {
    return speed;
}

void GameObject::set_speed(const float _speed) {
    speed = _speed;
}

void GameObject::move() {
    // Using vector operations to account for movement (A = A + v * B)
    position.x += speed * direction.x;
    position.y += speed * direction.y;
}

void GameObject::draw() const {
    al_draw_bitmap(bitmap, position.x, position.y, 0);
}
