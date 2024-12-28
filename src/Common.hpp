#ifndef COMMON_HPP
#define COMMON_HPP

#include <vector>

struct Vector2f {
    float x;
    float y;
};

// Display constants
static constexpr int    WINDOW_WIDTH     = 560;
static constexpr int    WINDOW_HEIGHT    = 900;
static constexpr double TARGET_FRAMERATE = 60;

// Ball constants
static constexpr float BALL_RADIUS = 10.0;
static constexpr float BALL_SPEED  = 8.0;

// Bricks constants
static constexpr int BRICK_ROWS    = 8;
static constexpr int BRICK_COLUMNS = 14;

static constexpr int BRICK_WIDTH  = 40;
static constexpr int BRICK_HEIGHT = 25;

static constexpr int BRICKS_Y_PADDING = 100; // The Y-axis padding of the bricks

// Plate constants
static constexpr int PLATE_WIDTH  = 130;
static constexpr int PLATE_HEIGHT = 34;

static constexpr float PLATE_SPEED = 10.0;

// Functions definitions
float get_minimum(std::vector<float>);

float get_maximum(std::vector<float>);

float get_length(const std::vector<float> &);

float get_length(float);

bool intersect_circle_AABB(Vector2f, float, Vector2f, float, float, Vector2f &);

#endif
