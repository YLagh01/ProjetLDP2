#include "FontManager.hpp"

#include <iostream>
#include <ostream>

FontManager::FontManager() {
    main_font      = al_load_font("../res/fonts/press_start_2p.ttf", MAIN_FONT_SIZE, 0);
    secondary_font = al_load_font("../res/fonts/retro_gaming.ttf", MAIN_FONT_SIZE, 0);
}
