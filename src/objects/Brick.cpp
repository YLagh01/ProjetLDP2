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
    hits_needed(brick_type_data.hits_needed),
    held_powerup(POWERUP_TYPE::NONE) {

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

int Brick::get_hits_needed() const {
    return hits_needed;
}

void Brick::set_hits_needed(const int _hits_needed) {
    hits_needed = _hits_needed;
}

POWERUP_TYPE Brick::get_held_powerup_type() const {
    return held_powerup;
}

void Brick::set_held_powerup_type(const POWERUP_TYPE _held_powerup_type) {
    held_powerup = _held_powerup_type;
}

void Brick::draw() const {
    // Drawing the brick's tinted bitmap
    al_draw_tinted_bitmap(bitmap, brick_type_data.color, position.x, position.y, 0);

    // Drawing the letter of the brick's held powerup on top of the brick's sprite if it holds one
    if (held_powerup != POWERUP_TYPE::NONE) {
        ALLEGRO_BITMAP *powerup_letter_bitmap = get_powerup_bitmaps(sprite_manager).at(held_powerup).letter_bitmap;
        al_draw_bitmap(powerup_letter_bitmap, position.x, position.y, 0);
    }
}

void Brick::draw_bricks(const SpriteManager &sprite_manager, const std::vector<std::shared_ptr<Brick> > &bricks) {
    for (const auto &brick: bricks) {
        brick->draw();

        // If the brick is silver, if it needs 1 hit to be destroyed and if it doesn't have the appropriate sprite yet, set it to the appropriate sprite
        if (brick->get_brick_type() == BRICK_TYPE::SILVER && brick->get_hits_needed() == 1 && brick->get_bitmap() != sprite_manager.brick_silver_low_bitmap) {
            brick->set_bitmap(sprite_manager.brick_silver_low_bitmap);
        }
    }
}

std::shared_ptr<Brick> Brick::intersects_brick(std::vector<std::shared_ptr<Brick> > &bricks, GameObject *object, Vector2f &brick_intersection_normal) {
    std::shared_ptr<Brick> intersected_brick = nullptr;

    // Finding the first intersected brick
    for (const auto & brick : bricks) {
        const bool intersects_brick = object->intersects(brick->get_position(), brick->get_size(), brick_intersection_normal);
        // Found an intersection
        if (intersects_brick) {
            intersected_brick = brick;
            break;
        }
    }
    return intersected_brick;
}

void Brick::on_brick_destroy(std::vector<std::shared_ptr<Brick> > &bricks, std::vector<std::shared_ptr<Powerup> > &powerups, int &score) {
    // Removing the brick if the hits needed to destroy it are equal to 1
    if (hits_needed == 1) {
        // Removing the brick from the bricks vector
        erase_game_object(bricks, this);

        // Updating the player score
        score += brick_type_data.points_bonus;

        // Spawning the brick's held powerup if it holds one
        if (held_powerup != POWERUP_TYPE::NONE) {
            Powerup powerup{sprite_manager, position, held_powerup};
            powerups.push_back(std::make_shared<Powerup>(powerup));
        }
    }
    // If the hits needed to remove the brick are over 1
    else if (hits_needed > 1) {
        // Decrementing the hits needed to destroy the brick
        hits_needed--;
    }
}
