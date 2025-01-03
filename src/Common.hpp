/*
 * INFO-F202 (2024 - 2025)
 * Written with ❤︎ by Yassir Laghmouchi & Nabil El Muhur @ ULB
 */

#ifndef COMMON_HPP
#define COMMON_HPP

#include "core/FontManager.hpp"

#include <string>

struct Vector2f {
    float x;
    float y;
};

// Display constants
static constexpr int    WINDOW_WIDTH     = 806;
static constexpr int    WINDOW_HEIGHT    = 890;
static constexpr double TARGET_FRAMERATE = 60;

static constexpr int BORDERS_SIZE = 29;

// Vector constants
// Considering the cartesian coordinates origin (0, 0) is at the top left of the display
static constexpr Vector2f NULL_VECTOR   = { 0,  0};
static constexpr Vector2f LEFT_VECTOR   = {-1,  0};
static constexpr Vector2f RIGHT_VECTOR  = { 1,  0};
static constexpr Vector2f UP_VECTOR     = { 0, -1};
static constexpr Vector2f BOTTOM_VECTOR = { 0,  1};

// Color constants
static const ALLEGRO_COLOR white_color = al_map_rgb(255, 255, 255);

// Stage constants
static constexpr int STAGES_COUNT = 7;

// Path constants
static const std::string HIGH_SCORE_PATH = "res/player_data/high_score.txt";

// Bricks constants
static constexpr float BRICK_WIDTH  = 53.55f;
static constexpr float BRICK_HEIGHT = 29.0f;

static constexpr int BRICKS_Y_PADDING = 100 + BORDERS_SIZE; // The Y-axis padding of the bricks

// Plate constants
static constexpr float PLATE_Y_PADDING = 140;
static constexpr float PLATE_SPEED     = 9.0;

// Ball constants
static constexpr float BALL_SPEED = 10.0;

// Powerups constants
static constexpr float POWERUP_FALL_SPEED = 4.0;

static constexpr float LASER_WIDTH  = 15.0;
static constexpr float LASER_HEIGHT = 25.0;

static constexpr long BALL_RELEASE_AFTER_MS = 5 * 1000; // Time the ball gets released after being caught (in milliseconds)

static constexpr long  SLOW_POWERUP_DURATION_MS      = 5 * 1000; // The duration of each slow powerup (in milliseconds)
static constexpr float SLOW_POWERUP_REDUCTION_FACTOR = 0.7;      // Slowness factor applied to the ball speed by the slow powerups

enum class POWERUP_TYPE {
    NONE, LASER, ENLARGE, CATCH, SLOW, DISRUPT, PLAYER
};

// Laser constants
static constexpr float LASER_SPEED = 10.0;

// Functions declarations
long current_time_milliseconds();

void draw_score(const FontManager &, int, const Vector2f &, const std::string &, bool);

#endif
