/*
 * INFO-F202 (2024 - 2025)
 * Written with ❤︎ by Yassir Laghmouchi & Nabil El Muhur @ ULB
 */

#include "GameObject.hpp"

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
    size = _size;
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

void GameObject::move(const float _speed, const Vector2f _direction) {
    // Using vector operations to account for movement (A = A + v * B)
    position.x += _speed * _direction.x;
    position.y += _speed * _direction.y;
}

void GameObject::draw() const {
    al_draw_bitmap(bitmap, position.x, position.y, 0);
}

bool GameObject::intersects(const Vector2f target_origin, const Vector2f target_size, Vector2f &intersection_normal) {
    // Calculating the upper bounds of each of the AABBs
    const float source_upper_x = position.x      + size.x;
    const float source_upper_y = position.y      + size.y;
    const float target_upper_x = target_origin.x + target_size.x;
    const float target_upper_y = target_origin.y + target_size.y;

    // Checking if the AABBs overlap on the two axes
    if (source_upper_x < target_origin.x || position.x > target_upper_x ||
        source_upper_y < target_origin.y || position.y > target_upper_y) {
        intersection_normal = NULL_VECTOR;
        return false;
    }

    // Calculating the distance of the overlap on the two axes
    const float overlap_x = std::min(source_upper_x, target_upper_x) - std::max(position.x, target_origin.x);
    const float overlap_y = std::min(source_upper_y, target_upper_y) - std::max(position.y, target_origin.y);

    // Determining the intersection normal from the overlap and respective origin coordinates on the two axes
    if (overlap_x < overlap_y) {
        if (position.x < target_origin.x) {
            intersection_normal = LEFT_VECTOR; // Left face of the target
        } else {
            intersection_normal = RIGHT_VECTOR; // Right face of the target
        }
    } else {
        if (position.y < target_origin.y) {
            intersection_normal = UP_VECTOR; // Top face of the target
        } else {
            intersection_normal = BOTTOM_VECTOR; // Bottom face of the target
        }
    }

    // Resolving the intersection position to prevent clipping
    if (intersection_normal.x != 0) {
        position.x += intersection_normal.x * overlap_x;
    }
    if (intersection_normal.y != 0) {
        position.y += intersection_normal.y * overlap_y;
    }
    // An intersection was found
    return true;
}
