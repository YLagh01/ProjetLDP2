#include "Common.hpp"

#include <cmath>
#include <vector>

float get_minimum(std::vector<float> values) {
    float minimum = values[0];
    for (const float value: values) {
        if (value < minimum) { minimum = value; }
    }
    return minimum;
}

float get_maximum(std::vector<float> values) {
    float maximum = values[0];
    for (const float value: values) {
        if (value > maximum) { maximum = value; }
    }
    return maximum;
}

float get_length(const std::vector<float> &vector) {
    return std::sqrt(vector[0] * vector[0] + vector[1] * vector[1]);
}

float get_length(const float vector) {
    return std::sqrt(vector * vector + vector * vector);
}

bool intersect_AABB_AABB(const Vector2f source_origin, const Vector2f source_size,
                         const Vector2f target_origin, const Vector2f target_size,
                         Vector2f &intersection_normal) {
    // Calculating the upper bounds of each of the AABBs
    const float source_upper_x = source_origin.x + source_size.x;
    const float source_upper_y = source_origin.y + source_size.y;
    const float target_upper_x = target_origin.x + target_size.x;
    const float target_upper_y = target_origin.y + target_size.y;

    // Checking if the AABBs overlap on the two axes
    // Adding epsilon to the upper bounds prevent clipping
    if (source_upper_x + EPS < target_origin.x || source_origin.x > target_upper_x + EPS ||
        source_upper_y + EPS < target_origin.y || source_origin.y > target_upper_y + EPS) {
        intersection_normal = Vector2f{0, 0};
        return false;
    }

    // Calculating the length of the overlap on the two axes
    const float overlap_x = std::min(source_upper_x, target_upper_x) - std::max(source_origin.x, target_origin.x);
    const float overlap_y = std::min(source_upper_y, target_upper_y) - std::max(source_origin.y, target_origin.y);

    // Determining the intersection normal from the overlap and respective origin coordinates on the two axes
    if (overlap_x < overlap_y) {
        if (source_origin.x < target_origin.x) {
            intersection_normal = Vector2f{1, 0}; // Left face of target
        } else {
            intersection_normal = Vector2f{-1, 0}; // Right face of target
        }
    } else {
        if (source_origin.y < target_origin.y) {
            intersection_normal = Vector2f{0, 1}; // Top face of target
        } else {
            intersection_normal = Vector2f{0, -1}; // Bottom face of target
        }
    }

    // An intersection was found
    return true;
}
