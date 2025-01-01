/*
 * INFO-F202 (2024 - 2025)
 * Written with ❤︎ by Yassir Laghmouchi & Nabil El Muhur @ ULB
 */

#ifndef BRICK_HPP
#define BRICK_HPP

#include "../core/GameObject.hpp"
#include "../core/SpriteManager.hpp"

#include <unordered_map>

#include "Powerup.hpp"

enum class BRICK_TYPE {
    WHITE, ORANGE, CYAN, GREEN, RED, BLUE, MAGENTA, YELLOW, SILVER, GOLDEN
};

struct BrickTypeData {
    ALLEGRO_COLOR color;
    int points_bonus;
    int hits_needed;
};

static const std::unordered_map<std::string, const BRICK_TYPE> code_to_brick_type = {
    {"WH", BRICK_TYPE::WHITE  },
    {"OR", BRICK_TYPE::ORANGE },
    {"CY", BRICK_TYPE::CYAN   },
    {"GR", BRICK_TYPE::GREEN  },
    {"RE", BRICK_TYPE::RED    },
    {"BL", BRICK_TYPE::BLUE   },
    {"MA", BRICK_TYPE::MAGENTA},
    {"YE", BRICK_TYPE::YELLOW },
    {"SI", BRICK_TYPE::SILVER },
    {"GO", BRICK_TYPE::GOLDEN }
};

class Brick : public GameObject {
public:
    Brick(SpriteManager _sprite_manager, Vector2f _position, BRICK_TYPE _brick_type);

    BRICK_TYPE get_brick_type() const;

    BrickTypeData get_brick_type_data() const;

    int get_hits_needed() const;

    void set_hits_needed(int _hits_needed);

    POWERUP_TYPE get_held_powerup_type() const;

    void set_held_powerup_type(POWERUP_TYPE);

    void draw() const;

    static void draw_bricks(const SpriteManager &, const std::vector<std::shared_ptr<Brick> > &);

    static std::shared_ptr<Brick> intersects_brick(std::vector<std::shared_ptr<Brick> > &, GameObject *, Vector2f &);

    void on_brick_destroy(std::vector<std::shared_ptr<Brick> > &, std::vector<std::shared_ptr<Powerup> > &, int &);

private:
    SpriteManager sprite_manager;

    BRICK_TYPE brick_type;

    BrickTypeData brick_type_data;

    int hits_needed;

    POWERUP_TYPE held_powerup;
};

#endif
