/*
 * INFO-F202 (2024 - 2025)
 * Written with ❤︎ by Yassir Laghmouchi & Nabil El Muhur @ ULB
 */

#ifndef BRICK_HPP
#define BRICK_HPP

#include "../core/GameObject.hpp"
#include "../core/SpriteManager.hpp"

enum class BRICK_TYPE {
    WHITE, ORANGE, CYAN, GREEN, RED, BLUE, MAGENTA, YELLOW, SILVER, GOLDEN
};

struct BrickTypeData {
    ALLEGRO_COLOR color;
    int points_bonus;
    int hits_needed;
};

class Brick : public GameObject {
public:
    Brick(SpriteManager _sprite_manager, Vector2f _position, BRICK_TYPE _brick_type);

    BRICK_TYPE get_brick_type() const;

    BrickTypeData get_brick_type_data() const;

    static BRICK_TYPE get_brick_type_from_index(int);

    int get_hits_needed() const;

    void set_hits_needed(int _hits_needed);

    void draw() const;

private:
    SpriteManager sprite_manager;

    BRICK_TYPE brick_type;

    BrickTypeData brick_type_data;

    int hits_needed;
};

#endif
