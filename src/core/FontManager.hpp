#ifndef FONTMANAGER_HPP
#define FONTMANAGER_HPP

#include <allegro5/allegro_font.h>

static constexpr int MAIN_FONT_SIZE = 16;

class FontManager {
public:
    FontManager();

    ALLEGRO_FONT *main_font;
    ALLEGRO_FONT *secondary_font;
};

#endif
