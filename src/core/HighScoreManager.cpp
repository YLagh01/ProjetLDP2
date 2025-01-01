/*
 * INFO-F202 (2024 - 2025)
 * Written with ❤︎ by Yassir Laghmouchi & Nabil El Muhur @ ULB
 */

#include "HighScoreManager.hpp"

#include "../Common.hpp"

#include <iostream>
#include <fstream>

int read_high_score() {
    int high_score = 0;

    // Opening the input file stream
    std::ifstream input_high_score(HIGH_SCORE_PATH);

    // Checking if the high score file is open
    if (!input_high_score) {
        std::cerr << "Error: Could not open the high score data file" << std::endl;
        exit(1);
    }

    // Reading the first line of the file
    std::string high_score_string;
    if (std::getline(input_high_score, high_score_string)) {
        high_score = std::stoi(high_score_string);
    }

    // Closing the input file stream
    input_high_score.close();
    return high_score;
}

void write_high_score(const int score, const int high_score, const bool force) {
    // Writing the high score to the file only if the current score is greater or equal and if the writing isn't forced
    if (score < high_score && !force) return;

    // Opening the output file stream
    std::ofstream output_high_score(HIGH_SCORE_PATH);

    // Checking if the high score file is open
    if (!output_high_score) {
        std::cerr << "Error: Could not open the high score data file" << std::endl;
        exit(1);
    }

    // Writing the new high score to the file
    output_high_score << score;

    // Closing the input file stream
    output_high_score.close();
}
