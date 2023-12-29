#include "scorespage.h"
#include "mainwindow.h"
#include "Hardware/HighScore.h"
#include <QDebug>
#include <QDir>

/**
 * @class ScoresPage
 * @brief Class responsible for displaying high scores in the application.
 *
 * This class sets up and displays a page showing high scores. It includes a QLabel for the title,
 * a QListWidget for listing scores, and a QPushButton to return to the main menu.
 * @author Yangxiuye Gu
 */
ScoresPage::ScoresPage(const QSize &size, QWidget *parent)
        : QWidget(parent) {
    setFixedSize(size);
    setStyleSheet("background-color: #857be6;"); // Set the background color

    layout = new QVBoxLayout(this);
    titleLabel = new QLabel("High Scores", this);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("font-size: 32px; font-weight: bold; color: white;");

    scoresListWidget = new QListWidget(this);
    scoresListWidget->setStyleSheet(
            "QListWidget { font-size: 20px; background-color: #f3e5f5; border-radius: 5px; }"
            "QListWidget::item { border-bottom: 1px solid #b39ddb; padding: 5px; }"
            "QListWidget::item:nth-child(even) { background-color: #ede7f6; }"
    );

    returnButton = new QPushButton(this);
    QPixmap returnPixmap("return.png"); // Replace with your image path
    returnPixmap = returnPixmap.scaled(QSize(190, 80), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    returnButton->setIcon(QIcon(returnPixmap));
    returnButton->setIconSize(returnPixmap.size());
    returnButton->setFixedSize(QSize(190, 80));
    returnButton->setStyleSheet("QPushButton { border: none; background-color: transparent; }"
                                "QPushButton:pressed { background-color: rgba(255, 255, 255, 100); }");

    connect(returnButton, &QPushButton::clicked, this, &ScoresPage::onReturnButtonClicked);

    layout->addWidget(titleLabel, 0, Qt::AlignCenter);
    layout->addSpacing(20); // Add some space between title and list
    layout->addWidget(scoresListWidget);
    layout->addSpacing(10); // Space before the return button
    layout->addWidget(returnButton, 0, Qt::AlignCenter);
    layout->addSpacing(10); // Space at the bottom

    updateHighScores(scoresListWidget);
}

/**
 * @brief Updates the list widget with high scores.
 *
 * Retrieves high scores from the HighScore class and populates the QListWidget with these scores.
 *
 * @param scoresListWidget Pointer to the QListWidget that displays the scores.
 */
void ScoresPage::updateHighScores(QListWidget* scoresListWidget) {
    HighScore highScore;
    highScore.print();
    auto scores = highScore.getHighScores();

    qDebug() << "Updating high scores. Found " << scores.size() << " entries.";
    qDebug() << "Current directory:" << QDir::currentPath();

    scoresListWidget->clear();

    for (const auto& score : scores) {
        QString scoreEntry = QString::fromStdString(score.second + " - " + std::to_string(score.first));
        qDebug() << "Adding score to list:" << scoreEntry;
        scoresListWidget->addItem(scoreEntry);
    }
}

/**
 * @brief Slot to handle the return button click.
 *
 * Emits a signal to return to the main menu when the return button is clicked.
 */
void ScoresPage::onReturnButtonClicked() {
    emit returnToMainMenu();
    playAudio("Click.wav");
    playAudio("gameSound.mp3");
}
