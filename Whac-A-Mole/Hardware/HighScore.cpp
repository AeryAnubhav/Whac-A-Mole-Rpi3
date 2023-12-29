#include "HighScore.h"
#include <fstream>
#include <iostream>

/**
 * @class HighScore
 * @brief Manages high score data for the game.
 *
 * This class is responsible for reading, writing, and maintaining high score data.
 * It interacts with a file to persist high score information.
 */

/**
 * @brief Retrieves high scores as a sorted vector.
 *
 * Returns a vector of pairs, each containing a score and the corresponding player's name.
 * The vector is sorted based on the score.
 *
 * @return Vector of pairs with score and player name.
 * @author Eseosa Emmanuel Atekha
 */
std::vector<std::pair<int, std::string>> HighScore::getHighScores() const {
    std::vector<std::pair<int, std::string>> scores;
    for (const auto& entry : highScoresMap) {
        scores.push_back({entry.first, entry.second});
    }
    return scores;
}

/**
 * @brief Reads high scores from a file and prints them to the console.
 *
 * Opens and reads the 'highScores.txt' file, if available, and prints the high scores
 * to the console. The scores are inserted into a map for sorting purposes.
 */
void HighScore::print() {
    std::ifstream inputFile("highScores.txt");
    if (inputFile.is_open()) {
        std::string name;
        int score;
        while (inputFile >> name >> score) {
            highScoresMap.insert(std::make_pair(score, name));
        }
        inputFile.close();

        std::cout << "Name " << "Score" << std::endl;
        for (auto rit = highScoresMap.rbegin(); rit != highScoresMap.rend(); ++rit) {
            std::cout << rit->second << " " << rit->first << std::endl;
        }

    } else {
        std::cerr << "Unable to open the file." << std::endl;
    }
}

/**
 * @brief Adds a new high score to the file.
 *
 * Appends a new high score entry, consisting of the player's name and score, to the 'highScores.txt' file.
 * If the file cannot be opened, an error message is displayed.
 *
 * @param score The score achieved by the player.
 * @param playerName The name of the player.
 */
void HighScore::add(int score, const std::string& playerName) {
    std::ofstream outputFile("highScores.txt", std::ios::app);
    if (outputFile.is_open()) {
        outputFile << playerName << " " << score << std::endl;
        outputFile.close();
    } else {
        std::cerr << "Unable to open the file for writing." << std::endl;
    }
}
