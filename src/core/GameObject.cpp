#include "GameObject.hpp"

#include <allegro5/allegro_primitives.h>

GameObject::GameObject(const Vector2f _position, const Vector2f _direction, const Vector2f _size,
                       const float _speed): position(_position), direction(_direction), size(_size), speed(_speed) {
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

void GameObject::draw(ALLEGRO_BITMAP *bitmap) const {
    al_draw_bitmap(bitmap, position.x, position.y, 0);
}
