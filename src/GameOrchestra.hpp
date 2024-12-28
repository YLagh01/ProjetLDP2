#ifndef GAMEORCHESTRA_HPP
#define GAMEORCHESTRA_HPP

#include "Brick.hpp"
#include "Ball.hpp"
#include "Plate.hpp"

#include <vector>

class GameOrchestra {
public:
    GameOrchestra();

    void update();

    void input(ALLEGRO_EVENT_TYPE, int);

    void render() const;

private:
    int score = 0;

    std::vector<Brick> bricks;

    Ball ball;

    Plate plate;

    void init_bricks();

    void check_ball_collisions();

    void key_down(int);

    static void key_up(int);
};

#endif
