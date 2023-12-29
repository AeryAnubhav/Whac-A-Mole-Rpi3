#include "gamepage.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QPixmap>
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>
#include <QDebug>
#include "playpage.h"
#include "mainwindow.h"

/**
 * @brief Animates a QPushButton to create a visual effect.
 *
 * This function creates an animation that makes the button appear to shrink briefly and then revert back to its original size.
 *
 * @param button Pointer to the QPushButton to be animated.
 * @author Yangxiuye Gu
 */
void animateButton(QPushButton* button) {
    QPropertyAnimation* animation = new QPropertyAnimation(button, "geometry");
    animation->setDuration(100);
    QRect startGeometry = button->geometry();
    QRect endGeometry = startGeometry.adjusted(5, 5, -5, -5); // Shrink by 5 pixels on each side
    animation->setStartValue(startGeometry);
    animation->setEndValue(endGeometry);

    QPropertyAnimation* revertAnimation = new QPropertyAnimation(button, "geometry");
    revertAnimation->setDuration(100);
    revertAnimation->setStartValue(endGeometry);
    revertAnimation->setEndValue(startGeometry);

    QSequentialAnimationGroup* group = new QSequentialAnimationGroup;
    group->addAnimation(animation);
    group->addAnimation(revertAnimation);
    group->start(QAbstractAnimation::DeleteWhenStopped);
}

GamePage::GamePage(const QSize &size, QWidget *parent)
        : QWidget(parent)
{
    setFixedSize(size);
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setAlignment(Qt::AlignCenter); // Center the content in the layout
    this->setStyleSheet("background-color: #857be6;"); // Set the background color

    // Create a label to display the image with instructions
    QLabel *instructionsImageLabel = new QLabel(this);
    QPixmap instructionsPixmap("ruleimage.png");

    if (!instructionsPixmap.isNull()) {
        QSize scaledSize = size * 0.9; // Example: Scale down to 90% of the GamePage size
        instructionsImageLabel->setPixmap(instructionsPixmap.scaled(scaledSize, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        instructionsImageLabel->setAlignment(Qt::AlignCenter);
    } else {
        qDebug() << "Failed to load the instructions image.";
    }

    // Create a PLAY button using an image
    QPushButton *playButton = new QPushButton(this);
    QPixmap playButtonPixmap("play.png");

    if (!playButtonPixmap.isNull()) {
        playButtonPixmap = playButtonPixmap.scaled(QSize(190, 70), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        playButton->setIcon(QIcon(playButtonPixmap));
        playButton->setIconSize(playButtonPixmap.size());
        playButton->setFixedSize(QSize(190, 70));
        playButton->setStyleSheet("border: none;");
        // Connect the pressed signal to the animate button function
        connect(playButton, &QPushButton::pressed, [playButton]()
        { animateButton(playButton);
            playAudio("Click.wav");
        });
        // Connect the clicked signal to the start game slot
        connect(playButton, &QPushButton::clicked, this, &GamePage::startGame);
    } else {
        qDebug() << "Failed to load the play button image.";
    }

    layout->addWidget(instructionsImageLabel, 0, Qt::AlignCenter);
    layout->addWidget(playButton, 0, Qt::AlignCenter);

    // Set the layout for the GamePage
    this->setLayout(layout);
}

void GamePage::startGame() {
    qDebug() << "Play button clicked, transitioning to play page.";
    // Hide the current game instructions page
    this->hide();
    playAudio("gameSound.mp3"); // Play an audio file at startup
    // Create and show the play page
    PlayPage *playPage = new PlayPage(this->size(), this->parentWidget()); // Pass the size and parent
    playPage->show();
}
