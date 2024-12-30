#ifndef GAMEOVERSTATE_HPP
#define GAMEOVERSTATE_HPP

#include "GameState.hpp"

class GameOverState final : public GameState {
public:
    explicit GameOverState(GameStateManager *game_state_manager);

    void update() override;

    void input(const ALLEGRO_MOUSE_STATE &, const ALLEGRO_MOUSE_STATE &, ALLEGRO_EVENT_TYPE, int) override;

    void render(const FontManager &) const override;
};

#endif
