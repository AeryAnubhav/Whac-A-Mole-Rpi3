#ifndef PLAYPAGE_H
#define PLAYPAGE_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include "HardwareInterface.h"

/**
 * @class PlayPage
 * @brief The PlayPage class for displaying the game interface.
 *
 * This class is responsible for setting up and displaying the game play interface
 * in a GUI application. It includes various UI elements like buttons and labels
 * to interact with the user and display game information.
 */
class PlayPage : public QWidget {
    Q_OBJECT

public:
    /**
     * @brief Constructs a PlayPage object.
     *
     * Initializes a new instance of the PlayPage class with a specified size and parent widget.
     * Sets up the UI elements required for the game play page.
     *
     * @param size The size of the widget.
     * @param parent The parent QWidget, defaulting to nullptr if not specified.
     */
    explicit PlayPage(const QSize &size, QWidget *parent = nullptr);

    /**
     * @brief Destructor for PlayPage.
     *
     * Cleans up resources used by the PlayPage instance, like UI elements and hardware interface.
     */
    ~PlayPage();

    signals:
            /**
             * @brief Signal to return to the main window.
             *
             * Emitted when the user requests to return to the main window from the game page.
             */
            void returnToMainMenu();
public slots:
            void rankDisplay();

private:
    HardwareInterface* hardwareInterface;  ///< Pointer to the HardwareInterface object.

    // UI elements as member variables
    QLineEdit* usernameInput;      ///< Input field for the player's username.
    QLabel* welcomeLabel;          ///< Label to display welcome message.
    QPushButton* startButton;      ///< Button to start the game.
    QLabel* countdownLabel;        ///< Label to display the game countdown.
    QLabel* scoreLabel;            ///< Label to display the player's score.
    QLabel* gameStatusLabel;       ///< Label to display the current game status.

    QPushButton* returnToMainWindowButton; ///< Button to return to the main window.

    // Additional member variables can be added as needed.
};

#endif // PLAYPAGE_H
