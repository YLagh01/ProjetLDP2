/*
 * INFO-F202 (2024 - 2025)
 * Written with ❤︎ by Yassir Laghmouchi & Nabil El Muhur @ ULB
 */

#ifndef LASER_HPP
#define LASER_HPP

#include "../core/GameObject.hpp"

#include "Plate.hpp"

class Laser : public GameObject {
public:
    Laser(ALLEGRO_BITMAP *_bitmap, Vector2f _position);

    void draw() const;

    static void spawn_laser(std::vector<std::shared_ptr<Laser> > &, const Plate &);
};

#endif
