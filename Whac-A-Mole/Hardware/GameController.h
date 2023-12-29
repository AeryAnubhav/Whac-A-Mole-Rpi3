#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "Timer.h"
#include "LEDMatrix.h"
#include "Player.h"
#include "HighScore.h"

/**
 * @class GameController
 * @brief Manages the core game logic and interfaces with hardware components.
 *
 * The GameController class is responsible for initializing the game environment,
 * handling game state, processing player inputs, controlling LED matrix, and managing
 * the game timer. It acts as the central component coordinating various aspects of the game.
 * @author Anubhav Aery
 */
class GameController {
public:
    /**
     * @brief Constructor for GameController.
     *
     * Initializes a new GameController instance with default Timer, LEDMatrix, and Player objects.
     */
    GameController();

    /**
     * @brief Sets up the game environment.
     *
     * Initializes GPIO pins for LED control and prepares the game for starting.
     */
    void setup();

    /**
     * @brief Starts the game.
     *
     * Begins the game by starting the timer and initializing game parameters.
     */
    void startGame();

    /**
     * @brief Manages the in-game logic.
     *
     * Controls the gameplay activities, including LED matrix interactions, player score,
     * and handling game timing. Continues until the game timer runs out.
     *
     * @param player Reference to the current Player object.
     * @param highScore Reference to the HighScore manager.
     */
    void inGame(Player& player, HighScore& highScore);

    /**
     * @brief Ends the game.
     *
     * Stops the game, finalizes the score, and performs any necessary cleanup.
     *
     * @param player Reference to the current Player object.
     */
    void endGame(Player& player);

    Timer timer; ///< Timer object to manage game timing.
    LEDMatrix ledMatrix; ///< LEDMatrix object to control the LED matrix.
    Player currentPlayer; ///< Player object to represent the current player.
};

#endif // GAMECONTROLLER_H
