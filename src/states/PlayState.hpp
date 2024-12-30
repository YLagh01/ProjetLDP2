#ifndef GAMEORCHESTRA_HPP
#define GAMEORCHESTRA_HPP

#include "GameState.hpp"

#include "../core/Brick.hpp"
#include "../core/Ball.hpp"
#include "../core/Plate.hpp"

#include <vector>
#include <memory>

class PlayState final : public GameState {
public:
    explicit PlayState(GameStateManager *game_state_manager);

    void update() override;

    void input(const ALLEGRO_MOUSE_STATE &, const ALLEGRO_MOUSE_STATE &, ALLEGRO_EVENT_TYPE, int) override;

    void render(const FontManager &) const override;

private:
    bool mouse_control_mode = false;

    int score = 0;

    std::vector<std::shared_ptr<Brick> > bricks;

    Ball ball;

    Plate plate;

    ALLEGRO_BITMAP *background_bitmap;
    ALLEGRO_BITMAP *brick_bitmap;
    ALLEGRO_BITMAP *plate_bitmap;
    ALLEGRO_BITMAP *ball_bitmap;

    void init_bricks();

    void check_ball_collisions();

    void key_down(int);

    void key_up(int);
};

#endif
