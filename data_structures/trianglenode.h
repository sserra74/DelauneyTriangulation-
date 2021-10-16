#ifndef TRIANGLENODE_H
#define TRIANGLENODE_H

#include "drawable/drawabletriangle.h"
#include "data_structures/triangle.h"

class TriangleNode
{
public:
    TriangleNode();

    //Costruttore che setta il triangolo del nodo, l'etichetta del padre e dei figli
    TriangleNode(Triangle triangle, unsigned  long etichetta_p, unsigned long etichetta_f1, unsigned long etichetta_f2, unsigned long etichetta_f3);

    //Restituisce il triangolo associato al nodo
    Triangle get_Triangle() const;

    //Restituisce l'indice della posizione del primo figlio del nodo corrente
    unsigned long getLabelF1();

    //Restituisce l'indice della posizione del secondo figlio del nodo corrente
    unsigned long getLabelF2();

    //Restituisce l'indice della posizione del terzo figlio del nodo corrente
    unsigned long getLabelF3();

    //Restituisce l'indice della posizione del padre del nodo corrente
    unsigned long getLableP();

    //Restituisce true se il nodo ha figli, false altrimenti
    bool getFigli();

    /*Setta i figli del nodo corrente dove set rappresenta un booleano (true se il nodo ha figli, false altrimenti)
     * e a,b e c sono gli indici dei figli di quel nodo all'interno del vettore*/
    void setFigli(bool set, unsigned long a, unsigned long b,  unsigned long  c);

    //Restituisce l'adiacente i-esimo del nodo corrente
    unsigned long getAdjacent(unsigned long i) const;

    //Restituisce la dimensione del vettore adjacent
    unsigned long getAdjacentVectorSize() const;

    //Metodo utilizzato per settare la visualizzazione del nodo e quindi del triangolo ad esso associato durante la stampa
    void setSalta();

    //Restituisce true se il triangolo associato al nodo non deve essere stampato durante la visualizzazione, false altrimenti
    bool getSalta() const;

    //Aggiunge l'adiacente passato come parametro al vettore adjacent del nodo corrente
    void addAdjacent(unsigned long newAdjacent);

    //Sostituisce nella posizione i-esima l'adiacente con l'indice del nuovo adiacente
    void replaceAdjacent(unsigned long i, unsigned long newAdjacent);

    //Trova l'adiacente che ha l'edge (p2,p3) in comune con il nodo corrente (index). Avrà come parametri il dag e i punti
    unsigned long findAdjacent(std::vector<TriangleNode>& dag, const cg3::Point2Dd& p2, const cg3::Point2Dd& p3);

    //Cancella il contenuto del vettore adjacent
    void clearAdjacentVector();

private:

    //etichette che rappresentano gli indici del padre e dei figli del nodo corrente nel vettore
    unsigned long etichetta_p;
    unsigned long etichetta_f1;
    unsigned long  etichetta_f2;
    unsigned long etichetta_f3=0;


    bool figli=false;
    bool salta=false;

    //vettore di adiacenti per il nodo corrente
    std::vector<unsigned long> adjacent;

    //Ogni nodo contiene il corrispettivo triangolo
    Triangle triangle;
};

#endif // TRIANGLENODE_H
