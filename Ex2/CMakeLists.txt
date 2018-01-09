cmake_minimum_required(VERSION 3.6)
project(PuzzleSolver)

set(CMAKE_CXX_STANDARD 14)

if (WIN32)
    set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror -pedantic-errors -DNDEBUG -static")
else()
    set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror -pedantic-errors -DNDEBUG")
endif (WIN32)

set(SOURCE_FILES Ex2/ex3.cpp Ex2/Piece.cpp Ex2/Piece.h Ex2/Board.cpp Ex2/Board.h Ex2/BoardErrors.cpp Ex2/BoardErrors.h Ex2/PieceEQClasses.cpp Ex2/PieceEQClasses.h Ex2/PieceRotationContainer.cpp Ex2/PieceRotationContainer.h Ex2/RotatableSolution.cpp Ex2/RotatableSolution.h Ex2/RotationContainer.cpp Ex2/RotationContainer.h)
add_executable(PuzzleSolver ${SOURCE_FILES})
