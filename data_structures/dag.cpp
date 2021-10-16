#include "dag.h"

#include <static/adjacent.h>
#include <iostream>
Dag::Dag()
{

}

//Aggiunge il nodo passato come parametro al vettore
void Dag::addToDag(const TriangleNode& triangleNode)
{
    dagNode.push_back(triangleNode);
}

//Restituisce il vettore contente i nodi i quali a loro volta contengono ciascuno un triangolo
std::vector<TriangleNode>& Dag::getVector()
{
    return dagNode;
}

//Restituisce la dimensione del vettore
unsigned long Dag::getSize()
{
    return static_cast<unsigned long>(dagNode.size());
}

//Restituisce l'i-esimo elemento (nodo) del vettore
TriangleNode Dag::get_nodes(unsigned long i)
{
    return dagNode.at(i);
}

/*Metodo che prende come parametro i che rappresenta il triangolo i-esimo e p che rappresenta il punto
 *del triangolo da restituire*/
cg3::Point2Dd Dag::getPoint_of_iNode(unsigned long i, unsigned long p)
{

    if(p==1) //accedo al nodo i e restituisco il first point del triangolo associato al nodo
        return dagNode.at(i).get_Triangle().getFirstPoint();
    else
        if(p==2)
            return dagNode.at(i).get_Triangle().getSecondPoint();
        else
            if(p==3)
                return dagNode.at(i).get_Triangle().getThirdPoint();

    return cg3::Point2Dd(0,0);
}

//Restituisce il figlio (l) del nodo corrente (i) in termini di indice del vettore
unsigned long Dag::getLabel_of_iNode(unsigned long i, unsigned long l)
{

    if(l==1)
        return dagNode.at(i).getLabelF1();
    else
        if(l==2)
            return dagNode.at(i).getLabelF2();
        else
            if(l==3)
                return dagNode.at(i).getLabelF3();;

    return 0;
}

/*Prende come parametro il punto da inserire e l'indice i del triangolo in cui cade quel punto,
 *crea i nodi e i triangoli corrispondenti andando a richiamare i vari metodi che aggiornano le informazioni dei nodi,
 * tra cui i figli, la visualizzazione e le adiacenze*/
void Dag::updateDag(const cg3::Point2Dd& point, unsigned long i)
{

    unsigned long size;

    //Creo i tre nuovi triangoli assegnando le coordinate in clockwise-order. Il primo triangolo sarà dato dal nuovo
    //punto, dal first point del triangolo in cui cade il punto e dal second point del triangolo in cui cade il punto.
    Triangle newTriangle1(point,dagNode.at(i).get_Triangle().getFirstPoint(), dagNode.at(i).get_Triangle().getSecondPoint());
    Triangle newTriangle2(point, dagNode.at(i).get_Triangle().getSecondPoint(), dagNode.at(i).get_Triangle().getThirdPoint());
    Triangle newTriangle3(point, dagNode.at(i).get_Triangle().getThirdPoint(), dagNode.at(i).get_Triangle().getFirstPoint());

    /*I nuovi nodi saranno formati dai triangoli, dall'etichetta del padre (i) e da quella dei figli (al momento della
     * creazione non avranno figli, quindi viene assegnata loro l'etichetta 0)*/
    TriangleNode newNode1(newTriangle1,i, 0,0,0);
    TriangleNode newNode2(newTriangle2,i, 0,0,0);
    TriangleNode newNode3(newTriangle3,i, 0,0,0);


    //Aggiungo i nodi al dag
    this->addToDag(newNode1);
    this->addToDag(newNode2);
    this->addToDag(newNode3);


    /*una volta che i nodi contenenti i triangoli sono stati inseriti nel dag, recupero l'indice del primo nodo
     *inserito tra gli ultimi tre*/
    size=this->getSize()-3;


    /*i rappresenta il nodo, e quindi il triangolo (dato che lo contiene)in cui cade il punto. Da quel triangolo
     * vengono quindi formati 3 nuovi triangoli. Allora, i figli di quel triangolo saranno appunto gli ultimi
     * 3 figli inseriti nel vettore. Il dag contiene i nodi, i quali, a loro volta, contengono i triangoli.*/
    dagNode.at(i).setFigli(true,size,size+1,size+2);

    /*Allo stesso modo, il triangolo in cui cade il punto sarà "sostituito" nella visualizzazione dai suoi figli,
     * cioè, dagli ultimi tre triangoli inseriti. Quindi quel triangolo non verrà stampato durante la
     * visualizzazione*/
    dagNode.at(i).setSalta();

    //Cerco gli adiacenti dei nuovi nodi inseriti (ultimi tre triangoli)
    Adjacent::setBrotherAdjacent(i,dagNode, false);



}

//Cancella ìl vettore dei nodi e per ognuno di essi i suoi adiacenti
 void Dag::clearDagNode()
{
     for(unsigned long i=0;i<dagNode.size();i++)
         dagNode.at(i).clearAdjacentVector();
     dagNode.clear();
}

//Richiama il metodo getFigli() che ci dice se il nodo i-esimo ha figli
bool Dag::takeChildrenFromNode(unsigned long i)
{
    return dagNode.at(i).getFigli();
}

//Il metodo getTriangleFromNode restituisce il triangolo contenuto nel nodo i-esimo
Triangle Dag::getTriangleFromNode(unsigned long i)
{
    return dagNode.at(i).get_Triangle();
}

