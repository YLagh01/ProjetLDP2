/*
 * INFO-F202 (2024 - 2025)
 * Written with ❤︎ by Yassir Laghmouchi & Nabil El Muhur @ ULB
 */

#ifndef LASER_HPP
#define LASER_HPP

#include "../core/GameObject.hpp"
#include "../core/SpriteManager.hpp"

#include "Plate.hpp"

class Brick;
class Powerup;

class Laser : public GameObject {
public:
    Laser(ALLEGRO_BITMAP *_bitmap, Vector2f _position);

    void on_update(std::vector<std::shared_ptr<Laser> > &, std::vector<std::shared_ptr<Brick> > &,
                   std::vector<std::shared_ptr<Powerup> > &, const std::shared_ptr<Powerup> &, int &);

    static void spawn_laser(const SpriteManager &, std::vector<std::shared_ptr<Laser> > &, const Plate &);
};

#endif
