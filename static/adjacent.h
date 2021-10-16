#ifndef ADJACENT_H
#define ADJACENT_H
#include <data_structures/trianglenode.h>

class Adjacent
{
public:
    Adjacent();

    //Setta i primi adiacenti dei figli del nodo: inizialmente si considerano i fratelli dei figli del nodo
    static void setBrotherAdjacent(unsigned long i, std::vector<TriangleNode>& dag, bool flip);

    //Va alla ricerca degli adiacenti dei nuovi nodi che possono avere in comune con il padre
    static void addAdjacentinCommonwithParent(unsigned long parent, unsigned long child, std::vector<TriangleNode>& dag);

    //Permette di associare le adiacenze del padre ai figli
    static bool checkAdjacency(std::vector<TriangleNode>& dag,unsigned long adjacentP,unsigned long parent, unsigned long child);

    //Permette di modificare le adiacenze una volta che si è verificato il flip
    static void FlipAdjacence(unsigned long parent, unsigned long dagSize, unsigned long parent2, std::vector<TriangleNode>& dag);
};

#endif // ADJACENT_H
