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

bool intersect_circle_AABB(const Vector2f circle_origin, const float circle_radius,
                          const Vector2f aabb_origin, const float aabb_width, const float aabb_height,
                          Vector2f &intersection_normal) {
    // Finding the closest point on the AABB from the circle origin
    const float closest_x = std::max(aabb_origin.x, std::min(circle_origin.x, aabb_origin.x + aabb_width));
    const float closest_y = std::max(aabb_origin.y, std::min(circle_origin.y, aabb_origin.y + aabb_height));

    const float distance_x = circle_origin.x - closest_x;
    const float distance_y = circle_origin.y - closest_y;

    // No possible intersection, the AABB is out of range
    if (distance_x * distance_x + distance_y * distance_y > circle_radius * circle_radius) {
        intersection_normal = Vector2f{0, 0};
        return false;
    }

    // Computing the distance to each of the AABB faces
    const float left_dist   = std::fabs(circle_origin.x - (aabb_origin.x - circle_radius));               // Distance to the left face
    const float right_dist  = std::fabs(circle_origin.x - (aabb_origin.x + aabb_width + circle_radius));  // Distance to the right face
    const float top_dist    = std::fabs(circle_origin.y - (aabb_origin.y - circle_radius));               // Distance to the top face
    const float bottom_dist = std::fabs(circle_origin.y - (aabb_origin.y + aabb_height + circle_radius)); // Distance to the bottom face

    // The smallest distance to the AABB is the distance to the nearest face
    const float min_dist = std::min(std::min(left_dist, right_dist), std::min(top_dist, bottom_dist));

    // Determining the intersection normal from the nearest face
    if (min_dist == left_dist) {
        intersection_normal = Vector2f{1, 0}; // Left face
    } else if (min_dist == right_dist) {
        intersection_normal = Vector2f{-1, 0}; // Right face
    } else if (min_dist == top_dist) {
        intersection_normal = Vector2f{0, 1}; // Top face
    } else if (min_dist == bottom_dist) {
        intersection_normal = Vector2f{0, -1}; // Bottom face
    }

    // An intersection was found
    return true;
}
