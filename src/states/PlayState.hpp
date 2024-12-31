/*
 * INFO-F202 (2024 - 2025)
 * Written with ❤︎ by Yassir Laghmouchi & Nabil El Muhur @ ULB
 */

#ifndef GAMEORCHESTRA_HPP
#define GAMEORCHESTRA_HPP

#include "GameState.hpp"

#include "../objects/Brick.hpp"
#include "../objects/Ball.hpp"
#include "../objects/Plate.hpp"

#include <vector>
#include <memory>

class PlayState final : public GameState {
public:
    PlayState(GameStateManager *_game_state_manager, const SpriteManager &_sprite_manager);

    void update() override;

    void input(const ALLEGRO_MOUSE_STATE &, ALLEGRO_EVENT_TYPE, int) override;

    void render(const FontManager &) const override;

private:
    // Gameplay variables declarations
    bool game_started = false; // The game is considered "started" when the player moves the plate the first time

    uint8_t lives_remaining = 3;

    int score      = 0;
    int high_score = 0;

    bool mouse_control_mode = false;

    // Game objects declarations
    std::vector<std::shared_ptr<Brick> > bricks;

    Ball ball;

    Plate plate;

    // Functions declarations
    void setup_plate_and_ball();

    void init_bricks();

    void draw_health_bar() const;

    void check_ball_collisions();

    void key_down(int);

    void key_up(int);

    static int read_high_score();

    void write_high_score(bool) const;
};

#endif
