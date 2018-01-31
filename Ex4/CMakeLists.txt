cmake_minimum_required(VERSION 3.9)
project(Ex4)

if (WIN32)
    set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror -pedantic-errors -DNDEBUG -static")
else()
    set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror -pedantic-errors -DNDEBUG")
endif (WIN32)

set(CMAKE_CXX_STANDARD 14)

add_executable(Ex4 main.cpp Piece.h Puzzle2dPiece.cpp Puzzle2dPiece.h Puzzle3dPiece.cpp Puzzle3dPiece.h TypesMap.cpp TypesMap.h ex4headers.h)