/*
 * INFO-F202 (2024 - 2025)
 * Written with ❤︎ by Yassir Laghmouchi & Nabil El Muhur @ ULB
 */

#ifndef BALL_HPP
#define BALL_HPP

#include "../core/GameObject.hpp"

#include "Brick.hpp"
#include "Plate.hpp"

class Ball : public GameObject {
public:
    bool caught;
    long caught_time;

    Ball(const SpriteManager &_sprite_manager, Vector2f _position, Vector2f _direction, float _speed);

    static Vector2f get_bounce_direction(Vector2f, Vector2f);

    void handle_collisions_bricks(std::vector<std::shared_ptr<Brick> > &, std::vector<std::shared_ptr<Powerup> > &,
                                  const std::shared_ptr<Powerup> &, int &);

    void handle_collisions_plate(const Plate &, const std::shared_ptr<Powerup> &);

    void handle_collisions_walls();

    void handle_collisions(std::vector<std::shared_ptr<Brick> > &, const Plate &,
                           std::vector<std::shared_ptr<Powerup> > &, const std::shared_ptr<Powerup> &, int &);

    void catch_ball(const Plate &);

private:
    SpriteManager sprite_manager;
};

#endif
