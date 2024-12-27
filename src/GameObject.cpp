#include "GameObject.hpp"

#include <complex>
#include <allegro5/allegro_primitives.h>


GameObject::GameObject(const vector<vector<float> > &_vertices, const Position _position, const Direction _direction,
                       const float _speed): vertices(_vertices), position(_position), direction(_direction),
                                            speed(_speed) {
}

vector<float> GameObject::get_collision_normal_vector(const GameObject &target) const {
    vector<float> first  = MTV(vertices, target.vertices);
    vector<float> second = MTV(target.vertices, vertices);
    if (get_vector_size(first) < get_vector_size(second)) {
        return first;
    }
    return second;
}

// vector<float> GameObject::get_collision_normal_vector(GameObject other) {
//     vector<float> collision = MTV(vertexes, other.vertexes);

//     // Add a small epsilon to avoid floating-point precision issues
//     const float EPSILON = 1e-5;
//     if (abs(collision[0]) > EPSILON || abs(collision[1]) > EPSILON) {
//         return collision;
//     }

//     return {0, 0};
// }


void GameObject::draw(const ALLEGRO_COLOR color) const {
    //Use draw_polygon instead
    al_draw_filled_rectangle(position.x - 20, position.y + 10, position.x + 20, position.y - 10, color);
}

void GameObject::draw(ALLEGRO_BITMAP *bitmap) const {
    al_draw_bitmap(bitmap, position.x, position.y, 0);
}

void GameObject::set_direction(const Direction _direction) {
    direction = _direction;
}

void GameObject::move() {
    position.x += speed * direction.x;
    position.y += speed * direction.y;
    for (auto &vertex: vertices) {
        vertex[0] += speed * direction.x;
        vertex[1] += speed * direction.y;
    }
}

Direction GameObject::get_direction() const {
    return direction;
}


Position GameObject::get_position() const {
    return position;
}

void GameObject::draw_vertices() {
    for (auto &vertex: vertices) {
        al_draw_filled_circle(vertex[0], vertex[1], 2, al_map_rgb(0, 0, 255));
    }
}


float GameObject::get_maximum(vector<float> values) {
    float maximum = values[0];
    for (const float value: values) {
        if (value > maximum) { maximum = value; }
    }
    return maximum;
}

float GameObject::get_minimum(vector<float> values) {
    float minimum = values[0];
    for (const float value: values) {
        if (value < minimum) { minimum = value; }
    }
    return minimum;
}

float GameObject::get_vector_size(const vector<float> &vector) {
    return std::sqrt(vector[0] * vector[0] + vector[1] * vector[1]);
}


vector<float> GameObject::MTV(const vector<vector<float> > &source_vertices,
                              const vector<vector<float> > &target_vertices) const {
    vector<vector<float> > translation_vectors;

    for (long unsigned int i = 0; i < source_vertices.size(); i++) {
        const vector<float> &vertex1 = source_vertices[i];
        const vector<float> &vertex2 = source_vertices[(i + 1) % source_vertices.size()];

        vector<float> source_projections;
        vector<float> target_projections;

        vector<float> normal_axis = {vertex2[1] - vertex1[1], -(vertex2[0] - vertex1[0])};
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
            return vector<float>{0, 0};
        }
    }
    for (long unsigned int i = 0; i < translation_vectors.size(); i++) {
        const float dot_product = direction.x * translation_vectors[i][0] + direction.y * translation_vectors[i][1];
        if (dot_product > 0) {
            translation_vectors.erase(translation_vectors.begin() + static_cast<long>(i));
        }
    }

    vector<float> result = {translation_vectors[0][0], translation_vectors[0][1]};
    for (auto &vector: translation_vectors) {
        const float size = get_vector_size(vector);

        if (get_vector_size(result) > size && size != 0) {
            result[0] = vector[0];
            result[1] = vector[1];
        }
    }

    return result;
}

// vector<float> GameObject::MTV(vector<vector<float>> this_vertices, vector<vector<float>> other_vertices) {
//     float smallest_overlap = std::numeric_limits<float>::max();
//     vector<float> smallest_translation = {0, 0};

//     // Check axes of both polygons
//     for (int polygon = 0; polygon < 2; polygon++) {
//         vector<vector<float>>& current_vertices = (polygon == 0) ? this_vertices : other_vertices;

//         for (size_t i = 0; i < current_vertices.size(); i++) {
//             // Compute normal axis (perpendicular to current edge)
//             vector<float> vertex1 = current_vertices[i];
//             vector<float> vertex2 = current_vertices[(i + 1) % current_vertices.size()];

//             // Perpendicular normal axis (normalized)
//             vector<float> normal_axis = {
//                 vertex2[1] - vertex1[1],
//                 -(vertex2[0] - vertex1[0])
//             };

//             float axis_length = sqrt(normal_axis[0]*normal_axis[0] + normal_axis[1]*normal_axis[1]);
//             if (axis_length == 0) continue;

//             normal_axis[0] /= axis_length;
//             normal_axis[1] /= axis_length;

//             // Project vertices
//             float this_min = std::numeric_limits<float>::max();
//             float this_max = std::numeric_limits<float>::lowest();
//             float other_min = std::numeric_limits<float>::max();
//             float other_max = std::numeric_limits<float>::lowest();

//             for (auto& vertex : this_vertices) {
//                 float proj = vertex[0] * normal_axis[0] + vertex[1] * normal_axis[1];
//                 this_min = std::min(this_min, proj);
//                 this_max = std::max(this_max, proj);
//             }

//             for (auto& vertex : other_vertices) {
//                 float proj = vertex[0] * normal_axis[0] + vertex[1] * normal_axis[1];
//                 other_min = std::min(other_min, proj);
//                 other_max = std::max(other_max, proj);
//             }

//             // Check for separation
//             if (this_max < other_min || this_min > other_max) {
//                 return {0, 0}; // No collision
//             }

//             // Compute overlap
//             float overlap = std::min(this_max - other_min, other_max - this_min);

//             // Track smallest translation
//             if (overlap < smallest_overlap) {
//                 smallest_overlap = overlap;
//                 smallest_translation = {
//                     normal_axis[0] * overlap,
//                     normal_axis[1] * overlap
//                 };
//             }
//         }
//     }

//     return smallest_translation;
// }
