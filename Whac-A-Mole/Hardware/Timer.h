#ifndef TIMER_H
#define TIMER_H

#include <chrono>

/**
 * @class Timer
 * @brief Manages a countdown timer for timing events in a game.
 *
 * This class is responsible for starting a countdown timer, stopping it,
 * and providing information about the time left and whether the time is up.
 * It uses the std::chrono library for time measurements.
 * @author Anubhav Aery
 */
class Timer {
public:
    /**
     * @brief Constructor for Timer.
     *
     * Initializes a new Timer instance, setting the initial time left for the countdown.
     */
    Timer();

    /**
     * @brief Starts the countdown timer.
     *
     * Sets the end time for the timer based on the current time and the initial time left.
     */
    void start();

    /**
     * @brief Stops the countdown timer.
     *
     * Stops the timer, preventing any further countdown.
     */
    void stop();

    /**
     * @brief Retrieves the time left on the timer.
     *
     * Calculates and returns the remaining time in seconds. If the time is up, returns zero.
     *
     * @return The time left in seconds, or zero if the time is up.
     */
    int getTimeLeft() const;

    /**
     * @brief Checks if the timer's countdown has completed.
     *
     * Returns true if the current time is greater than or equal to the end time of the timer.
     *
     * @return True if the timer's time is up, false otherwise.
     */
    bool isTimeUp() const;

private:
    int timeLeft; ///< The initial time left for the countdown in seconds.
    std::chrono::time_point<std::chrono::system_clock> endTime; ///< The end time point for the timer.
};

#endif // TIMER_H
