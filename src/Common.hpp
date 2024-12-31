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

// Math constants
static constexpr double EPS = 1e-2; // epsilon value

// Path constants
static const std::string HIGH_SCORE_PATH = "../res/player_data/high_score.txt";

// Display constants
static constexpr int    WINDOW_WIDTH     = 806;
static constexpr int    WINDOW_HEIGHT    = 890;
static constexpr double TARGET_FRAMERATE = 60;

static constexpr int BORDERS_SIZE = 29;

// Ball constants
static constexpr float BALL_DIAMETER = 20.0;
static constexpr float BALL_SPEED    = 10.0;

// Bricks constants
static constexpr int BRICK_ROWS    = 8;
static constexpr int BRICK_COLUMNS = 14;

static constexpr float BRICK_WIDTH  = 53.55f;
static constexpr float BRICK_HEIGHT = 29.0f;

static constexpr int BRICKS_Y_PADDING = 100 + BORDERS_SIZE; // The Y-axis padding of the bricks

// Plate constants
static constexpr int PLATE_WIDTH  = 115;
static constexpr int PLATE_HEIGHT = 29;

static constexpr float PLATE_SPEED = 9.0;

// Functions declarations
int8_t sign(float);

void draw_score(const FontManager &, int, const Vector2f &, const std::string &, bool);

bool intersect_AABB_AABB(Vector2f, Vector2f, Vector2f, Vector2f, Vector2f &);

#endif
