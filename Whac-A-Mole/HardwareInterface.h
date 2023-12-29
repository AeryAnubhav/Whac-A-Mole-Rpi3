#ifndef HARDWAREINTERFACE_H
#define HARDWAREINTERFACE_H

#include <QObject>
#include "Hardware/GameController.h"
#include "Hardware/Player.h"
#include "Hardware/HighScore.h"

/**
 * @class HardwareInterface
 * @brief Manages the interface between the game logic and the hardware components.
 *
 * This class encapsulates the interaction with the game hardware, including the game controller,
 * player data, and high score management. It offers functionality to start and stop the game,
 * handle the game's logic, and emit relevant signals during the game's lifecycle.
 * @author Anubhav Aery
 */
class HardwareInterface : public QObject {
    Q_OBJECT

public:
    /**
     * @brief Constructs a HardwareInterface object.
     *
     * Initializes a new instance of the HardwareInterface with a parent QObject.
     *
     * @param parent The parent QObject, defaulting to nullptr if not specified.
     */
    explicit HardwareInterface(QObject *parent = nullptr);

    /**
     * @brief Destructor for HardwareInterface.
     *
     * Cleans up resources used by the HardwareInterface instance.
     */
    ~HardwareInterface();

    /**
     * @brief Handles the overall game logic.
     *
     * This method is responsible for setting up and managing the game logic,
     * including starting and stopping the game.
     *
     * @param playerName The name of the player as a QString.
     */
    void handleGame(const QString& playerName); // New method for game logic
    int getFinalScore();

public slots:
            /**
             * @brief Slot to start the game with a given player name.
             *
             * This slot sets up the game environment, initializes the game controller, and starts the game.
             *
             * @param playerName The name of the player as a QString.
             */
            void startGame(const QString& playerName);

    /**
     * @brief Slot to stop the game.
     *
     * This slot is responsible for ending the game and handling any necessary cleanup.
     */
    void stopGame();

    signals:
            /**
             * @brief Signal emitted when the score is updated.
             *
             * @param newScore The updated score as an integer.
             */
            void scoreUpdated(int newScore);

    /**
     * @brief Signal emitted when the game starts.
     */
    void gameStarted();

    /**
     * @brief Signal emitted when the game ends.
     */
    void gameEnded();

    /**
     * @brief Signal emitted to update the countdown timer.
     *
     * @param timeLeft The time left in the countdown as an integer.
     */
    void countdownUpdated(int timeLeft);
    

private:
    GameController gameController; ///< Manages game control logic.
    Player player;                 ///< Represents the player in the game.
    HighScore highScore;           ///< Manages high score data.
};

#endif // HARDWAREINTERFACE_H
