Algorithm:
we noted that if we need to fill the (i, j) place, we are bound by the pieces we already filled in (i-1, j) and (i, j+1), dictating a left and top edges.

so when lookong for a solution, we dont need to try all the pieces, just the pieces that have that kind of left-top combo.

we sorted the pieces into a DS (PieceEQClasses) that saves the pieces by their left-top combo.


straight egdes:
when checking a mXn solution, we check if we have enough straight edges in the top (for m) and the left (for n)
(that number was already pre-processed..) if its not, we can rule out this solution without even trying it.
if no mXn combination worked in this manner, we can give an error on straight edges, that is not trivial.

design:
we preferred making piece not const in our solution, because we anticipate the next solution will in include rotation.