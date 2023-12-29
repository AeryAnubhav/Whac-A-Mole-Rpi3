#ifndef PLAYER_H
#define PLAYER_H

#include <string>

/**
 * @class Player
 * @brief Manages player information in a game, including their name and score.
 *
 * The Player class is responsible for storing and updating player-specific data such as
 * the player's name and their score in the game. It provides methods for setting the name,
 * getting the name and score, and modifying the score.
 * @author Anubhav Aery
 */
class Player {
public:
    /**
     * @brief Constructor for the Player class.
     *
     * Initializes a new Player instance with a score of 0.
     */
    Player();

    /**
     * @brief Sets the player's name.
     *
     * @param n A string representing the player's name.
     */
    void setName(const std::string& n);

    /**
     * @brief Retrieves the player's name.
     *
     * @return A string representing the player's name.
     */
    std::string getName() const;

    /**
     * @brief Retrieves the player's current score.
     *
     * @return An integer representing the player's score.
     */
    int getScore() const;

    /**
     * @brief Increments the player's score by one.
     *
     * Increases the player's score by one point each time it is called.
     */
    void incrementScore();

    /**
     * @brief Decrements the player's score by one, not allowing it to go below zero.
     *
     * Decreases the player's score by one point each time it is called, ensuring that
     * the score does not drop below zero.
     */
    void decrementScore();

private:
    std::string name; ///< The name of the player.
    int score; ///< The score of the player.
};

#endif // PLAYER_H
