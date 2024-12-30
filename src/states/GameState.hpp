#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include "../core/FontManager.hpp"

#include <allegro5/allegro.h>

class GameStateManager;

class GameState {
protected:
    GameStateManager *game_state_manager;

public:
    explicit GameState(GameStateManager *_game_state_manager) : game_state_manager(_game_state_manager) {}

    virtual ~GameState() = default;

    virtual void update() = 0;

    virtual void input(const ALLEGRO_MOUSE_STATE &, const ALLEGRO_MOUSE_STATE &, ALLEGRO_EVENT_TYPE, int) = 0;

    virtual void render(const FontManager &) const = 0;
};

#endif
