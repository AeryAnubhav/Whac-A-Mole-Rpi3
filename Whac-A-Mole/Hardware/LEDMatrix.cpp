#include "LEDMatrix.h"
#include <pigpio.h>
#include <random>

/**
 * @class LEDMatrix
 * @brief Manages the mapping and control of LEDs in a matrix layout.
 *
 * This class is responsible for associating keys with specific LEDs in the matrix
 * and controlling these LEDs, including lighting up a random LED.
 * @author Anubhav Aery
 */
LEDMatrix::LEDMatrix() {
    // Initialize LED pin numbers
    keyToLedMap = {
            {'4', 15}, {'5', 24}, {'6', 8}, {'7', 20},
            {'r', 14}, {'t', 23}, {'y', 7}, {'u', 21},
            {'f', 3}, {'g', 17}, {'h', 5}, {'j', 19},
            {'v', 2}, {'b', 27}, {'n', 6}, {'m', 26}
    };
}

/**
 * @brief Lights up a random LED in the matrix.
 *
 * Selects a random LED to light up, ensuring it is different from the currently lit LED.
 * The LED is lit by writing a high signal to the corresponding GPIO pin.
 *
 * @param currentLedPin The GPIO pin number of the currently lit LED.
 * @return The GPIO pin number of the newly lit LED.
 */
int LEDMatrix::lightUpRandomLED(int currentLedPin) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, keyToLedMap.size() - 1);
    int randomIndex = distrib(gen);
    for (auto &led : keyToLedMap) {
        if (randomIndex-- == 0) {
            currentLedPin = led.second;
            gpioWrite(currentLedPin, 1); // Turn on the new LED
            break;
        }
    }
    return currentLedPin;
}

/**
 * @brief Retrieves the map linking keys to LED GPIO pins.
 *
 * Provides access to the internal map that associates keys with specific GPIO pins controlling LEDs.
 *
 * @return A constant reference to the key-to-LED GPIO pin map.
 */
const std::unordered_map<char, int>& LEDMatrix::getKeyToLedMap() const {
    return keyToLedMap;
}
