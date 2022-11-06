# Generated from DoodleDrawServer.pro.

cmake_minimum_required(VERSION 3.16)
project(DoodleDrawServer VERSION 1.0 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)

if(NOT DEFINED INSTALL_EXAMPLESDIR)
    set(INSTALL_EXAMPLESDIR "examples")
endif()

set(INSTALL_EXAMPLEDIR "${INSTALL_EXAMPLESDIR}")

find_package(QT NAMES Qt5 Qt6 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS WebSockets)

qt_add_executable(DoodleDrawServer
    gamelobbyhandler.cpp gamelobbyhandler.h
    gamemanager.cpp gamemanager.h
    main.cpp
    messageprocessor.cpp messageprocessor.h
    websockethandler.cpp websockethandler.h
)
target_link_libraries(DoodleDrawServer PUBLIC
    Qt::Core
    Qt::WebSockets
)

install(TARGETS DoodleDrawServer
    RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
    BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)
