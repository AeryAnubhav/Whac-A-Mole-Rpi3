#include "mainwindow.h"
#include <QApplication>

/**
 * @file main.cpp
 * @brief Entry point for the Qt application.
 *
 * This file contains the main function, which initializes the QApplication,
 * sets up the main window, and starts the event loop.
 * @author Yangxiuye Gu
 */

/**
 * @brief Main entry point for the Qt application.
 *
 * Initializes the QApplication, plays a startup audio file, creates the main window,
 * and enters the main event loop of the application.
 *
 * @param argc Argument count.
 * @param argv Argument vector.
 * @return Integer signaling successful completion.
 */
int main(int argc, char *argv[])
{
    QApplication app(argc, argv); // Initialize the Qt application
    playAudio("gameSound.mp3"); // Play an audio file at startup
    
    MainWindow mainWindow; // Create the main window
    mainWindow.show(); // Display the main window

    return app.exec(); // Enter the main event loop of the application
}
