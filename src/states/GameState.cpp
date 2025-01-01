/*
 * INFO-F202 (2024 - 2025)
 * Written with ❤︎ by Yassir Laghmouchi & Nabil El Muhur @ ULB
 */

#include "GameState.hpp"

void GameState::update() {
}

void GameState::input(const ALLEGRO_MOUSE_STATE &mouse_state, const ALLEGRO_EVENT_TYPE event, const int keycode) {
    (void) mouse_state;
    (void) event;
    (void) keycode;
}

void GameState::render(const FontManager &font_manager) const {
    (void) font_manager;
}
