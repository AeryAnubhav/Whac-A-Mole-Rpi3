#include "playpage.h"
#include "mainwindow.h"
#include "HardwareInterface.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QThread>
#include <QTimer>
#include <QDebug>
#include "scorespage.h"

PlayPage::PlayPage(const QSize &size, QWidget *parent)
    : QWidget(parent), hardwareInterface(new HardwareInterface(this)) {
    setFixedSize(size);
    setStyleSheet("QWidget { background-color: #857be6; }"
                  "QLabel { font-size: 20px; color: #FFD700; text-align: center; }"
                  "QLineEdit { font-size: 18px; color: black; background-color: white; border-radius: 5px; padding: 10px; margin-bottom: 15px; text-align: center; border: 2px solid #FFD700; }");

    QVBoxLayout *layout = new QVBoxLayout(this);

    QLineEdit *usernameInput = new QLineEdit(this);
    usernameInput->setPlaceholderText("Enter your name");
    layout->addWidget(usernameInput, 0, Qt::AlignCenter);

    QPushButton *startButton = new QPushButton(this);
    QPixmap startButtonPixmap("start.png");
    startButtonPixmap = startButtonPixmap.scaled(QSize(190, 80), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    startButton->setIcon(QIcon(startButtonPixmap));
    startButton->setIconSize(startButtonPixmap.size());
    startButton->setFixedSize(QSize(190, 80));
    startButton->setStyleSheet("border: none; background-color: transparent;");
    layout->addWidget(startButton, 0, Qt::AlignCenter);

    QLabel *welcomeLabel = new QLabel(this);
    layout->addWidget(welcomeLabel, 0, Qt::AlignCenter);

    QLabel *countdownLabel = new QLabel("You have 30 seconds", this);
    layout->addWidget(countdownLabel, 0, Qt::AlignCenter);

    QLabel *scoreLabel = new QLabel("", this);
    layout->addWidget(scoreLabel, 0, Qt::AlignCenter);

    QTimer *updateTimer = new QTimer(this);
    int timeLeft = 30;
    
    QPushButton *rankButton = new QPushButton(this);
    QPixmap rankButtonPixmap("main.png");
    rankButtonPixmap = rankButtonPixmap.scaled(QSize(190, 80), Qt::KeepAspectRatio, Qt::SmoothTransformation); // Adjust size as needed
    rankButton->setIcon(QIcon(rankButtonPixmap));
    rankButton->setIconSize(rankButtonPixmap.size());
    rankButton->setFixedSize(QSize(190, 80)); // Adjust size as needed
    rankButton->setStyleSheet("border: none; background-color: transparent;");
    layout->addWidget(rankButton, 0, Qt::AlignHCenter);
    // Connect the clicked signal to the start game slot
    connect(rankButton, &QPushButton::clicked, this, &PlayPage::rankDisplay);
    rankButton->setEnabled(false);

    connect(startButton, &QPushButton::clicked, this, [this, usernameInput, welcomeLabel, startButton, updateTimer, scoreLabel, &timeLeft]() {
        QString playerName = usernameInput->text();
        if (!playerName.isEmpty()) {
            welcomeLabel->setText("Get Ready, " + playerName + "!");
            hardwareInterface->handleGame(playerName);
            startButton->setDisabled(true);
            usernameInput->setDisabled(true);
            scoreLabel->setText(QString("Game Started"));
            timeLeft = 30; // Reset the countdown to 30 seconds
            playAudio("Click.wav");
            updateTimer->start(1000); // Update the countdown every second
        } else {
            welcomeLabel->setText("Please enter your name!");
            welcomeLabel->setStyleSheet("color: red;");
        }
    });

    connect(hardwareInterface, &HardwareInterface::scoreUpdated, this, [scoreLabel](int newScore) {
        scoreLabel->setText(QString("Score: %1").arg(newScore));
    });

    connect(hardwareInterface, &HardwareInterface::countdownUpdated, this, [countdownLabel](int timeLeft) {
        countdownLabel->setText("Time left: " + QString::number(timeLeft));
    });

    connect(hardwareInterface, &HardwareInterface::gameEnded, this, [this, startButton, usernameInput, scoreLabel, rankButton]() {
        //playAudio("over.wav");
        //startButton->setEnabled(true);
        //usernameInput->setEnabled(true);
        int finalScore = hardwareInterface->getFinalScore();
        scoreLabel->setText(QString("Final Score: %1").arg(finalScore));
        rankButton->setEnabled(true);

    });

    setLayout(layout);
    
    
}

PlayPage::~PlayPage() {
    // Cleanup if needed
}

void PlayPage::rankDisplay() {
    playAudio("Click.wav");
    playAudio("gameSound.mp3");
    MainWindow* mainPage = new MainWindow();
    mainPage->show();
    this->hide();
}
