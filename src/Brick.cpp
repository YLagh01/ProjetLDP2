#include "Brick.hpp"

#include <unordered_map>

#include "Common.hpp"

static const std::unordered_map<const BRICK_TYPE, const BrickTypeData> brick_type_data_map = {
    {BRICK_TYPE::WHITE  , {al_map_rgb(255, 255, 255), 50 }},
    {BRICK_TYPE::ORANGE , {al_map_rgb(252, 139, 0  ), 60 }},
    {BRICK_TYPE::CYAN   , {al_map_rgb(17 , 212, 212), 70 }},
    {BRICK_TYPE::GREEN  , {al_map_rgb(84 , 252, 0  ), 80 }},
    {BRICK_TYPE::RED    , {al_map_rgb(255, 0  , 0  ), 90 }},
    {BRICK_TYPE::BLUE   , {al_map_rgb(0  , 145, 255), 100}},
    {BRICK_TYPE::MAGENTA, {al_map_rgb(252, 0  , 185), 110}},
    {BRICK_TYPE::YELLOW , {al_map_rgb(252, 218, 0  ), 120}},
    {BRICK_TYPE::SILVER , {al_map_rgb(167, 174, 176), 200}},
    {BRICK_TYPE::GOLDEN , {al_map_rgb(242, 168, 31 ), 0  }}
};

Brick::Brick(const Vector2f _position, const Vector2f _direction, const float _speed,
             const BRICK_TYPE _brick_type): GameObject(_position, _direction, _speed),
                                      brick_type_data(brick_type_data_map.find(_brick_type)->second) {
}

BrickTypeData Brick::get_brick_type_data() const {
    return brick_type_data;
}

BRICK_TYPE Brick::get_brick_type_from_index(const int index) {
    return static_cast<BRICK_TYPE>(index % brick_type_data_map.size());
}
