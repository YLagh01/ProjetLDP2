#ifndef GAMEORCHESTRA_HPP
#define GAMEORCHESTRA_HPP

#include <vector>
#include "Brick.hpp"
#include "Ball.hpp"
#include "Plate.hpp"

class GameOrchestra {
public:
    GameOrchestra();

    void check_collisions();

    void draw() const;

    void move_plate(bool direction);

    void move_ball();

    void draw_ball();

    void draw_plate();

    void draw_bricks() const;

private:
    vector<Brick> Bricks;

    Ball ball{Position{280, 750}, Direction{0, -1}, 5};

    Plate plate{al_load_bitmap("../res/plate.png"), Position{250, 800}, Direction{0, 0}, 1};

    static Direction get_reflected_direction(Direction init_direction, vector<float> normal);

    void init_bricks();

    void check_collision_wall();
};


#endif
