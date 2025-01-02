/*
 * INFO-F202 (2024 - 2025)
 * Written with ❤︎ by Yassir Laghmouchi & Nabil El Muhur @ ULB
 */

#ifndef STAGEMANAGER_HPP
#define STAGEMANAGER_HPP

#include "../objects/Brick.hpp"

void init_stage(const SpriteManager&, uint8_t, ALLEGRO_BITMAP *&, std::vector<std::shared_ptr<Brick> > &);

#endif
