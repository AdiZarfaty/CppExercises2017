COMP = g++-5.3.0
#put all your object files here
OBJS = Puzzle2dPiece.o Puzzle3dPiece.o TypesMap.o main.o

#The executabel filename DON'T CHANGE
EXEC = ex4

CPP_COMP_FLAG = -std=c++14 -Wall -Wextra \
-Werror -pedantic-errors -DNDEBUG


$(EXEC): $(OBJS)
	$(COMP) $(OBJS) -o ex4
#a rule for building a simple c++ source file
#use g++ -MM ex2.cpp to see dependencies

Puzzle2dPiece.o: Puzzle2dPiece.cpp Puzzle2dPiece.h Piece.h
	$(COMP) $(CPP_COMP_FLAG) -c Puzzle2dPiece.cpp

Puzzle3dPiece.o: Puzzle3dPiece.cpp Puzzle3dPiece.h Piece.h
	$(COMP) $(CPP_COMP_FLAG) -c Puzzle3dPiece.cpp

TypesMap.o: TypesMap.cpp TypesMap.h
	$(COMP) $(CPP_COMP_FLAG) -c TypesMap.cpp

main.o: main.cpp Puzzle2dPiece.h Puzzle3dPiece.h
	$(COMP) $(CPP_COMP_FLAG) -c main.cpp


clean:
	rm -f $(OBJS) $(EXEC)
