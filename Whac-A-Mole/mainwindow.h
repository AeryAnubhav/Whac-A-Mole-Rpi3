#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>
#include "gamepage.h"
#include "scorespage.h"
#include "playpage.h"
#include <string>

/**
 * @brief Plays an audio file using SDL2.
 *
 * @param audioPath Path to the audio file as a std::string.
 * @return True if the audio plays successfully, false otherwise.
 */
bool playAudio(const std::string &audioPath);

/**
 * @class MainWindow
 * @brief Main window class for the GUI application.
 *
 * This class is responsible for setting up and displaying the main window of the application.
 * It includes button initialization, signal-slot connections, and window layout management.
 */
class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    /**
     * @brief Constructs a MainWindow object.
     *
     * Initializes a new instance of the MainWindow class with a parent QWidget.
     *
     * @param parent The parent QWidget, defaulting to nullptr if not specified.
     */
    explicit MainWindow(QWidget *parent = nullptr);

private slots:
            /**
             * @brief Slot for handling the start button click.
             *
             * Initiates actions when the start button is clicked, such as transitioning to the game page.
             */
            void on_startButton_clicked();

    /**
     * @brief Slot for handling the game scores button click.
     *
     * Transitions to the scores page when the game scores button is clicked.
     */
    void on_gamescoresButton_clicked();

    /**
     * @brief Slot for handling the exit button click.
     *
     * Closes the application when the exit button is clicked.
     */
    void on_exitButton_clicked();

    /**
     * @brief Slot to handle the return from ScoresPage.
     *
     * Manages the transition back to the main menu from the ScoresPage.
     */
    void returnToMainMenu();

private:
    /**
     * @brief Creates a QPushButton with an image.
     *
     * Sets up a QPushButton, assigns an image to it, and applies necessary styles.
     *
     * @param imagePath Path to the image file as a QString.
     * @param size Size of the QPushButton as a QSize.
     * @return Pointer to the created QPushButton.
     */
    QPushButton* setupButtonWithImage(const QString &imagePath, const QSize &size);

    /**
     * @brief Animates a QPushButton.
     *
     * Creates a brief animation for the QPushButton, making it appear to shrink and then revert back to its original size.
     *
     * @param button Pointer to the QPushButton to be animated.
     */
    void animateButton(QPushButton* button);

    QPushButton *startButton; ///< Button to start the game.
    QPushButton *gamescoresButton; ///< Button to view game scores.
    QPushButton *exitButton; ///< Button to exit the application.

    ScoresPage *scoresPage; ///< Pointer to the ScoresPage.
    PlayPage *playPage;
};

#endif // MAINWINDOW_H
