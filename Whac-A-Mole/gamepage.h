/**
 * @file gamepage.h
 * @brief Header file for the GamePage class.
 *
 * This file contains the declaration of the GamePage class, which is a part of
 * the graphical user interface in a game application. It includes the setup and
 * functionality for the game's main page.
 * @author Yangxiuye Gu
 */

#ifndef GAMEPAGE_H
#define GAMEPAGE_H

#include <QWidget>
#include <QPushButton>

/**
 * @class GamePage
 * @brief Class representing the main game page in a GUI application.
 *
 * The GamePage class extends the QWidget class and is responsible for
 * displaying the main interface of the game, including any interactive elements
 * such as buttons and display elements like instructions.
 */
class GamePage : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Constructor for the GamePage class.
     *
     * Initializes a new instance of the GamePage class with a specified size and parent.
     *
     * @param size The size of the game page.
     * @param parent The parent widget, defaulting to nullptr if not specified.
     */
    explicit GamePage(const QSize &size, QWidget *parent = nullptr);

public slots:
            /**
             * @brief Slot to start the game.
             *
             * This slot is triggered to initiate the start of the game, typically connected
             * to a signal from a start button or similar interactive element.
             */
            void startGame();

    // ... other members and functions ...
};

#endif // GAMEPAGE_H
