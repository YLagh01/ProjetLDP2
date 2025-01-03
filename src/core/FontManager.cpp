/*
 * INFO-F202 (2024 - 2025)
 * Written with ❤︎ by Yassir Laghmouchi & Nabil El Muhur @ ULB
 */

#include "FontManager.hpp"

FontManager::FontManager() {
    main_font_small      = al_load_font("res/fonts/press_start_2p.ttf", MAIN_FONT_SIZE_SMALL, 0);
    secondary_font_small = al_load_font("res/fonts/retro_gaming.ttf", MAIN_FONT_SIZE_SMALL, 0);

    main_font_big      = al_load_font("res/fonts/press_start_2p.ttf", MAIN_FONT_SIZE_BIG, 0);
    secondary_font_big = al_load_font("res/fonts/retro_gaming.ttf", MAIN_FONT_SIZE_BIG, 0);
}
