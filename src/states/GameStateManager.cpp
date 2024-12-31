/*
 * INFO-F202 (2024 - 2025)
 * Written with ❤︎ by Yassir Laghmouchi & Nabil El Muhur @ ULB
 */

#include "GameStateManager.hpp"

void GameStateManager::update_state(std::unique_ptr<GameState> new_state) {
    current_state = std::move(new_state);
}

void GameStateManager::update() const {
    current_state->update();
}

void GameStateManager::input(const ALLEGRO_MOUSE_STATE &mouse_state, const ALLEGRO_EVENT_TYPE event, const int keycode) const {
    current_state->input(mouse_state, event, keycode);
}

void GameStateManager::render(const FontManager &font_manager) const {
    al_clear_to_color(al_map_rgb(0, 0, 0));

    current_state->render(font_manager);

    al_flip_display();
}
