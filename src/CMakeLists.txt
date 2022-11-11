cmake_minimum_required(VERSION 3.5)

project(chess_wibget LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

# копируем директорию img
FILE(
    COPY "${CMAKE_CURRENT_SOURCE_DIR}/png"
    DESTINATION "${CMAKE_CURRENT_BINARY_DIR}"
)

SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11 -pthread")

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

# if(ANDROID)
#   add_library(chess_wibget SHARED
#     main.cpp
#     widget.cpp
#     widget.h
#     widget.ui
#   )
# else()
  add_executable(chess_wibget
    main.cpp
    widget.cpp
    widget.h
    widget.ui
    bot_move.cpp
    real_move.cpp
    human_move.cpp
    chessboard.cpp
    global.cpp
    chessboard.h
    chess_defines.h
    structs.h
    piece.cpp
    png/11.png
    png/1-1.png
    png/21.png
    png/2-1.png
    png/31.png
    png/3-1.png
    png/41.png
    png/4-1.png
    png/51.png
    png/5-1.png
    png/61.png
    png/6-1.png
    log_speed.txt
  )
# endif()

target_link_libraries (chess_wibget ${CMAKE_THREAD_LIBS_INIT})

target_link_libraries(chess_wibget PRIVATE Qt5::Widgets)
