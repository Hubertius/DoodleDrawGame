# Generated from DoodleDrawClient.pro.

cmake_minimum_required(VERSION 3.16)
project(DoodleDrawClient VERSION 1.0 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)

if(NOT DEFINED INSTALL_EXAMPLESDIR)
    set(INSTALL_EXAMPLESDIR "examples")
endif()

set(INSTALL_EXAMPLEDIR "${INSTALL_EXAMPLESDIR}")

find_package(QT NAMES Qt5 Qt6 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Gui Quick WebSockets)

qt_add_executable(DoodleDrawClient WIN32 MACOSX_BUNDLE
    Controllers/gamemanager.cpp Controllers/gamemanager.h
    Controllers/messageprocessorhandler.cpp Controllers/messageprocessorhandler.h
    Controllers/websockethandler.cpp Controllers/websockethandler.h
    main.cpp
)
target_link_libraries(DoodleDrawClient PUBLIC
    Qt::Core
    Qt::Gui
    Qt::Quick
    Qt::WebSockets
)


# Resources:
set(qml_resource_files
    "main.qml"
    "ui/DoodleScreen.qml"
    "ui/DrawingInstructionScreen.qml"
    "ui/GameButton.qml"
    "ui/GameSelectScreen.qml"
    "ui/JoinLobbyScreen.qml"
    "ui/LobbyScreen.qml"
    "ui/MainMenuScreen.qml"
    "ui/VoteScreen.qml"
    "ui/WaitingForPlayersScreen.qml"
    "ui/WinnerScreen.qml"
    "ui/assets/check.png"
)

qt6_add_resources(DoodleDrawClient "qml"
    PREFIX
        "/"
    FILES
        ${qml_resource_files}
)

install(TARGETS DoodleDrawClient
    RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
    BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)
