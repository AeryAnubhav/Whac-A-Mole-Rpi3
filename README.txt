README.txt

Whack-a-LED Game

==================
Compilation Guide
==================

To compile the Whack-a-LED game on your Raspberry Pi, follow these steps:

1. Open a terminal window.
2. Change directory to the location of your game source files. For example:
   cd ~/Desktop/group7/Whac-A-Mole

3. Compile and run the game using the following command:
   rm -r build
   mkdir -p build && cd build
   cmake ..
   cmake --build .
   mv Whac-A-Mole ..
   cd ..
   sudo ./Whac-A-Mole
   
Make sure you have the pigpio library and ncurses installed on your Raspberry Pi. If not, you can install them using:
   sudo apt-get update
   sudo apt-get install pigpio
   sudo apt-get install libncurses5-dev libncursesw5-dev
   sudo apt-get install cmake G++
   sudo apt-get install qtbase5-dev qt5-qmake qtbase5-dev-tools

================
Running the Game
================

To run the game, use the following command in the terminal window:

   sudo ./Whac-A-Mole

The 'sudo' command is necessary because the pigpio library requires root privileges to access the GPIO pins.

======================
Raspberry Pi Setup Guide
======================

Hardware Setup:

Your Raspberry Pi needs to be connected to a matrix of LEDs. Here's how to set up the hardware:

1. Connect the anode (positive, longer leg) of each LED to the corresponding GPIO pin on the Raspberry Pi.
2. Connect the cathode (negative, shorter leg) of each LED to a common ground (GND) on the Raspberry Pi.

Refer to the Raspberry Pi GPIO pinout diagram to identify the GPIO pins. For the game, we are using the following pins:

   GPIO 15, GPIO 24, GPIO 8, GPIO 20, 
   GPIO 14, GPIO 23, GPIO 7, GPIO 21,
   GPIO  3, GPIO 17, GPIO 5, GPIO 19, 
   GPIO  2, GPIO 27, GPIO 6, GPIO 26

Each GPIO pin corresponds to a button press as defined in the 'keyToLedMap' within the game code.

Ensure that the LEDs are properly connected to the GPIO pins mentioned above. It is recommended to use resistors to prevent damage to the LEDs and the Raspberry Pi.

Once you have set up the hardware, you can proceed to compile and run the game as described above.

Enjoy the game!

