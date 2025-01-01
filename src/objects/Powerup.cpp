/*
 * INFO-F202 (2024 - 2025)
 * Written with ❤︎ by Yassir Laghmouchi & Nabil El Muhur @ ULB
 */

#include "Powerup.hpp"

#include "Ball.hpp"

std::unordered_map<const POWERUP_TYPE, const PowerupSprites> get_powerup_bitmaps(const SpriteManager &sprite_manager) {
    return {
        {POWERUP_TYPE::LASER  , {sprite_manager.laser_powerup_bitmap  , sprite_manager.laser_powerup_letter_bitmap  }},
        {POWERUP_TYPE::ENLARGE, {sprite_manager.enlarge_powerup_bitmap, sprite_manager.enlarge_powerup_letter_bitmap}},
        {POWERUP_TYPE::CATCH  , {sprite_manager.catch_powerup_bitmap  , sprite_manager.catch_powerup_letter_bitmap  }},
        {POWERUP_TYPE::SLOW   , {sprite_manager.slow_powerup_bitmap   , sprite_manager.slow_powerup_letter_bitmap   }},
        {POWERUP_TYPE::DISRUPT, {sprite_manager.disrupt_powerup_bitmap, sprite_manager.disrupt_powerup_letter_bitmap}},
        {POWERUP_TYPE::PLAYER , {sprite_manager.player_powerup_bitmap , sprite_manager.player_powerup_letter_bitmap }}
    };
}

Powerup::Powerup(const SpriteManager &_sprite_manager, const Vector2f _position, const POWERUP_TYPE _type): GameObject(
        nullptr, _position, Vector2f{}, Vector2f{}, POWERUP_FALL_SPEED), sprite_manager(_sprite_manager), type(_type) {
    // Setting the corresponding sprite to the powerup
    set_bitmap(get_powerup_bitmaps(_sprite_manager).at(type).object_bitmap);

    // Fall direction
    direction = BOTTOM_VECTOR;

    // Setting the size of the object to the size of its sprite
    size = Vector2f{
        static_cast<float>(al_get_bitmap_width(bitmap)),
        static_cast<float>(al_get_bitmap_height(bitmap))
    };
}

POWERUP_TYPE Powerup::get_type() const {
    return type;
}

bool Powerup::has_type(const POWERUP_TYPE _type) const {
    return type == _type;
}

void Powerup::on_activation(Plate &plate, uint8_t &lives_remaining) const {
    switch (type) {
        case POWERUP_TYPE::ENLARGE: {
            plate.change_sprite(sprite_manager.plate_big_bitmap);
            break;
        }
        case POWERUP_TYPE::PLAYER: {
            if (lives_remaining < 3) {
                lives_remaining++;
            }
            break;
        }
        default:
            break;
    }
}

void Powerup::on_deactivation(Plate &plate, Ball &ball) const {
    switch (type) {
        case POWERUP_TYPE::ENLARGE:
            plate.change_sprite(sprite_manager.plate_small_bitmap);
            break;
        case POWERUP_TYPE::CATCH:
            ball.caught = false;
            break;
        default:
            break;
    }
}
