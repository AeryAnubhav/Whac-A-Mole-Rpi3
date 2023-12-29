cmake_minimum_required(VERSION 3.5)

project(Whac-A-Mole VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SDL2 REQUIRED)
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

# Find the pigpio and ncurses libraries on the system
find_library(PIGPIO_LIBRARY pigpio)
find_library(NCURSES_LIBRARY ncurses)

set(HARDWARE_SOURCES
        Hardware/Timer.cpp
        Hardware/LEDMatrix.cpp
        Hardware/Player.cpp
        Hardware/HighScore.cpp
        Hardware/GameController.cpp
        HardwareInterface.cpp  # Add your HardwareInterface.cpp here
)

set(HARDWARE_HEADERS
        Hardware/Timer.h
        Hardware/LEDMatrix.h
        Hardware/Player.h
        Hardware/HighScore.h
        Hardware/GameController.h
        HardwareInterface.h   # Add your HardwareInterface.h here
)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        gamepage.cpp
        gamepage.h
        scorespage.cpp
        scorespage.h
        playpage.cpp
        playpage.h
        ${HARDWARE_SOURCES}
        ${HARDWARE_HEADERS}
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Whac-A-Mole
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(Whac-A-Mole SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(Whac-A-Mole
            ${PROJECT_SOURCES}
        )
    endif()
endif()

# Link against the Qt Widgets, pigpio, and ncurses libraries
target_link_libraries(Whac-A-Mole PRIVATE 
    Qt${QT_VERSION_MAJOR}::Widgets
    ${PIGPIO_LIBRARY}
    ${NCURSES_LIBRARY}
    pthread
    ${SDL2_LIBRARIES}
    SDL2_mixer
)

set_target_properties(Whac-A-Mole PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.Whac-A-Mole
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS Whac-A-Mole
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Whac-A-Mole)
endif()

