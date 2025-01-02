/*
 * INFO-F202 (2024 - 2025)
 * Written with ❤︎ by Yassir Laghmouchi & Nabil El Muhur @ ULB
 */

#include "Common.hpp"

#include <chrono>

long current_time_milliseconds() {
    // Yields the current time since epoch in milliseconds as a long value
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

void draw_score(const FontManager &font_manager, const int score, const Vector2f &position, const std::string &label,
                const bool one_line) {
    static const ALLEGRO_COLOR label_color = white_color;
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
        al_draw_text(font, value_color, position.x, position.y + static_cast<float>(al_get_font_line_height(font)) + score_spacing,
                     ALLEGRO_ALIGN_CENTER, score_value_string);
    }
}
