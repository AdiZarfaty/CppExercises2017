data structure:
=========
we have a PieceRotationContainer class - its job is to hold an info on the rotation of a piece, and a pointer to the actual piece.
pieces instnces are saved uniqly, and many containers can point to the same actual piece.

on the piece itself is a flag to mark it as "used" in the solution or not.

Algorithm:
======
we noted that if we need to fill the (i, j) place, we are bound by the pieces we already filled in (i-1, j) and (i, j+1), dictating a left and top edges.

so when lookong for a solution, we dont need to try all the pieces, just the pieces that have that kind of left-top combo.

we sorted the pieces into a DS (PieceEQClasses) that saves PieceRotationContainer by their left-top combo.
in case of rotation, we simply fill pieces into those EQ several times. (each 1 of 4 rotations going into a suitable EQ)

when solving(i,j) we go in o(1) to our options list, and iterate over the pieces that where not used.

whenever we try an option, we note in a bool array its "type" (right and bottom edges, as top and lef were dictated..)
so for every options list, we never acctually try more then 9 types.

straight edges:
=========
when checking a mXn solution, we check if we have enough straight edges in the top (for m) and the left (for n)
(that number was already pre-processed..) if its not, we can rule out this solution without even trying it.
if no mXn combination worked in this manner, we can give an error on straight edges, that is not trivial.

for rotation, we count the number of straight edges and make sure we have enough to build a rectangle circumference