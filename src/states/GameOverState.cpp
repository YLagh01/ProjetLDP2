/*
 * INFO-F202 (2024 - 2025)
 * Written with ❤︎ by Yassir Laghmouchi & Nabil El Muhur @ ULB
 */

#include "GameOverState.hpp"

#include "../Common.hpp"

#include "GameStateManager.hpp"
#include "PlayState.hpp"

#include <string>
#include <memory>

GameOverState::GameOverState(GameStateManager *_game_state_manager, const SpriteManager &_sprite_manager, const bool _game_won, const int _final_score):
        GameState(_game_state_manager, _sprite_manager), game_won(_game_won), final_score(_final_score) {
}

void GameOverState::update() {
}

void GameOverState::input(const ALLEGRO_MOUSE_STATE &mouse_state, const ALLEGRO_EVENT_TYPE event, const int keycode) {
    if (event == ALLEGRO_EVENT_KEY_DOWN) {
        game_state_manager->update_state(std::make_unique<PlayState>(game_state_manager, sprite_manager));
    }
}

void GameOverState::render(const FontManager &font_manager) const {
    // Using ternary operators to keep the "const" keyword
    const ALLEGRO_COLOR game_over_color = game_won ? al_map_rgb(0, 255, 0) : al_map_rgb(255, 0, 0);
    const std::string  &game_over_text  = game_won ? "VICTORY" : "DEFEAT";

    // Drawing the game over text
    al_draw_text(font_manager.main_font_big, game_over_color, WINDOW_WIDTH * 0.5,
                 WINDOW_HEIGHT * 0.5 - MAIN_FONT_SIZE_BIG, ALLEGRO_ALIGN_CENTER, game_over_text.c_str());

    // Drawing the score
    draw_score(font_manager, final_score, Vector2f{WINDOW_WIDTH * 0.5, (WINDOW_HEIGHT + MAIN_FONT_SIZE_BIG) * 0.5}, "SCORE", true);

    // Drawing the "press any key to continue" text
    al_draw_text(font_manager.main_font_small, al_map_rgb(128, 128, 128), WINDOW_WIDTH * 0.5,
                 WINDOW_HEIGHT * 0.5 + MAIN_FONT_SIZE_BIG * 2, ALLEGRO_ALIGN_CENTER, "PRESS ANY KEY TO START");
}
