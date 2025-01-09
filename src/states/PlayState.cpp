/*
 * INFO-F202 (2024 - 2025)
 * Written with ❤︎ by Yassir Laghmouchi & Nabil El Muhur @ ULB
 */

#include "PlayState.hpp"

#include "GameStateManager.hpp"
#include "GameOverState.hpp"

#include "../core/StageManager.hpp"
#include "../core/HighScoreManager.hpp"

/************************************/
/*         CLASS DEFINITION         */
/************************************/

PlayState::PlayState(GameStateManager *_game_state_manager, const SpriteManager &_sprite_manager,
                     const int _stage_index):
                     GameState(_game_state_manager, _sprite_manager),
                     stage_index(_stage_index),
                     plate(sprite_manager.plate_small_bitmap, Vector2f{}, Vector2f{}, PLATE_SPEED),
                     ball(sprite_manager, Vector2f{}, Vector2f{}, BALL_SPEED) {
    // Setting up the plate and ball
    setup_plate_and_ball();

    // Initialising the stage to set the background image and spawn the bricks and powerups
    init_stage(sprite_manager, stage_index, background, bricks);

    // Reading the high score from the player data file
    high_score = read_high_score();
}

void PlayState::setup_plate_and_ball() {
    // Setting the plate's size to match its sprite
    plate.set_size(Vector2f{
        static_cast<float>(al_get_bitmap_width(plate.get_bitmap())),
        static_cast<float>(al_get_bitmap_height(plate.get_bitmap()))
    });

    // Setting the plate's initial position
    plate.set_position(Vector2f{(WINDOW_WIDTH - plate.get_size().x) / 2, WINDOW_HEIGHT - PLATE_Y_PADDING});

    // Setting the ball's initial position and direction
    ball.set_position(Vector2f{
        static_cast<float>((WINDOW_WIDTH - ball.get_size().x) * 0.5), plate.get_position().y - ball.get_size().y
    });
    ball.set_direction(UP_VECTOR);
}

/************************************/
/*            UPDATE CODE           */
/************************************/

void PlayState::update() {
    // If the game hasn't started yet (if the player hasn't moved the plate), don't update game objects
    if (!game_started) {
        return;
    }

    // Handling powerups updates
    if (active_powerup != nullptr) {
        active_powerup->on_update(bricks, plate, ball, clone_balls, powerups, active_powerup, active_slow_powerups,
                                  score, mouse_control_mode);
    }

    // Moving the ball with its own speed and direction if it wasn't caught by the plate
    if (!ball.caught) {
        ball.move();
    }
    // Handling the ball's collisions
    ball.handle_collisions(bricks, plate, powerups, active_powerup, score);

    // Moving the plate and checking for collisions with the stage's walls
    if (!plate.check_collisions_walls() && !mouse_control_mode) {
        plate.move();
    }

    // Resetting the plate's direction if the inputs are neutral
    if (!plate.get_moving_left() && !plate.get_moving_right()) {
        plate.set_direction(NULL_VECTOR);
    }

    // Handling powerups collisions with the plate
    Powerup::handle_collisions_plate(powerups, active_powerup, active_slow_powerups, plate, ball, clone_balls,
                                     lives_remaining);

    // Handling laser powerup updates
    for (const auto &laser: lasers) {
        if (laser != nullptr) {
            laser->on_update(lasers, bricks, powerups, active_powerup, score);
        }
    }

    // If the main ball goes below the plate's height
    if (ball.get_position().y > plate.get_position().y + plate.get_size().y) {
        lives_remaining--;

        if (lives_remaining <= 0) {
            // Game over, defeat (no lives remaining)
            write_high_score(score, high_score, false);
            game_state_manager->update_current_state(
                std::make_unique<GameOverState>(game_state_manager, sprite_manager, score, stage_index, false));
            return;
        } else {
            // Lost one life, resetting the plate and ball
            setup_plate_and_ball();
            game_started = false;

            // Deactivating the active powerup on the player's death
            if (active_powerup != nullptr) {
                active_powerup->on_deactivation(plate, ball, active_slow_powerups);
            }
            active_powerup = nullptr;

            // Removing all clone balls if the player loses a life
            clone_balls.assign(0, nullptr);
        }
    }

    bool has_won = true;

    // If all the non-golden bricks have been destroyed
    for (const auto &brick: bricks) {
        if (brick->get_type() != BRICK_TYPE::GOLDEN) {
            has_won = false;
        }
    }

    // Game over, victory
    if (has_won) {
        write_high_score(score, high_score, false);
        game_state_manager->update_current_state(
            std::make_unique<GameOverState>(game_state_manager, sprite_manager, score, stage_index, true));
        return;
    }

    // Updating the high score if the current score is greater
    if (score > high_score) {
        high_score = score;
    }
}

/************************************/
/*            INPUT CODE            */
/************************************/

void PlayState::input(const ALLEGRO_MOUSE_STATE &mouse_state, const ALLEGRO_EVENT_TYPE event, const int keycode) {
    // Starting the game on the first plate movement from either keyboard inputs or the left click
    if ((event == ALLEGRO_EVENT_KEY_DOWN && (
             keycode == ALLEGRO_KEY_A || keycode == ALLEGRO_KEY_Q ||
             keycode == ALLEGRO_KEY_P || keycode == ALLEGRO_KEY_D
         ))
        || al_mouse_button_down(&mouse_state, 1)) {
        if (!game_started) {
            game_started = true;
        }
    }

    if (al_mouse_button_down(&mouse_state, 1) && !mouse_control_mode) {
        // Enter mouse plate control with left click
        mouse_control_mode = true;
    } else if (al_mouse_button_down(&mouse_state, 2) && mouse_control_mode) {
        // Leave mouse plate control with right click (back to keyboard inputs)
        mouse_control_mode = false;
    }

    // If the user is in mouse plate control mode, set the plate's X position to the mouse's
    if (mouse_control_mode && game_started) {
        plate.set_position(Vector2f{
            static_cast<float>(mouse_state.x - plate.get_size().x * 0.5), plate.get_position().y
        });

        // If the ball was caught by the plate, set the ball's X position to the mouse's
        if (ball.caught) {
            ball.set_position(Vector2f{
                static_cast<float>(mouse_state.x), ball.get_position().y
            });
        }
    }

    // Handling keyboard inputs
    if (event == ALLEGRO_EVENT_KEY_DOWN) {
        key_down(keycode);
    } else if (event == ALLEGRO_EVENT_KEY_UP) {
        key_up(keycode);
    }

    // Handling powerups keyboard inputs
    if (active_powerup != nullptr && game_started) {
        active_powerup->on_input(keycode, plate, ball, lasers);
    }
}

// Key codes are documented here: https://www.allegro.cc/manual/5/keyboard.html
void PlayState::key_down(const int keycode) {
    // Called when a key is pressed
    switch (keycode) {
        // F1 key (reset high score)
        case ALLEGRO_KEY_F1: {
            high_score = 0;
            write_high_score(score, high_score, true);
            break;
        }
        // F2 and F3 key (cycle through the stages)
        case ALLEGRO_KEY_F2:
        case ALLEGRO_KEY_F3: {
            // Using modulo (%) to cycle through the stages (if we increment the last stage's index, it points to the first stage)
            const int stage_index_increment = keycode == ALLEGRO_KEY_F2 ? -1 + STAGES_COUNT : 1;
            const int next_stage_index      = (stage_index + stage_index_increment) % STAGES_COUNT;
            // Updating the play state to load the next stage
            game_state_manager->update_current_state(
                std::make_unique<PlayState>(game_state_manager, sprite_manager, next_stage_index));
            break;
        }
        // Left key (move plate to the left)
        case ALLEGRO_KEY_A:
        case ALLEGRO_KEY_Q: {
            if (!mouse_control_mode) {
                plate.set_direction(LEFT_VECTOR);
                plate.set_moving_left(true);
            }
            break;
        }
        // Right key (move plate to the right)
        case ALLEGRO_KEY_P:
        case ALLEGRO_KEY_D: {
            if (!mouse_control_mode) {
                plate.set_direction(RIGHT_VECTOR);
                plate.set_moving_right(true);
            }
            break;
        }
        default: break;
    }
}

void PlayState::key_up(const int keycode) {
    if (mouse_control_mode) {
        return;
    }
    // Called when a key is released
    switch (keycode) {
        // Left key (move plate to the left)
        case ALLEGRO_KEY_A:
        case ALLEGRO_KEY_Q:
            plate.set_moving_left(false);
            break;
        // Right key (move plate to the right)
        case ALLEGRO_KEY_P:
        case ALLEGRO_KEY_D:
            plate.set_moving_right(false);
            break;
        default: break;
    }
}

/************************************/
/*            RENDER CODE           */
/************************************/

void PlayState::render(const FontManager &font_manager) const {
    // Drawing the background image
    al_draw_bitmap(background, 0, 0, ALLEGRO_FLIP_HORIZONTAL & ALLEGRO_FLIP_VERTICAL);

    // Drawing the bricks
    Brick::draw_bricks(sprite_manager, bricks);

    // Drawing the plate
    plate.draw();

    for (const auto &clone_ball: clone_balls) {
        if (clone_ball != nullptr) {
            // Drawing the clone balls with a darker tint to differentiate them from the main ball
            al_draw_tinted_bitmap(clone_ball->get_bitmap(), al_map_rgb(180, 180, 180), clone_ball->get_position().x,
                                  clone_ball->get_position().y, 0);
        }
    }
    // Drawing the main ball
    ball.draw();

    // Drawing the powerups
    for (auto &powerup: powerups) {
        if (powerup != nullptr) {
            powerup->draw();
        }
    }

    // Drawing the lasers
    for (auto &laser: lasers) {
        if (laser != nullptr) {
            laser->draw();
        }
    }

    // Drawing the health bar
    const auto health_bar_sprite_it = sprite_manager.health_bar_sprite_map.find(lives_remaining);
    if (health_bar_sprite_it != sprite_manager.health_bar_sprite_map.end()) {
        al_draw_bitmap(health_bar_sprite_it->second, 0,
                       static_cast<float>(WINDOW_HEIGHT - al_get_bitmap_height(health_bar_sprite_it->second)), 0);
    }

    // Drawing current and high scores
    static constexpr float top_text_padding = BORDERS_SIZE + MAIN_FONT_SIZE_SMALL;

    draw_score(font_manager, score, Vector2f{BORDERS_SIZE * 4, top_text_padding}, "SCORE", false);
    draw_score(font_manager, high_score, Vector2f{WINDOW_WIDTH - BORDERS_SIZE * 4, top_text_padding}, "HIGHSCORE",
               false);
    // Drawing the current stage index
    const std::string stage_string = "STAGE " + std::to_string(stage_index + 1);
    al_draw_text(font_manager.secondary_font_small, white_color, WINDOW_WIDTH * 0.5, top_text_padding,
                 ALLEGRO_ALIGN_CENTER, stage_string.c_str());
}
