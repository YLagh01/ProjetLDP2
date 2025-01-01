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

// Vector constants
static constexpr Vector2f NULL_VECTOR   = { 0,  0};
static constexpr Vector2f LEFT_VECTOR   = {-1,  0};
static constexpr Vector2f RIGHT_VECTOR  = { 1,  0};
static constexpr Vector2f UP_VECTOR     = { 0, -1};
static constexpr Vector2f BOTTOM_VECTOR = { 0,  1};

// Stage constants
static constexpr int STAGES_COUNT = 4;

// Path constants
static const std::string HIGH_SCORE_PATH = "../res/player_data/high_score.txt";

// Display constants
static constexpr int    WINDOW_WIDTH     = 806;
static constexpr int    WINDOW_HEIGHT    = 890;
static constexpr double TARGET_FRAMERATE = 60;

static constexpr int BORDERS_SIZE = 29;

// Bricks constants
static constexpr int BRICK_ROWS    = 8;
static constexpr int BRICK_COLUMNS = 14;

static constexpr float BRICK_WIDTH  = 53.55f;
static constexpr float BRICK_HEIGHT = 29.0f;

static constexpr int BRICKS_Y_PADDING = 100 + BORDERS_SIZE; // The Y-axis padding of the bricks

// Plate constants
static constexpr float PLATE_SPEED = 9.0;

// Ball constants
static constexpr float BALL_SPEED            = 10.0;
static constexpr long  BALL_RELEASE_AFTER_MS = 5 * 1000; // Time the ball gets released after being caught (5 seconds in milliseconds)

// Powerups constants
static constexpr float POWERUP_FALL_SPEED = 6.0;

enum class POWERUP_TYPE {
    NONE, LASER, ENLARGE, CATCH, SLOW, DISRUPT, PLAYER
};

// Laser constants
static constexpr float LASER_SPEED = 10.0;

// Functions declarations
long current_time_milliseconds();

void draw_score(const FontManager &, int, const Vector2f &, const std::string &, bool);

#endif
