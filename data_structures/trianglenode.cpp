#include "trianglenode.h"
#include <data_structures/triangle.h>

TriangleNode::TriangleNode()
{
}

//Costruttore che setta il triangolo del nodo, l'etichetta del padre e dei figli
TriangleNode::TriangleNode(Triangle triangle, unsigned long etichetta, unsigned long etichetta_f1, unsigned long etichetta_f2, unsigned long etichetta_f3)
{
    this->triangle=triangle;
    this->etichetta_p=etichetta;
    this->etichetta_f1=etichetta_f1;
    this->etichetta_f2=etichetta_f2;
    this->etichetta_f3=etichetta_f3;
}


//Restituisce il triangolo associato al nodo
Triangle TriangleNode::get_Triangle() const
{
    return this->triangle;
}

//Restituisce l'indice della posizione del primo figlio del nodo corrente
unsigned long  TriangleNode:: getLabelF1()
{
       return this->etichetta_f1;
}

//Restituisce l'indice della posizione del secondo figlio del nodo corrente
unsigned long    TriangleNode:: getLabelF2()
{
       return this->etichetta_f2;
}

//Restituisce l'indice della posizione del terzo figlio del nodo corrente
unsigned long   TriangleNode:: getLabelF3()
{
       return this->etichetta_f3;
}

//Restituisce l'indice della posizione del padre del nodo corrente
unsigned long TriangleNode::getLableP()
{
    return this->etichetta_p;
}

//Restituisce true se il nodo ha figli, false altrimenti
bool TriangleNode:: getFigli()
{
    return this->figli;
}

/*Setta i figli del nodo corrente dove set rappresenta un booleano (true se il nodo ha figli, false altrimenti)
 * e a,b e c sono gli indici dei figli di quel nodo all'interno del vettore*/
void TriangleNode:: setFigli(bool set,unsigned long a, unsigned long b,  unsigned long c)
{
    this->figli=set;
    this->etichetta_f1=a;
    this->etichetta_f2=b;
    this->etichetta_f3=c;

}

//Restituisce l'adiacente i-esimo del nodo corrente
unsigned long TriangleNode::getAdjacent(unsigned long i) const
{
    return this->adjacent.at(i);
}

//Restituisce la dimensione del vettore adjacent
unsigned long TriangleNode::getAdjacentVectorSize() const
{
    return adjacent.size();
}

//Metodo utilizzato per settare la visualizzazione del nodo e quindi del triangolo ad esso associato durante la stampa
void TriangleNode::setSalta()
{
        this->salta=true;
}

//Restituisce true se il triangolo associato al nodo non deve essere stampato durante la visualizzazione, false altrimenti
bool TriangleNode::getSalta() const
{
    return this->salta;
}

//Aggiunge l'adiacente passato come parametro al vettore adjacent del nodo corrente
void TriangleNode::addAdjacent(unsigned long newAdjacent)
{
    adjacent.push_back(newAdjacent);
}

//Sostituisce nella posizione i-esima l'adiacente con l'indice del nuovo adiacente
void TriangleNode::replaceAdjacent(unsigned long i, unsigned long newAdjacent)
{
    adjacent[i]=newAdjacent;
}

//Trova l'adiacente che ha l'edge (p2,p3) in comune con il nodo corrente (index). Avrà come parametri il dag e i punti
unsigned long TriangleNode::findAdjacent(std::vector<TriangleNode>& dag, const cg3::Point2Dd& p2, const cg3::Point2Dd& p3)
{
    //prendo gli adiacenti del nodo corrente
    unsigned long adjacent1=this->getAdjacent(0);
    unsigned long  adjacent2=this->getAdjacent(1);
    unsigned long adjacent3=0;
    if(this->getAdjacentVectorSize()==3)//se il nodo ha un terzo adiacente
         adjacent3=this->getAdjacent(2);

    //controllo quale degli adiacenti al triangolo associato al nodo corrente ha l'edge (p2,p3) in comune
    if((dag.at(adjacent1).get_Triangle().getFirstPoint()==p2 || dag.at(adjacent1).get_Triangle().getSecondPoint()==p2
        || dag.at(adjacent1).get_Triangle().getThirdPoint()==p2)
        && (dag.at(adjacent1).get_Triangle().getFirstPoint()==p3 || dag.at(adjacent1).get_Triangle().getSecondPoint()==p3
            || dag.at(adjacent1).get_Triangle().getThirdPoint()==p3))
    {
        return adjacent1;
    }

    else if((dag.at(adjacent2).get_Triangle().getFirstPoint()==p2 || dag.at(adjacent2).get_Triangle().getSecondPoint()==p2
             || dag.at(adjacent2).get_Triangle().getThirdPoint()==p2)
             && (dag.at(adjacent2).get_Triangle().getFirstPoint()==p3 || dag.at(adjacent2).get_Triangle().getSecondPoint()==p3
                 || dag.at(adjacent2).get_Triangle().getThirdPoint()==p3))
    {
        return adjacent2;
    }
    else if(adjacent3!=0)
        if((dag.at(adjacent3).get_Triangle().getFirstPoint()==p2 || dag.at(adjacent3).get_Triangle().getSecondPoint()==p2
            || dag.at(adjacent3).get_Triangle().getThirdPoint()==p2)
            && (dag.at(adjacent3).get_Triangle().getFirstPoint()==p3 || dag.at(adjacent3).get_Triangle().getSecondPoint()==p3
                || dag.at(adjacent3).get_Triangle().getThirdPoint()==p3))
            {
                return adjacent3;
            }


    return 0; //restituisco 0 se gli adiacenti di quel nodo non hanno in comune il lato (p2,p3)
}

//Cancella il contenuto del vettore adjacent
void TriangleNode::clearAdjacentVector()
{
    adjacent.clear();
}

