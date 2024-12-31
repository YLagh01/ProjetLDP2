/*
 * INFO-F202 (2024 - 2025)
 * Written with ❤︎ by Yassir Laghmouchi & Nabil El Muhur @ ULB
 */

#ifndef FONTMANAGER_HPP
#define FONTMANAGER_HPP

#include <allegro5/allegro_font.h>

static constexpr int MAIN_FONT_SIZE_SMALL = 16;
static constexpr int MAIN_FONT_SIZE_BIG   = 64;

class FontManager {
public:
    FontManager();

    ALLEGRO_FONT *main_font_small;
    ALLEGRO_FONT *secondary_font_small;

    ALLEGRO_FONT *main_font_big;
    ALLEGRO_FONT *secondary_font_big;
};

#endif
