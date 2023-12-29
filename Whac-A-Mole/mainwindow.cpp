#include "mainwindow.h"
#include <QVBoxLayout>
#include <QApplication>
#include <QDebug>
#include <QLabel>
#include <QPixmap>
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>
#include "gamepage.h"
#include "scorespage.h"
#include <QMovie>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>

/**
 * @brief Plays an audio file using SDL2.
 *
 * Initializes SDL and SDL_mixer, loads the specified audio file, and plays it.
 * It also handles any initialization or loading errors.
 *
 * @param audioPath Path to the audio file as a std::string.
 * @return True if the audio plays successfully, false otherwise.
 * @author Nasri Hussein
 */
bool playAudio(const std::string &audioPath)
{
    if (SDL_Init(SDL_INIT_AUDIO) < 0)
    {
        std::cerr << "SDL could not initialize! SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        std::cerr << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << std::endl;
        SDL_Quit();
        return false;
    }

    Mix_Music *music = Mix_LoadMUS(audioPath.c_str());
    if (music == NULL)
    {
        std::cerr << "Failed to load music! SDL_mixer Error: " << Mix_GetError() <<" "<<audioPath<<std::endl;
        Mix_CloseAudio();
        SDL_Quit();
        return false;
    }

    if (Mix_PlayMusic(music, 0) == -1)
    {
        std::cerr << "Failed to play music! SDL_mixer Error: " << Mix_GetError() << std::endl;
        Mix_FreeMusic(music);
        Mix_CloseAudio();
        SDL_Quit();
        return false;
    }

    return true;
}

/**
 * @class MainWindow
 * @brief Main window class for the GUI application.
 *
 * This class is responsible for setting up and displaying the main window of the application.
 * It includes background setting, button initialization, and signal-slot connections.
 */
MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent)
{   
    setWindowTitle("Whac-A-Mole Game");
    setFixedSize(900, 758);

    QPixmap background("mainbgimage.png");
    QLabel *backgroundLabel = new QLabel(this);
    backgroundLabel->setPixmap(background.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    backgroundLabel->setScaledContents(true);
    backgroundLabel->setGeometry(this->rect());

    QLabel *gifLabel = new QLabel(this);
    QMovie *movie = new QMovie("molegif.gif");
    if (movie->isValid()) {
        gifLabel->setMovie(movie);
        movie->start();
    } else {
        qDebug() << "Failed to load the GIF.";
    }

    gifLabel->setScaledContents(true);
    int gifWidth = 170;
    int gifHeight = 170;
    gifLabel->setFixedSize(gifWidth, gifHeight);
    gifLabel->setAlignment(Qt::AlignCenter);

    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);

    layout->addStretch(15);
    layout->addWidget(gifLabel, 0, Qt::AlignCenter);

    startButton = setupButtonWithImage("pressstart.png", QSize(200, 80));
    gamescoresButton = setupButtonWithImage("gamescores.png", QSize(200, 80));
    exitButton = setupButtonWithImage("exit.png", QSize(200, 80));

    layout->addStretch(1);
    layout->addWidget(startButton, 0, Qt::AlignCenter);
    layout->addWidget(gamescoresButton, 0, Qt::AlignCenter);
    layout->addWidget(exitButton, 0, Qt::AlignCenter);
    layout->addStretch(1);

    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);

    connect(startButton, &QPushButton::clicked, this, &MainWindow::on_startButton_clicked);
    connect(gamescoresButton, &QPushButton::clicked, this, &MainWindow::on_gamescoresButton_clicked);
    connect(exitButton, &QPushButton::clicked, this, &MainWindow::on_exitButton_clicked);

    scoresPage = nullptr;
}

/**
 * @brief Sets up a QPushButton with an image.
 *
 * Creates a QPushButton, sets its icon to the specified image, and applies styling.
 * It also connects a press signal to an animation and sound effect.
 *
 * @param imagePath Path to the image file as a QString.
 * @param size Size of the QPushButton as a QSize.
 * @return Pointer to the created QPushButton.
 */
QPushButton* MainWindow::setupButtonWithImage(const QString &imagePath, const QSize &size) {
    QPushButton *button = new QPushButton(this);
    QPixmap pixmap(imagePath);
    pixmap = pixmap.scaled(size, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    button->setIcon(QIcon(pixmap));
    button->setIconSize(size);
    button->setFixedSize(size);
    button->setStyleSheet("QPushButton { border: none; background-color: transparent; }"
                          "QPushButton:pressed { background-color: rgba(255, 255, 255, 100); }");

    connect(button, &QPushButton::pressed, this, [this, button]()
    {
        animateButton(button);
        playAudio("Click.wav");
    });

    return button;
}

/**
 * @brief Animates a QPushButton.
 *
 * Creates a brief animation for the QPushButton, making it appear to shrink and then revert back to its original size.
 *
 * @param button Pointer to the QPushButton to be animated.
 */
void MainWindow::animateButton(QPushButton* button) {
    QPropertyAnimation* animation = new QPropertyAnimation(button, "geometry");
    animation->setDuration(100);
    QRect startGeometry = button->geometry();
    QRect endGeometry = startGeometry.adjusted(5, 5, -5, -5);
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

/**
 * @brief Slot for handling the start button click.
 *
 * Hides the main window and displays the game page when the start button is clicked.
 */
void MainWindow::on_startButton_clicked() {
    QSize currentSize = this->size();
    this->hide();
    playAudio("gameSound.mp3"); // Play an audio file at startup
    GamePage *gamePage = new GamePage(currentSize);
    gamePage->show();

}

/**
 * @brief Slot for handling the game scores button click.
 *
 * Hides the main window and displays the scores page when the game scores button is clicked.
 */
void MainWindow::on_gamescoresButton_clicked() {
    this->hide();

    if (!scoresPage) {
        QSize currentSize = this->size();
        scoresPage = new ScoresPage(currentSize);
        connect(scoresPage, &ScoresPage::returnToMainMenu, this, &MainWindow::returnToMainMenu);
    }
    playAudio("gameSound.mp3"); // Play an audio file at startup
    scoresPage->show();
}

/**
 * @brief Slot for returning to the main menu.
 *
 * Shows the main window and hides the scores page.
 */
void MainWindow::returnToMainMenu() {
    this->show();
    if (scoresPage) {
        scoresPage->hide();
    }
}

/**
 * @brief Slot for handling the exit button click.
 *
 * Plays a click sound and quits the application when the exit button is clicked.
 */
void MainWindow::on_exitButton_clicked() {
    playAudio("Click.wav");
    QApplication::quit();
}
