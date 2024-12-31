/*
 * INFO-F202 (2024 - 2025)
 * Written with ❤︎ by Yassir Laghmouchi & Nabil El Muhur @ ULB
 */

#ifndef GAMEOVERSTATE_HPP
#define GAMEOVERSTATE_HPP

#include "GameState.hpp"

class GameOverState final : public GameState {
public:
    explicit GameOverState(GameStateManager *_game_state_manager, const SpriteManager &_sprite_manager, bool _game_won, int _final_score);

    void update() override;

    void input(const ALLEGRO_MOUSE_STATE &, ALLEGRO_EVENT_TYPE, int) override;

    void render(const FontManager &) const override;

private:
    bool game_won;

    int final_score;
};

#endif
