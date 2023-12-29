#include "HardwareInterface.h"
#include <QTimer>
#include <QThread>

/**
 * @class HardwareInterface
 * @brief Manages the hardware interactions in a game application.
 *
 * The HardwareInterface class is responsible for interfacing with the game hardware.
 * It includes methods for starting and stopping the game, handling the game logic,
 * and managing game-related events and signals.
 * @author Anubhav Aery
 */
HardwareInterface::HardwareInterface(QObject *parent)
        : QObject(parent), gameController(), player(), highScore() {
    // Initialization, if needed
}

/**
 * @brief Destructor for HardwareInterface.
 *
 * Responsible for cleaning up resources used by the HardwareInterface instance.
 */
HardwareInterface::~HardwareInterface() {
    // Clean up, if needed
}

/**
 * @brief Starts the game with a given player name.
 *
 * Sets up the game environment, initializes the game controller, starts the game timer,
 * and emits a signal indicating the game has started.
 *
 * @param playerName The name of the player as a QString.
 */
void HardwareInterface::startGame(const QString& playerName) {
    player.setName(playerName.toStdString());
    gameController.setup();
    gameController.startGame();
    emit gameStarted();

    // QTimer should be created in the thread it's going to be used in
    QTimer *countdownTimer = new QTimer(this);
    countdownTimer->moveToThread(QThread::currentThread()); // Ensure timer is in the correct thread
    connect(countdownTimer, &QTimer::timeout, this, [this, countdownTimer]() {
        if (!gameController.timer.isTimeUp()) {
            emit countdownUpdated(gameController.timer.getTimeLeft());
        } else {
            countdownTimer->stop();
            countdownTimer->deleteLater();
            stopGame();
        }
    });
    countdownTimer->start(1000);
}

/**
 * @brief Stops the game.
 *
 * Ends the game, calculates the final score, and emits a signal indicating the game has ended.
 */
void HardwareInterface::stopGame() {
    gameController.endGame(player);
    //highScore.add(player.getScore(), player.getName());
    emit gameEnded();
}

/**
 * @brief Handles the game logic in a separate thread.
 *
 * This method sets up a new thread for running the game logic. It manages the starting
 * and stopping of the game and the interaction between the game controller and other components.
 *
 * @param playerName The name of the player as a QString.
 */
void HardwareInterface::handleGame(const QString& playerName) {
    // Creating a thread for game logic
    QThread *gameThread = new QThread();
    moveToThread(gameThread); // Move this object to the new thread

    // Connecting signals and slots for thread management
    connect(gameThread, &QThread::started, this, [this, playerName]() {
        startGame(playerName);
        // Add game logic here
        // This can include interaction with LEDMatrix and GameController
        gameController.inGame(player, highScore);
        stopGame();
    });
    connect(this, &HardwareInterface::gameEnded, gameThread, &QThread::quit);
    connect(gameThread, &QThread::finished, gameThread, &QThread::deleteLater);

    // Start the thread
    gameThread->start();
}


int HardwareInterface::getFinalScore(){
    return player.getScore();
}
