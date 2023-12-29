#include "GameController.h"
#include <pigpio.h>
#include <iostream>
#include <thread>
#include <chrono>
#include <ncurses.h>

/**
 * @class GameController
 * @brief Controls the game logic and interactions with hardware components.
 *
 * This class is responsible for initializing GPIO pins, managing game timing,
 * handling user input, controlling LEDs, and maintaining game state.
 * @author Anubhav Aery
 */
GameController::GameController() : timer(), ledMatrix(), currentPlayer() {}

/**
 * @brief Initializes the game environment.
 *
 * Sets up GPIO pins for LED control using the pigpio library. Throws runtime error
 * if GPIO initialization fails.
 * @author Anubhav Aery
 */
void GameController::setup() {
    if (gpioInitialise() < 0) {
        throw std::runtime_error("Failed to initialize pigpio.");
    }
    const auto& keyToLedMap = ledMatrix.getKeyToLedMap();
    for (auto const& kvp : keyToLedMap) {
        gpioSetMode(kvp.second, PI_OUTPUT);
        gpioWrite(kvp.second, 0); // Initially turn off all LEDs
    }
}

/**
 * @brief Starts the game.
 *
 * Marks the beginning of the game by starting the timer and printing a start message.
 * @author Anubhav Aery
 */
void GameController::startGame() {
    std::cout << "Game started!\n";
    timer.start();
}

/**
 * @brief Handles the in-game logic.
 *
 * Manages the game's running state, including lighting up LEDs, capturing user input,
 * and updating the player's score. Ends when the timer is up.
 *
 * @param player Reference to the player's data.
 * @param highScore Reference to the high score manager.
 * @author Anubhav Aery
 */
void GameController::inGame(Player& player, HighScore& highScore) {
    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    curs_set(0);

    int currentLedPin = -1;
    bool ledOn = false;

    while (!timer.isTimeUp()) {
        mvprintw(0, 0, "Time left: %d seconds ", timer.getTimeLeft());
        mvprintw(1, 0, "Score:    "); // Clear the previous score by printing spaces
        mvprintw(1, 0, "Score: %d", player.getScore()); // Print the new score

        refresh();
        if (!ledOn) {
            if (currentLedPin != -1) {
                gpioWrite(currentLedPin, 0);
            }
            currentLedPin = ledMatrix.lightUpRandomLED(currentLedPin);
            ledOn = true;
        }

        int ch = getch();
        if (ch != ERR) {
            const auto& keyToLedMap = ledMatrix.getKeyToLedMap();
            if (keyToLedMap.count(ch) > 0) {
                if (keyToLedMap.at(ch) == currentLedPin) {
                    gpioWrite(currentLedPin, 0);
                    ledOn = false;
                    player.incrementScore();
                    //playAudio("Click.wav");
                } else {
                    player.decrementScore();
                }
            }
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    endwin();
    gpioTerminate();
    std::cout << "Game Over! Your score is: " << player.getScore() << std::endl;
    highScore.add(player.getScore(), player.getName());
}

/**
 * @brief Ends the game.
 *
 * Stops the game timer and prints the final score of the player.
 *
 * @param player Reference to the player's data.
 * @author Anubhav Aery
 */
void GameController::endGame(Player& player) {
    std::cout << "Game ended!\n";
    timer.stop();
    std::cout << "Final score: " << player.getScore() << "\n";
}
