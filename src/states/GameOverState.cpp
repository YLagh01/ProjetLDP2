#include "GameOverState.hpp"

#include "../Common.hpp"

GameOverState::GameOverState(GameStateManager *game_state_manager): GameState(game_state_manager) {
}

void GameOverState::update() {
}

void GameOverState::input(const ALLEGRO_MOUSE_STATE &current_mouse_state,
                          const ALLEGRO_MOUSE_STATE &previous_mouse_state, const ALLEGRO_EVENT_TYPE event,
                          const int keycode) {
}

void GameOverState::render(const FontManager &font_manager) const {
    al_draw_text(font_manager.secondary_font, al_map_rgb(255, 0, 0), WINDOW_WIDTH * 0.5, WINDOW_HEIGHT * 0.5, ALLEGRO_ALIGN_CENTER, "DEFEAT");
}
