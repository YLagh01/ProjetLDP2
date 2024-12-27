#include "GameObject.hpp"

#include <allegro5/allegro_primitives.h>
#include <complex>
#include <vector>

/*
 *  CLASS DEFINITION
 */

GameObject::GameObject(const std::vector<std::vector<float> > &_vertices, const Position _position, const Direction _direction,
                       const float _speed): vertices(_vertices), position(_position), direction(_direction),
                                            speed(_speed) {}

std::vector<float> GameObject::get_collision_normal_vector(const GameObject &target) const {
    std::vector<float> first  = MTV(vertices, target.vertices);
    std::vector<float> second = MTV(target.vertices, vertices);
    if (get_vector_size(first) < get_vector_size(second)) {
        return first;
    }
    return second;
}

Position GameObject::get_position() const {
    return position;
}

Direction GameObject::get_direction() const {
    return direction;
}

void GameObject::set_direction(const Direction _direction) {
    direction = _direction;
}

float GameObject::get_speed() const {
    return speed;
}

void GameObject::set_speed(const float _speed) {
    speed = _speed;
}

void GameObject::move() {
    position.x += speed * direction.x;
    position.y += speed * direction.y;
    for (auto &vertex: vertices) {
        vertex[0] += speed * direction.x;
        vertex[1] += speed * direction.y;
    }
}

/*
 *  DRAW CODE
 */

void GameObject::draw(const ALLEGRO_COLOR color) const {
    // Use draw_polygon instead
    al_draw_filled_rectangle(position.x - 20, position.y + 10, position.x + 20, position.y - 10, color);
}

void GameObject::draw(ALLEGRO_BITMAP *bitmap) const {
    al_draw_bitmap(bitmap, position.x, position.y, 0);
}

void GameObject::draw_vertices() const {
    for (auto &vertex: vertices) {
        al_draw_filled_circle(vertex[0], vertex[1], 2, al_map_rgb(0, 0, 255));
    }
}

/*
 *  INTERSECTION CODE
 */

float GameObject::get_maximum(std::vector<float> values) {
    float maximum = values[0];
    for (const float value: values) {
        if (value > maximum) { maximum = value; }
    }
    return maximum;
}

float GameObject::get_minimum(std::vector<float> values) {
    float minimum = values[0];
    for (const float value: values) {
        if (value < minimum) { minimum = value; }
    }
    return minimum;
}

float GameObject::get_vector_size(const std::vector<float> &vector) {
    return std::sqrt(vector[0] * vector[0] + vector[1] * vector[1]);
}

std::vector<float> GameObject::MTV(const std::vector<std::vector<float> > &source_vertices,
                              const std::vector<std::vector<float> > &target_vertices) const {
    std::vector<std::vector<float> > translation_vectors;

    for (long unsigned int i = 0; i < source_vertices.size(); i++) {
        const std::vector<float> &vertex1 = source_vertices[i];
        const std::vector<float> &vertex2 = source_vertices[(i + 1) % source_vertices.size()];

        std::vector<float> source_projections;
        std::vector<float> target_projections;

        std::vector<float> normal_axis = {vertex2[1] - vertex1[1], -(vertex2[0] - vertex1[0])};
        const float length = get_vector_size(normal_axis);
        normal_axis[0] /= length;
        normal_axis[1] /= length;

        for (const auto &source_vertex: source_vertices) {
            source_projections.push_back(source_vertex[0] * normal_axis[0] + source_vertex[1] * normal_axis[1]);
        }

        for (const auto &target_vertex: target_vertices) {
            target_projections.push_back(target_vertex[0] * normal_axis[0] + target_vertex[1] * normal_axis[1]);
        }

        const float this_min  = get_minimum(source_projections);
        const float this_max  = get_maximum(source_projections);
        const float other_min = get_minimum(target_projections);
        const float other_max = get_maximum(target_projections);

        if (this_max >= other_min && this_min <= other_max) {
            const float overlap = std::min(this_max - other_min, other_max - this_min);
            translation_vectors.push_back({normal_axis[0] * overlap, normal_axis[1] * overlap});
        } else {
            return std::vector<float>{0, 0};
        }
    }

    for (long unsigned int i = 0; i < translation_vectors.size(); i++) {
        const float dot_product = direction.x * translation_vectors[i][0] + direction.y * translation_vectors[i][1];
        if (dot_product > 0) {
            translation_vectors.erase(translation_vectors.begin() + static_cast<long>(i));
        }
    }

    std::vector<float> result = {translation_vectors[0][0], translation_vectors[0][1]};
    for (auto &vector: translation_vectors) {
        const float size = get_vector_size(vector);

        if (get_vector_size(result) > size && size != 0) {
            result[0] = vector[0];
            result[1] = vector[1];
        }
    }
    return result;
}
