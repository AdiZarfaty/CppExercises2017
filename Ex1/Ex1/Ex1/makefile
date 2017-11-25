COMP = g++-5.3.0
#put all your object files here
OBJS = Board.o BoardErrors.o Ex1.o Piece.o PieceEQClasses.o Solution.o

#The executabel filename DON'T CHANGE
EXEC = ex1

CPP_COMP_FLAG = -std=c++14 -Wall -Wextra \
-Werror -pedantic-errors -DNDEBUG


$(EXEC): $(OBJS)
	$(COMP) $(OBJS) -o ex1
#a rule for building a simple c++ source file
#use g++ -MM main.cpp to see dependencies
Board.o: Board.cpp Board.h Piece.h BoardErrors.h PieceEQClasses.h Solution.h
	$(COMP) $(CPP_COMP_FLAG) -c Board.cpp

BoardErrors.o: BoardErrors.cpp BoardErrors.h
	$(COMP) $(CPP_COMP_FLAG) -c BoardErrors.cpp

Ex1.o: Ex1.cpp Board.h
	$(COMP) $(CPP_COMP_FLAG) -c Ex1.cpp

Piece.o: Piece.cpp Piece.h
	$(COMP) $(CPP_COMP_FLAG) -c Piece.cpp

PieceEQClasses.o: PieceEQClasses.cpp PieceEQClasses.h Piece.h
	$(COMP) $(CPP_COMP_FLAG) -c PieceEQClasses.cpp

Solution.o: Solution.cpp Solution.h Piece.h PieceEQClasses.h
	$(COMP) $(CPP_COMP_FLAG) -c Solution.cpp
clean:
	rm -f $(OBJS) $(EXEC)
