/*
 * INFO-F202 (2024 - 2025)
 * Written with ❤︎ by Yassir Laghmouchi & Nabil El Muhur @ ULB
 */

#ifndef POWERUP_HPP
#define POWERUP_HPP

#include "../core/GameObject.hpp"
#include "../core/SpriteManager.hpp"

#include "Laser.hpp"

#include <unordered_map>
#include <queue>

class Ball;

struct PowerupSprites {
    ALLEGRO_BITMAP *object_bitmap;
    ALLEGRO_BITMAP *letter_bitmap;
};

static const std::unordered_map<std::string, const POWERUP_TYPE> code_to_powerup_type = {
    {"L", POWERUP_TYPE::LASER  },
    {"E", POWERUP_TYPE::ENLARGE},
    {"C", POWERUP_TYPE::CATCH  },
    {"S", POWERUP_TYPE::SLOW   },
    {"D", POWERUP_TYPE::DISRUPT},
    {"P", POWERUP_TYPE::PLAYER }
};

std::unordered_map<const POWERUP_TYPE, const PowerupSprites> get_powerup_bitmaps(const SpriteManager &);

class Powerup : public GameObject {
public:
    Powerup(const SpriteManager &_sprite_manager, Vector2f _position, POWERUP_TYPE _type);

    POWERUP_TYPE get_type() const;

    bool has_type(POWERUP_TYPE) const;

    void on_activation(Plate &, Ball &, std::vector<std::shared_ptr<Ball> > &, std::vector<std::shared_ptr<Powerup> > &,
                       std::queue<long> &, uint8_t &) const;

    void on_deactivation(Plate &, Ball &, std::queue<long> &) const;

    void on_update(std::vector<std::shared_ptr<Brick> > &, const Plate &, Ball &, std::vector<std::shared_ptr<Ball> > &,
                   std::vector<std::shared_ptr<Powerup> > &, std::shared_ptr<Powerup> &, std::queue<long> &,
                   int &, bool) const;

    void on_input(int, const Plate &, Ball &, std::vector<std::shared_ptr<Laser> > &) const;

    static void handle_collisions_plate(std::vector<std::shared_ptr<Powerup> > &, std::shared_ptr<Powerup> &,
                                        std::queue<long> &, Plate &, Ball &, std::vector<std::shared_ptr<Ball> > &,
                                        uint8_t &);

private:
    SpriteManager sprite_manager;

    POWERUP_TYPE type;

    static float get_slowed_ball_speed(const std::queue<long> &);
};

#endif
