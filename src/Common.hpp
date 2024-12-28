#ifndef COMMON_HPP
#define COMMON_HPP

#include <vector>

struct Vector2f {
    float x;
    float y;
};

// Display constants
static constexpr int    WINDOW_WIDTH     = 806;
static constexpr int    WINDOW_HEIGHT    = 890;
static constexpr double TARGET_FRAMERATE = 60;

static constexpr int BORDERS_SIZE = 29;

static constexpr int MAIN_FONT_SIZE = 16;

// Ball constants
static constexpr float BALL_RADIUS = 10.0;
static constexpr float BALL_SPEED  = 8.0;

// Bricks constants
static constexpr int BRICK_ROWS    = 8;
static constexpr int BRICK_COLUMNS = 14;

static constexpr float BRICK_WIDTH  = 53.55f;
static constexpr float BRICK_HEIGHT = 29.0f;

static constexpr int BRICKS_Y_PADDING = 100 + BORDERS_SIZE; // The Y-axis padding of the bricks

// Plate constants
static constexpr int PLATE_WIDTH  = 115;
static constexpr int PLATE_HEIGHT = 29;

static constexpr float PLATE_SPEED = 10.0;

// Functions definitions
float get_minimum(std::vector<float>);

float get_maximum(std::vector<float>);

float get_length(const std::vector<float> &);

float get_length(float);

bool intersect_circle_AABB(Vector2f, float, Vector2f, float, float, Vector2f &);

#endif
