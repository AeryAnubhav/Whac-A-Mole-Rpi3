#ifndef HIGHSCORE_H
#define HIGHSCORE_H

#include <map>
#include <string>
#include <vector>
#include <functional> // Include for std::greater

/**
 * @class HighScore
 * @brief Manages high score data for the game.
 *
 * This class handles the storage, retrieval, and updating of high scores. It supports
 * reading and writing high score data to a file and provides functionalities to print
 * and retrieve sorted high score entries.
 * @author Eseosa Emmanuel Atekha
 */
class HighScore {
public:
    /**
     * @brief Reads and prints high scores from a file.
     *
     * Opens the 'highScores.txt' file, reads high score entries, and prints them.
     * High scores are stored in a map sorted in descending order.
     */
    void print();

    /**
     * @brief Adds a new high score entry to a file.
     *
     * Appends a player's name and score to the 'highScores.txt' file. High scores are stored
     * in a multimap in descending order.
     *
     * @param score The score achieved by the player.
     * @param playerName The name of the player.
     */
    void add(int score, const std::string& playerName);

    /**
     * @brief Retrieves sorted high scores as a vector.
     *
     * Returns a vector of pairs, each containing a score and the corresponding player's name.
     * The vector is sorted in descending order based on the score.
     *
     * @return Vector of pairs with score and player name.
     */
    std::vector<std::pair<int, std::string>> getHighScores() const;

private:
    // Use std::greater to sort scores in descending order
    std::multimap<int, std::string, std::greater<int>> highScoresMap; ///< Map storing high scores in descending order.
};

#endif // HIGHSCORE_H
