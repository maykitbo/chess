cmake_minimum_required(VERSION 3.5)

project(chess_wibget LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

# копируем директорию img
FILE(
    COPY "${CMAKE_CURRENT_SOURCE_DIR}/../png"
    DESTINATION "${CMAKE_CURRENT_BINARY_DIR}"
)

SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11 -pthread")

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# find_package(Qt6 COMPONENTS Widgets REQUIRED)
find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(chess_wibget
  ../view/main.cpp
  ../view/widget.cpp
  ../view/widget.h
  ../view/widget.ui
  ../model/bot_move.cpp
  ../model/real_move.cpp
  ../model/human_move.cpp
  ../model/chessboard.cpp
  ../def_glob/global.cpp
  ../model/chessboard.h
  ../def_glob/chess_defines.h
  ../model/structs.h
  ../model/piece.cpp
  ../png/11.png
  ../png/10.png
  ../png/21.png
  ../png/20.png
  ../png/31.png
  ../png/30.png
  ../png/41.png
  ../png/40.png
  ../png/51.png
  ../png/50.png
  ../png/61.png
  ../png/60.png
  ../logs/log_speed.txt
  ../logs/logs.cpp
)

target_link_libraries (chess_wibget ${CMAKE_THREAD_LIBS_INIT})

# target_link_libraries(chess_wibget PRIVATE Qt6::Widgets)
target_link_libraries(chess_wibget PRIVATE Qt5::Widgets)
