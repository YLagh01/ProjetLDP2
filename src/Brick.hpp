#ifndef BRICK_HPP
#define BRICK_HPP

#include "GameObject.hpp"

enum class BRICK_TYPE {
    WHITE, ORANGE, CYAN, GREEN, RED, BLUE, MAGENTA, YELLOW, SILVER, GOLDEN
};

struct BrickTypeData {
    ALLEGRO_COLOR color;
    int points_bonus;
};

class Brick : public GameObject {
public:
    Brick(Vector2f _position, Vector2f _direction, float _speed, BRICK_TYPE _brick_type);

    BrickTypeData get_brick_type_data() const;

    static BRICK_TYPE get_brick_type_from_index(int) ;

private:
    BrickTypeData brick_type_data;
};

#endif
