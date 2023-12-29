#include "Player.h"

/**
 * @class Player
 * @brief Represents a player in the game, managing their name and score.
 *
 * This class is responsible for storing and manipulating player-specific information,
 * including their name and score. It provides methods to set and get the player's name,
 * retrieve the score, and modify the score through increments and decrements.
 * @author Anubhav Aery
 */
Player::Player() : score(0) {}

/**
 * @brief Sets the player's name.
 *
 * @param n A string representing the player's name.
 */
void Player::setName(const std::string& n) {
    name = n;
}

/**
 * @brief Retrieves the player's name.
 *
 * @return A string representing the player's name.
 */
std::string Player::getName() const {
    return name;
}

/**
 * @brief Retrieves the player's current score.
 *
 * @return An integer representing the player's score.
 */
int Player::getScore() const {
    return score;
}

/**
 * @brief Increments the player's score by one.
 *
 * Increases the player's score by one point each time it is called.
 */
void Player::incrementScore() {
    score++;
}

/**
 * @brief Decrements the player's score by one, not allowing it to go below zero.
 *
 * Decreases the player's score by one point each time it is called, ensuring that
 * the score does not drop below zero.
 */
void Player::decrementScore() {
    if (score > 0) {
        score--;
    }
}
