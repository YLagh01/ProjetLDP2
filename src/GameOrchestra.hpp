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

    void input(const ALLEGRO_MOUSE_STATE &, const ALLEGRO_MOUSE_STATE &, ALLEGRO_EVENT_TYPE, int);

    void render() const;

private:
    bool mouse_control_mode = false;

    int score = 0;

    std::vector<Brick> bricks;

    Ball ball;

    Plate plate;

    ALLEGRO_BITMAP *background_bitmap;
    ALLEGRO_BITMAP *brick_bitmap;
    ALLEGRO_BITMAP *plate_bitmap;
    ALLEGRO_BITMAP *ball_bitmap;

    ALLEGRO_FONT *main_font;

    void init_bricks();

    void check_ball_collisions();

    void key_down(int);

    void key_up(int);
};

#endif
