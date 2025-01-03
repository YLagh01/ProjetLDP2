/*
 * INFO-F202 (2024 - 2025)
 * Written with ❤︎ by Yassir Laghmouchi & Nabil El Muhur @ ULB
 */

#include "GameOverState.hpp"

#include "../Common.hpp"

#include "GameStateManager.hpp"
#include "PlayState.hpp"

#include <string>

GameOverState::GameOverState(GameStateManager *_game_state_manager, const SpriteManager &_sprite_manager,
    const int _final_score, const int _current_stage_index, const bool _game_won):
    GameState(_game_state_manager, _sprite_manager),
    game_won(_game_won), final_score(_final_score), current_stage_index(_current_stage_index) {
}

void GameOverState::update() {
}

void GameOverState::input(const ALLEGRO_MOUSE_STATE &mouse_state, const ALLEGRO_EVENT_TYPE event, const int keycode) {
    (void) mouse_state;
    (void) keycode;

    if (event == ALLEGRO_EVENT_KEY_DOWN) {
        // Advancing to the next stage only if the player has won, otherwise going back to the first stage
        const int next_stage_index = game_won ? (current_stage_index + 1) % STAGES_COUNT : 0;
        game_state_manager->update_current_state(std::make_unique<PlayState>(game_state_manager, sprite_manager, next_stage_index));
    }
}

void GameOverState::render(const FontManager &font_manager) const {
    // Using ternary operators to keep the "const" keyword
    const ALLEGRO_COLOR game_over_color = game_won ? al_map_rgb(252, 218, 0) : al_map_rgb(255, 0, 0);
    const std::string  &game_over_text  = game_won ? "VICTORY" : "DEFEAT";

    static const ALLEGRO_COLOR press_any_color = al_map_rgb(128, 128, 128);

    // Drawing the game over text
    al_draw_text(font_manager.main_font_big, game_over_color, WINDOW_WIDTH * 0.5,
                 WINDOW_HEIGHT * 0.5 - MAIN_FONT_SIZE_BIG, ALLEGRO_ALIGN_CENTER, game_over_text.c_str());

    // Drawing the "press any key to continue" text
    static const std::string press_any_text = "PRESS ANY KEY TO START";
    al_draw_text(font_manager.main_font_small, press_any_color, WINDOW_WIDTH * 0.5,
                 WINDOW_HEIGHT * 0.5 + MAIN_FONT_SIZE_BIG, ALLEGRO_ALIGN_CENTER, press_any_text.c_str());

    // Drawing the score
    static const std::string score_label = "SCORE";
    draw_score(font_manager, final_score, Vector2f{WINDOW_WIDTH * 0.5, WINDOW_HEIGHT * 0.5 + MAIN_FONT_SIZE_SMALL * 6.0}, score_label, true);
}
