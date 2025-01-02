/*
 * INFO-F202 (2024 - 2025)
 * Written with ❤︎ by Yassir Laghmouchi & Nabil El Muhur @ ULB
 */

#include "Powerup.hpp"

#include "Ball.hpp"

std::unordered_map<const POWERUP_TYPE, const PowerupSprites> get_powerup_bitmaps(const SpriteManager &sprite_manager) {
    return {
        {POWERUP_TYPE::LASER  , {sprite_manager.laser_powerup_bitmap  , sprite_manager.laser_powerup_letter_bitmap  }},
        {POWERUP_TYPE::ENLARGE, {sprite_manager.enlarge_powerup_bitmap, sprite_manager.enlarge_powerup_letter_bitmap}},
        {POWERUP_TYPE::CATCH  , {sprite_manager.catch_powerup_bitmap  , sprite_manager.catch_powerup_letter_bitmap  }},
        {POWERUP_TYPE::SLOW   , {sprite_manager.slow_powerup_bitmap   , sprite_manager.slow_powerup_letter_bitmap   }},
        {POWERUP_TYPE::DISRUPT, {sprite_manager.disrupt_powerup_bitmap, sprite_manager.disrupt_powerup_letter_bitmap}},
        {POWERUP_TYPE::PLAYER , {sprite_manager.player_powerup_bitmap , sprite_manager.player_powerup_letter_bitmap }}
    };
}

Powerup::Powerup(const SpriteManager &_sprite_manager, const Vector2f _position, const POWERUP_TYPE _type): GameObject(
    nullptr, _position, Vector2f{}, Vector2f{}, POWERUP_FALL_SPEED), sprite_manager(_sprite_manager), type(_type) {
    // Setting the corresponding sprite to the powerup
    set_bitmap(get_powerup_bitmaps(_sprite_manager).at(type).object_bitmap);

    // Fall direction
    direction = BOTTOM_VECTOR;

    // Setting the size of the object to the size of its sprite
    size = Vector2f{
        static_cast<float>(al_get_bitmap_width(bitmap)),
        static_cast<float>(al_get_bitmap_height(bitmap))
    };
}

POWERUP_TYPE Powerup::get_type() const {
    return type;
}

bool Powerup::has_type(const POWERUP_TYPE _type) const {
    return type == _type;
}

void Powerup::on_activation(Plate &plate, Ball &ball, std::vector<std::shared_ptr<Ball> > &clone_balls,
                            std::vector<std::shared_ptr<Powerup> > &powerups, std::queue<long> &active_slow_powerups,
                            uint8_t &lives_remaining) const {
    switch (type) {
        case POWERUP_TYPE::ENLARGE:
            plate.change_sprite(sprite_manager.plate_big_bitmap);
            break;
        case POWERUP_TYPE::SLOW: {
            // Adding an active slow powerup to the queue and slowing down the ball's speed accordingly
            active_slow_powerups.push(current_time_milliseconds());
            ball.set_speed(get_slowed_ball_speed(active_slow_powerups));
            break;
        }
        case POWERUP_TYPE::DISRUPT: {
            if (clone_balls.empty()) {
                // Removing all falling powerups if the disrupt powerup is activated
                powerups = std::vector<std::shared_ptr<Powerup> >();

                // Spawning clone balls
                Ball clone_ball{sprite_manager, ball.get_position(), ball.get_direction(), ball.get_speed()};

                clone_balls.push_back(std::make_shared<Ball>(clone_ball));
                clone_balls.push_back(std::make_shared<Ball>(clone_ball));
            }
            break;
        }
        case POWERUP_TYPE::PLAYER: {
            // Adding one life to the player if the health bar isn't full
            if (lives_remaining < 3) {
                lives_remaining++;
            }
            break;
        }
        default:
            break;
    }
}

void Powerup::on_deactivation(Plate &plate, Ball &ball, std::queue<long> &active_slow_powerups) const {
    switch (type) {
        case POWERUP_TYPE::ENLARGE:
            plate.change_sprite(sprite_manager.plate_small_bitmap);
            break;
        case POWERUP_TYPE::SLOW: {
            // Resetting the ball's speed and emptying the active slow powerups queue
            ball.set_speed(BALL_SPEED);
            active_slow_powerups = std::queue<long>();
            break;
        }
        case POWERUP_TYPE::CATCH:
            ball.caught = false;
            break;
        default:
            break;
    }
}

void Powerup::on_update(std::vector<std::shared_ptr<Brick> > &bricks, const Plate &plate, Ball &ball,
                        std::vector<std::shared_ptr<Ball> > &clone_balls,
                        std::vector<std::shared_ptr<Powerup> > &powerups,
                        std::shared_ptr<Powerup> &active_powerup, std::queue<long> &active_slow_powerups,
                        int &score, const bool mouse_control_mode) const {

    // If the catch powerup is active and if the ball was caught
    if (type == POWERUP_TYPE::CATCH && ball.caught) {
        // Time elapsed since the ball was caught
        const long elapsed_time = current_time_milliseconds() - ball.caught_time;

        // Releasing the ball if enough time has passed since it was caught
        if (elapsed_time > BALL_RELEASE_AFTER_MS) {
            ball.caught = false;
        }
        else {
            // Moving the ball with the plate's speed and direction if there are no collisions in keyboard mode
            if (!plate.check_collisions_walls() && !mouse_control_mode) {
                ball.move(plate.get_speed(), plate.get_direction());
            }
        }
    }

    else if (type == POWERUP_TYPE::SLOW) {
        if (!active_slow_powerups.empty()) {
            // Time elapsed since the slow powerup is active
            const long elapsed_time = current_time_milliseconds() - active_slow_powerups.front();
            // If enough time has passed, remove the slow powerup from the queue and adjust the ball's speed accordingly
            if (elapsed_time > SLOW_POWERUP_DURATION_MS) {
                active_slow_powerups.pop();
                ball.set_speed(get_slowed_ball_speed(active_slow_powerups));
            }
        }
    }

    else if (type == POWERUP_TYPE::DISRUPT) {
        // If there are no clone balls left, the disrupt powerup is deactivated
        if (clone_balls.empty()) {
            active_powerup = nullptr;
            return;
        }

        // Handling updates for clone balls from the disrupt powerup
        for (const auto &clone_ball: clone_balls) {
            if (clone_ball != nullptr) {
                clone_ball->move();
                // Handling clone ball collisions
                clone_ball->handle_collisions(bricks, plate, powerups, active_powerup, score);
                // If the clone ball goes below the plate's height
                if (clone_ball->get_position().y >  plate.get_position().y + plate.get_size().y) {
                    // Removing it from the clone balls vector
                    erase_game_object(clone_balls, clone_ball.get());
                }
            }
        }
    }
}

void Powerup::on_input(const int keycode, const Plate &plate, Ball &ball,
                       std::vector<std::shared_ptr<Laser> > &lasers) const {
    if (keycode == ALLEGRO_KEY_SPACE) {
        // If the space bar is pressed
        if (type == POWERUP_TYPE::LASER) {
            // Spawning a laser object
            Laser::spawn_laser(sprite_manager, lasers, plate);
        }
        else if (type == POWERUP_TYPE::CATCH && ball.caught) {
            // Releasing the ball
            ball.caught = false;
        }
    }
}

void Powerup::handle_collisions_plate(std::vector<std::shared_ptr<Powerup> > &powerups,
                                      std::shared_ptr<Powerup> &active_powerup, std::queue<long> &active_slow_powerups,
                                      Plate &plate, Ball &ball, std::vector<std::shared_ptr<Ball> > &clone_balls,
                                      uint8_t &lives_remaining) {
    std::shared_ptr<Powerup> intersected_powerup = nullptr;

    for (const auto &powerup: powerups) {
        if (powerup != nullptr) {
            // Making powerups fall down
            powerup->move();

            // Removing the powerup object from the powerups vector if it falls outside the window's bounds
            if (powerup->get_position().y > WINDOW_HEIGHT) {
                erase_game_object(powerups, powerup.get());
            }

            // Checking for collisions of the powerups with the plate
            Vector2f   powerup_intersection_normal{};
            const bool intersects_powerup = plate.intersects(powerup->get_position(), powerup->get_size(),
                                                             powerup_intersection_normal);

            // Found a collision with a powerup
            if (intersects_powerup) {
                intersected_powerup = powerup;
            }
        }
    }

    // If there was a collision with a powerup
    if (intersected_powerup != nullptr) {
        // Removing the powerup object from the powerups vector
        erase_game_object(powerups, intersected_powerup.get());

        // Handling what happens on deactivation of the previous active powerup if there is one and if it's different from the new one
        if (active_powerup != nullptr && active_powerup->get_type() != intersected_powerup->get_type()) {
            active_powerup->on_deactivation(plate, ball, active_slow_powerups);
        }
        // Updating the active powerup
        active_powerup = intersected_powerup;
        // Handling what happens on activation of the new active powerup
        active_powerup->on_activation(plate, ball, clone_balls, powerups, active_slow_powerups, lives_remaining);
    }
}

float Powerup::get_slowed_ball_speed(const std::queue<long> &active_slow_powerups) {
    // Calculating the ball's slowed speed depending on the amount of active slow powerups
    // Avoiding divisions by zero using a ternary condition operator
    return active_slow_powerups.empty()
               ? BALL_SPEED
               : BALL_SPEED * SLOW_POWERUP_REDUCTION_FACTOR / static_cast<float>(active_slow_powerups.size());
}
