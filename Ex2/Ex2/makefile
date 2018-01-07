COMP = g++-5.3.0
#g++-5.3.0
#put all your object files here
OBJS = Board.o BoardErrors.o ex3.o Piece.o PieceEQClasses.o RotatableSolution.o PieceRotationContainer.o SolutionFoundChecker.o

#The executabel filename DON'T CHANGE
EXEC = ex3

CPP_COMP_FLAG = -std=c++14 -Wall -Wextra \
-Werror -pedantic-errors -DNDEBUG


$(EXEC): $(OBJS)
	$(COMP) -pthread $(OBJS) -o ex3
#a rule for building a simple c++ source file
#use g++ -MM ex3.cpp to see dependencies

SolutionFoundChecker.o: SolutionFoundChecker.h
	$(COMP) $(CPP_COMP_FLAG) -c  SolutionFoundChecker.cpp

Board.o: Board.cpp Board.h Piece.h BoardErrors.h PieceEQClasses.h RotatableSolution.h PieceRotationContainer.h
	$(COMP) $(CPP_COMP_FLAG) -c Board.cpp

BoardErrors.o: BoardErrors.cpp BoardErrors.h
	$(COMP) $(CPP_COMP_FLAG) -c BoardErrors.cpp

ex3.o: ex3.cpp Board.h
	$(COMP) $(CPP_COMP_FLAG) -c ex3.cpp

PieceRotationContainer.o: PieceRotationContainer.cpp PieceRotationContainer.h Piece.h
	$(COMP) $(CPP_COMP_FLAG) -c PieceRotationContainer.cpp

Piece.o: Piece.cpp Piece.h
	$(COMP) $(CPP_COMP_FLAG) -c Piece.cpp

PieceEQClasses.o: PieceEQClasses.cpp PieceEQClasses.h Piece.h
	$(COMP) $(CPP_COMP_FLAG) -c PieceEQClasses.cpp

RotatableSolution.o: RotatableSolution.cpp RotatableSolution.h Piece.h PieceEQClasses.h PieceRotationContainer.h
	$(COMP) $(CPP_COMP_FLAG) -c RotatableSolution.cpp
clean:
	rm -f $(OBJS) $(EXEC)
