/*
 * INFO-F202 (2024 - 2025)
 * Written with ❤︎ by Yassir Laghmouchi & Nabil El Muhur @ ULB
 */

#include "Brick.hpp"

#include <unordered_map>

// Map of each brick type and its information (color, points bonus)
static const std::unordered_map<const BRICK_TYPE, const BrickTypeData> brick_type_data_map = {
    {BRICK_TYPE::WHITE  , {al_map_rgb(255, 255, 255), 50 , 1}},
    {BRICK_TYPE::ORANGE , {al_map_rgb(252, 139, 0  ), 60 , 1}},
    {BRICK_TYPE::CYAN   , {al_map_rgb(17 , 212, 212), 70 , 1}},
    {BRICK_TYPE::GREEN  , {al_map_rgb(84 , 252, 0  ), 80 , 1}},
    {BRICK_TYPE::RED    , {al_map_rgb(255, 0  , 0  ), 90 , 1}},
    {BRICK_TYPE::BLUE   , {al_map_rgb(0  , 145, 255), 100, 1}},
    {BRICK_TYPE::MAGENTA, {al_map_rgb(252, 0  , 185), 110, 1}},
    {BRICK_TYPE::YELLOW , {al_map_rgb(252, 218, 0  ), 120, 1}},
    {BRICK_TYPE::SILVER , {al_map_rgb(255, 255, 255), 200, 2}},
    {BRICK_TYPE::GOLDEN , {al_map_rgb(255, 255, 255), 0  , 0}}
};

Brick::Brick(SpriteManager _sprite_manager, const Vector2f _position, const BRICK_TYPE _brick_type):
    GameObject(nullptr, _position, Vector2f{}, Vector2f{BRICK_WIDTH, BRICK_HEIGHT}, 0),
    sprite_manager(_sprite_manager),
    brick_type(_brick_type),
    brick_type_data(brick_type_data_map.at(_brick_type)),
    hits_needed(brick_type_data.hits_needed) {

    // Handling special brick sprites
    if (brick_type == BRICK_TYPE::SILVER) {
        bitmap = sprite_manager.brick_silver_bitmap;
    }
    else if (brick_type == BRICK_TYPE::GOLDEN) {
        bitmap = sprite_manager.brick_golden_bitmap;
    }
    else {
        bitmap = sprite_manager.brick_bitmap;
    }
}

BRICK_TYPE Brick::get_brick_type() const {
    return brick_type;
}

BrickTypeData Brick::get_brick_type_data() const {
    return brick_type_data;
}

BRICK_TYPE Brick::get_brick_type_from_index(const int index) {
    return static_cast<BRICK_TYPE>(index % brick_type_data_map.size());
}

int Brick::get_hits_needed() const {
    return hits_needed;
}

void Brick::set_hits_needed(const int _hits_needed) {
    hits_needed = _hits_needed;
}

void Brick::draw() const {
    al_draw_tinted_bitmap(bitmap, brick_type_data.color, position.x, position.y, 0);
}
