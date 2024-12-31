/*
 * INFO-F202 (2024 - 2025)
 * Written with ❤︎ by Yassir Laghmouchi & Nabil El Muhur @ ULB
 */

#ifndef SPRITEMANAGER_HPP
#define SPRITEMANAGER_HPP

#include <allegro5/bitmap.h>

class SpriteManager {
public:
    SpriteManager();

    // Background
    ALLEGRO_BITMAP *background_bitmap;

    // Health bar
    ALLEGRO_BITMAP *health_bar_full;
    ALLEGRO_BITMAP *health_bar_two_left;
    ALLEGRO_BITMAP *health_bar_one_left;

    // Bricks
    ALLEGRO_BITMAP *brick_bitmap;
    ALLEGRO_BITMAP *brick_silver_bitmap;
    ALLEGRO_BITMAP *brick_silver_low_bitmap;
    ALLEGRO_BITMAP *brick_golden_bitmap;

    // Plates
    ALLEGRO_BITMAP *plate_small_bitmap;
    ALLEGRO_BITMAP *plate_big_bitmap;

    // Ball
    ALLEGRO_BITMAP *ball_bitmap;

    // Powerups
    ALLEGRO_BITMAP *laser_powerup_bitmap;
    ALLEGRO_BITMAP *laser_powerup_letter_bitmap;

    ALLEGRO_BITMAP *enlarge_powerup_bitmap;
    ALLEGRO_BITMAP *enlarge_powerup_letter_bitmap;

    ALLEGRO_BITMAP *catch_powerup_bitmap;
    ALLEGRO_BITMAP *catch_powerup_letter_bitmap;

    ALLEGRO_BITMAP *slow_powerup_bitmap;
    ALLEGRO_BITMAP *slow_powerup_letter_bitmap;

    ALLEGRO_BITMAP *disrupt_powerup_bitmap;
    ALLEGRO_BITMAP *disrupt_powerup_letter_bitmap;

    ALLEGRO_BITMAP *player_powerup_bitmap;
    ALLEGRO_BITMAP *player_powerup_letter_bitmap;
};

#endif