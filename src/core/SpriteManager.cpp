/*
 * INFO-F202 (2024 - 2025)
 * Written with ❤︎ by Yassir Laghmouchi & Nabil El Muhur @ ULB
 */

#include "SpriteManager.hpp"

#include <allegro5/bitmap_io.h>

SpriteManager::SpriteManager() {
    // Background
    background_0_bitmap = al_load_bitmap("../res/sprites/background/background_0.png");
    background_1_bitmap = al_load_bitmap("../res/sprites/background/background_1.png");
    background_2_bitmap = al_load_bitmap("../res/sprites/background/background_2.png");

    // Health bar
    health_bar_full_bitmap     = al_load_bitmap("../res/sprites/health_bar/health_bar_full.png");
    health_bar_two_left_bitmap = al_load_bitmap("../res/sprites/health_bar/health_bar_two_left.png");
    health_bar_one_left_bitmap = al_load_bitmap("../res/sprites/health_bar/health_bar_one_left.png");

    health_bar_sprite_map = {
        {3, health_bar_full_bitmap    },
        {2, health_bar_two_left_bitmap},
        {1, health_bar_one_left_bitmap}
    };

    // Bricks
    brick_bitmap            = al_load_bitmap("../res/sprites/objects/brick/brick.png");
    brick_silver_bitmap     = al_load_bitmap("../res/sprites/objects/brick/brick_silver.png");
    brick_silver_low_bitmap = al_load_bitmap("../res/sprites/objects/brick/brick_silver_low.png");
    brick_golden_bitmap     = al_load_bitmap("../res/sprites/objects/brick/brick_golden.png");

    // Plates
    plate_small_bitmap = al_load_bitmap("../res/sprites/objects/plate_small.png");
    plate_big_bitmap   = al_load_bitmap("../res/sprites/objects/plate_big.png");

    // Ball
    ball_bitmap = al_load_bitmap("../res/sprites/objects/ball.png");

    // Powerups
    laser_powerup_bitmap        = al_load_bitmap("../res/sprites/objects/powerup/laser_powerup.png");
    laser_powerup_letter_bitmap = al_load_bitmap("../res/sprites/objects/powerup/laser_powerup_letter.png");

    enlarge_powerup_bitmap        = al_load_bitmap("../res/sprites/objects/powerup/enlarge_powerup.png");
    enlarge_powerup_letter_bitmap = al_load_bitmap("../res/sprites/objects/powerup/enlarge_powerup_letter.png");

    catch_powerup_bitmap        = al_load_bitmap("../res/sprites/objects/powerup/catch_powerup.png");
    catch_powerup_letter_bitmap = al_load_bitmap("../res/sprites/objects/powerup/catch_powerup_letter.png");

    slow_powerup_bitmap        = al_load_bitmap("../res/sprites/objects/powerup/slow_powerup.png");
    slow_powerup_letter_bitmap = al_load_bitmap("../res/sprites/objects/powerup/slow_powerup_letter.png");

    disrupt_powerup_bitmap        = al_load_bitmap("../res/sprites/objects/powerup/disrupt_powerup.png");
    disrupt_powerup_letter_bitmap = al_load_bitmap("../res/sprites/objects/powerup/disrupt_powerup_letter.png");

    player_powerup_bitmap        = al_load_bitmap("../res/sprites/objects/powerup/player_powerup.png");
    player_powerup_letter_bitmap = al_load_bitmap("../res/sprites/objects/powerup/player_powerup_letter.png");

    // Laser
    laser_bitmap = al_load_bitmap("../res/sprites/objects/laser.png");
}
