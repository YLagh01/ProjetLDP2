/*
 * INFO-F202 (2024 - 2025)
 * Written with ❤︎ by Yassir Laghmouchi & Nabil El Muhur @ ULB
 */

#include "Laser.hpp"

#include "Brick.hpp"

Laser::Laser(ALLEGRO_BITMAP *_bitmap, const Vector2f _position): GameObject(
    _bitmap, _position, Vector2f{}, Vector2f{LASER_WIDTH, LASER_HEIGHT}, LASER_SPEED) {
    direction = UP_VECTOR;
}

void Laser::on_update(std::vector<std::shared_ptr<Laser> > &lasers, std::vector<std::shared_ptr<Brick> > &bricks,
                      std::vector<std::shared_ptr<Powerup> > &powerups, const std::shared_ptr<Powerup> &active_powerup,
                      int &score) {
    // Making the laser move up
    move();

    // Removing the laser object from the lasers vector if it goes outside the window's bounds
    if (position.y < BORDERS_SIZE) {
        erase_game_object(lasers, this);
    }

    // Checking for collisions with the bricks
    Vector2f                     brick_intersection_normal{};
    const std::shared_ptr<Brick> intersected_brick = Brick::intersects_brick(bricks, this, brick_intersection_normal);

    // If a brick was intersected
    if (intersected_brick != nullptr) {
        // Removing the laser object from the lasers vector
        erase_game_object(lasers, this);
        // Handling what happens when a brick is destroyed
        intersected_brick->on_destroy(bricks, powerups, active_powerup, score);
    }
}

void Laser::spawn_laser(const SpriteManager &sprite_manager, std::vector<std::shared_ptr<Laser> > &lasers,
                        const Plate &plate) {
    Laser laser{sprite_manager.laser_bitmap, Vector2f{}};

    // Setting the laser's initial position to be in the middle of the plate's width
    laser.set_position(Vector2f{
        plate.get_position().x + (plate.get_size().x - laser.get_size().x) / 2,
        plate.get_position().y - laser.get_size().y
    });

    lasers.push_back(std::make_shared<Laser>(laser));
}
