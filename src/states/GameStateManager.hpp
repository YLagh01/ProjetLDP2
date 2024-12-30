#ifndef GAMESTATEMANAGER_HPP
#define GAMESTATEMANAGER_HPP

#include "GameState.hpp"

#include <memory>

class GameStateManager final {
protected:
    std::unique_ptr<GameState> current_state;

public:
    ~GameStateManager() = default;

    void update_state(std::unique_ptr<GameState>);

    void update() const;

    void input(const ALLEGRO_MOUSE_STATE &, const ALLEGRO_MOUSE_STATE &, ALLEGRO_EVENT_TYPE, int) const;

    void render(const FontManager &) const;
};

#endif
