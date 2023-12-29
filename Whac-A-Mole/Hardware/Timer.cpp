#include "Timer.h"
#include <iostream>
#include <algorithm>
#include <chrono>

/**
 * @class Timer
 * @brief Manages a countdown timer for a game.
 *
 * This class provides functionalities for starting, stopping, and checking a countdown timer.
 * It is used to keep track of the remaining time in a game scenario.
 * @author Anubhav Aery
 */
Timer::Timer() : timeLeft(30) {}

/**
 * @brief Starts the countdown timer.
 *
 * Initiates the countdown timer for the specified duration (default 30 seconds).
 * The end time is set based on the current time plus the countdown duration.
 */
void Timer::start() {
    endTime = std::chrono::system_clock::now() + std::chrono::seconds(timeLeft);
    std::cout << "Timer started!\n";
}

/**
 * @brief Stops the countdown timer.
 *
 * Stops the timer and prints a message indicating that the timer has been stopped.
 */
void Timer::stop() {
    std::cout << "Timer stopped!\n";
}

/**
 * @brief Retrieves the time left on the timer.
 *
 * Calculates and returns the remaining time in seconds. If the time is up, returns zero.
 *
 * @return The time left in seconds, or zero if the time is up.
 */
int Timer::getTimeLeft() const {
    auto now = std::chrono::system_clock::now();
    auto durationLeft = std::chrono::duration_cast<std::chrono::seconds>(endTime - now);
    return std::max(0, static_cast<int>(durationLeft.count()));
}

/**
 * @brief Checks if the timer's countdown has completed.
 *
 * Returns true if the current time is greater than or equal to the end time of the timer.
 *
 * @return True if the timer's time is up, false otherwise.
 */
bool Timer::isTimeUp() const {
    return std::chrono::system_clock::now() >= endTime;
}
