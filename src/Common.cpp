/*
 * INFO-F202 (2024 - 2025)
 * Written with ❤︎ by Yassir Laghmouchi & Nabil El Muhur @ ULB
 */

#include "Common.hpp"

#include <string>
#include <cmath>

int8_t sign(const float value) {
    return (value < 0) ? -1 : 1;
}

void draw_score(const FontManager &font_manager, const int score, const Vector2f &position, const std::string &label,
                const bool one_line) {
    static const ALLEGRO_COLOR label_color = al_map_rgb(255, 255, 255);
    static const ALLEGRO_COLOR value_color = al_map_rgb(255, 0, 0);

    const ALLEGRO_FONT *font = font_manager.main_font_small;

    // If the score needs to be drawn on one line
    if (one_line) {
        const std::string label_with_space   = std::string(label) + " ";

        const char *score_label_string = label_with_space.c_str();
        const char *score_value_string = std::to_string(score).c_str();

        // Calculating the total width of the two strings combined
        const int score_label_width = al_get_text_width(font, score_label_string);
        const int score_value_width = al_get_text_width(font, score_value_string);
        const int score_total_width = score_label_width + score_value_width;

        // Calculating the resulting padding of the score text for the X axis
        const float final_padding_x = position.x - static_cast<float>(score_total_width * 0.5);

        // Drawing the score label and value
        al_draw_text(font, label_color, final_padding_x, position.y, ALLEGRO_ALIGN_LEFT, score_label_string);
        al_draw_text(font, value_color, final_padding_x + static_cast<float>(score_label_width), position.y,
                     ALLEGRO_ALIGN_LEFT, score_value_string);
    }
    // If the score can be drawn on two separate lines (one for the label, one for the value)
    else {
        static constexpr int score_spacing = 10;

        const char *score_value_string = std::to_string(score).c_str();

        // Drawing the score label and value
        al_draw_text(font, label_color, position.x, position.y, ALLEGRO_ALIGN_CENTER, label.c_str());
        al_draw_text(font, value_color, position.x, position.y + MAIN_FONT_SIZE_SMALL + score_spacing,
                     ALLEGRO_ALIGN_CENTER, score_value_string);
    }
}

bool intersect_AABB_AABB(const Vector2f source_origin, const Vector2f source_size,
                         const Vector2f target_origin, const Vector2f target_size,
                         Vector2f &     intersection_normal) {
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

    // Calculating the distance of the overlap on the two axes
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
