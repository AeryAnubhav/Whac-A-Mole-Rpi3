#ifndef SCORESPAGE_H
#define SCORESPAGE_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QListWidget>

/**
 * @class ScoresPage
 * @brief Class representing the high scores page in the GUI application.
 *
 * The ScoresPage class is responsible for displaying high scores in a list format.
 * It includes a return button to navigate back to the main menu.
 */
class ScoresPage : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Constructs a ScoresPage object.
     *
     * Initializes a new instance of the ScoresPage class with a specified size and parent widget.
     * Sets up the UI elements required for the scores page.
     *
     * @param size The size of the widget.
     * @param parent The parent QWidget, defaulting to nullptr if not specified.
     */
    explicit ScoresPage(const QSize &size, QWidget *parent = nullptr);

    /**
     * @brief Function to update the high scores displayed on the page.
     *
     * Updates the QListWidget with the latest high scores.
     *
     * @param scoresListWidget Pointer to the QListWidget that displays the scores.
     */
    void updateHighScores(QListWidget* scoresListWidget);

    signals:
            /**
             * @brief Signal to indicate a return to the main menu.
             *
             * Emitted when the user interacts with the return button.
             */
            void returnToMainMenu();

private slots:
            /**
             * @brief Slot for handling return button click.
             *
             * Invoked when the return button is clicked to navigate back to the main menu.
             */
            void onReturnButtonClicked();

private:
    QVBoxLayout* layout;       ///< Layout to organize widgets.
    QLabel* titleLabel;        ///< Label to display the title of the page.
    QPushButton* returnButton; ///< Button to return to the main menu.
    QListWidget* scoresListWidget; ///< List widget to display scores.
};

#endif // SCORESPAGE_H
