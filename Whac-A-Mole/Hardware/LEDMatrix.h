#ifndef LEDMATRIX_H
#define LEDMATRIX_H

#include <unordered_map>
#include <random>

/**
 * @class LEDMatrix
 * @brief Manages an LED matrix by mapping keys to specific LED GPIO pins.
 *
 * This class is responsible for associating specific keys with LED GPIO pins and
 * controlling the lighting of these LEDs. It includes functionality to light up a random LED.
 * @author Anubhav Aery
 */
class LEDMatrix {
public:
    /**
     * @brief Constructor for LEDMatrix.
     *
     * Initializes the LEDMatrix with a predefined mapping of keys to LED GPIO pins.
     */
    LEDMatrix();

    /**
     * @brief Lights up a random LED in the matrix.
     *
     * Selects a random LED to light up based on the current LED pin, ensuring a different LED is chosen.
     * It uses a random number generator to select a LED.
     *
     * @param currentLedPin The GPIO pin number of the currently lit LED.
     * @return The GPIO pin number of the newly lit LED.
     */
    int lightUpRandomLED(int currentLedPin);

    /**
     * @brief Retrieves the mapping of keys to LED GPIO pins.
     *
     * Provides access to the map that links specific keys with their corresponding LED GPIO pins.
     *
     * @return A constant reference to the unordered map of keys to LED GPIO pins.
     */
    const std::unordered_map<char, int>& getKeyToLedMap() const;

private:
    std::unordered_map<char, int> keyToLedMap; ///< Map linking keys to LED GPIO pins.
};

#endif // LEDMATRIX_H
