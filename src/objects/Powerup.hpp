/*
 * INFO-F202 (2024 - 2025)
 * Written with ❤︎ by Yassir Laghmouchi & Nabil El Muhur @ ULB
 */

#ifndef POWERUP_HPP
#define POWERUP_HPP

#include "../core/GameObject.hpp"
#include "../core/SpriteManager.hpp"

#include "Plate.hpp"

#include <unordered_map>

class Ball;

struct PowerupSprites {
    ALLEGRO_BITMAP *object_bitmap;
    ALLEGRO_BITMAP *letter_bitmap;
};

static const std::unordered_map<std::string, const POWERUP_TYPE> code_to_powerup_type = {
    {"L", POWERUP_TYPE::LASER   },
    {"E", POWERUP_TYPE::ENLARGE },
    {"C", POWERUP_TYPE::CATCH   },
    {"S", POWERUP_TYPE::SLOW    },
    {"D", POWERUP_TYPE::DISRUPT },
    {"P", POWERUP_TYPE::PLAYER  }
};

std::unordered_map<const POWERUP_TYPE, const PowerupSprites> get_powerup_bitmaps(const SpriteManager &);

class Powerup : public GameObject {
public:
    Powerup(const SpriteManager &_sprite_manager, Vector2f _position, POWERUP_TYPE _type);

    POWERUP_TYPE get_type() const;

    bool has_type(POWERUP_TYPE) const;

    void on_activation(Plate &, uint8_t &) const;

    void on_deactivation(Plate &, Ball &) const;

private:
    SpriteManager sprite_manager;

    POWERUP_TYPE type;
};

#endif
