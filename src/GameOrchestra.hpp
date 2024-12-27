#ifndef GAMEORCHESTRA_HPP
#define GAMEORCHESTRA_HPP

#include "Brick.hpp"
#include "Ball.hpp"
#include "Main.hpp"
#include "Plate.hpp"

#include <vector>

class GameOrchestra {
public:
    GameOrchestra();

    void update();

    void input(ALLEGRO_EVENT_TYPE, int);

    void render() const;

private:
    std::vector<Brick> bricks;

    Ball ball{Position{280, 750}, Direction{0, -1}, 5};

    Plate plate{al_load_bitmap("../res/plate.png"), Position{250, 800}, Direction{0, 0}, PLATE_SPEED};

    void init_bricks();

    void check_ball_collisions();

    void key_down(int);

    static void key_up(int);
};

#endif
