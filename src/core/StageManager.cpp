/*
 * INFO-F202 (2024 - 2025)
 * Written with ❤︎ by Yassir Laghmouchi & Nabil El Muhur @ ULB
 */

#include "StageManager.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>

void init_stage(SpriteManager sprite_manager, uint8_t stage_index, ALLEGRO_BITMAP *&background, std::vector<std::shared_ptr<Brick> > &bricks) {
    // Opening the input file stream
    std::ifstream input_stage("../res/stages/stage_" + std::to_string(stage_index) + ".txt");

    // Checking if the high score file is open
    if (!input_stage) {
        std::cerr << "Error: Could not open the stage file" << std::endl;
        exit(1);
    }

    // Reading the first line of the file to set the background image
    std::string background_image;
    std::getline(input_stage, background_image);

    if (background_image == "background_0") {
        background = sprite_manager.background_0_bitmap;
    }
    else if (background_image == "background_1") {
        background = sprite_manager.background_1_bitmap;
    }
    else if (background_image == "background_2") {
        background = sprite_manager.background_2_bitmap;
    }
    else {
        std::cerr << "Error: Could not find the background image" << std::endl;
        exit(1);
    }

    // Using a regex pattern to decode bricks from the stage file
    const std::regex brick_encoding_pattern(R"((\w\w)(?:\[(\w)\])?)");

    // Iterating rows and columns to define bricks and push them into the vector
    int row = 0;
    std::string line;

    while (std::getline(input_stage, line)) {
        std::stringstream linestream(line);
        std::string brick_encoding;

        int column = 0;

        // Iterating the line's substrings delimited by ','
        while (std::getline(linestream, brick_encoding, ',')) {

            // Using regex matching to decode the brick encoding pattern (i.e.: WH[L] for a white brick holding a laser powerup)
            std::smatch brick_encoding_match;
            if (std::regex_match(brick_encoding, brick_encoding_match, brick_encoding_pattern)) {
                std::string brick_type_code = brick_encoding_match[1];
                std::string powerup_code    = brick_encoding_match[2];

                auto brick_type_it = code_to_brick_type.find(brick_type_code);

                // If the brick type is defined (= if there is a brick at those coordinates)
                if (brick_type_it != code_to_brick_type.end()) {
                    BRICK_TYPE brick_type = brick_type_it->second;

                    // Calculating the brick's position in the grid
                    Vector2f brick_position{
                        BRICK_WIDTH  * static_cast<float>(column) + BORDERS_SIZE,
                        BRICK_HEIGHT * static_cast<float>(row)    + BRICKS_Y_PADDING
                    };

                    // Defining the brick's object
                    Brick brick{sprite_manager, brick_position, brick_type};

                    // Setting the brick's held powerup if it has one
                    auto brick_powerup_it = code_to_powerup_type.find(powerup_code);

                    if (brick_powerup_it != code_to_powerup_type.end()) {
                        brick.set_held_powerup_type(brick_powerup_it->second);
                    }

                    // Adding the brick to the vector
                    bricks.push_back(std::make_shared<Brick>(brick));
                }
            }
            column++;
        }
        row++;
    }

    // Closing the input file stream
    input_stage.close();
}
