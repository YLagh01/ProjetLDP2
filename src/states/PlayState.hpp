/*
 * INFO-F202 (2024 - 2025)
 * Written with ❤︎ by Yassir Laghmouchi & Nabil El Muhur @ ULB
 */

#ifndef GAMEORCHESTRA_HPP
#define GAMEORCHESTRA_HPP

#include "GameState.hpp"

#include "../objects/Brick.hpp"
#include "../objects/Plate.hpp"
#include "../objects/Ball.hpp"
#include "../objects/Laser.hpp"

#include <vector>
#include <memory>

class PlayState final : public GameState {
public:
    PlayState(GameStateManager *_game_state_manager, const SpriteManager &_sprite_manager, int _stage_index);

    void update() override;

    void input(const ALLEGRO_MOUSE_STATE &, ALLEGRO_EVENT_TYPE, int) override;

    void render(const FontManager &) const override;

    // Gameplay variables declarations
    uint8_t lives_remaining = 3;

    // Game objects declarations
    Plate plate;

    Ball ball;

    std::shared_ptr<Powerup> active_powerup;

private:
    // Stage variables declarations
    int stage_index;

    ALLEGRO_BITMAP *background = nullptr;

    // Gameplay variables declarations
    bool game_started = false; // The game is considered "started" when the player moves the plate the first time

    int score      = 0;
    int high_score = 0;

    bool mouse_control_mode = false;

    // Game objects declarations
    std::vector<std::shared_ptr<Brick> > bricks;

    std::vector<std::shared_ptr<Powerup> > powerups;

    std::vector<std::shared_ptr<Laser> > lasers;

    // Functions declarations
    void setup_plate_and_ball();

    void draw_health_bar() const;

    void key_down(int);

    void key_up(int);
};

#endif
