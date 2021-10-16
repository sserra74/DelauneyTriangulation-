#ifndef DAG_H
#define DAG_H

#include <data_structures/trianglenode.h>
class Dag
{
public:
    Dag();

    //Aggiunge il nodo passato come parametro al vettore
    void addToDag(const TriangleNode& triangle);

//    Triangle getTriangle(unsigned long i);

    //Restituisce la dimensione del vettore
    unsigned long getSize();

    //Restituisce l'i-esimo elemento (nodo) del vettore
    TriangleNode get_nodes(unsigned long i);

    /*Il metodo updateDag prende come parametro il punto da inserire e l'indice i del triangolo in cui cade quel punto,
     *crea i nodi e triangoli corrispondenti andando a richiamare i vari metodi che aggiornano le informazioni dei nodi,
     * tra cui i figli, la visualizzazione e le adiacenze*/
    void updateDag(const cg3::Point2Dd& point, unsigned long i);

    //Restituisce il vettore contente i nodi i quali a loro volta contengono ciascuno un triangolo
    std::vector<TriangleNode>& getVector();

    //Cancella ìl vettore dei nodi e per ognuno di essi i suoi adiacenti
    void clearDagNode();

    /*Prende come parametri i che rappresenta il triangolo i-esimo e p che rappresenta il punto
     * del triangolo da restituire*/
    cg3::Point2Dd getPoint_of_iNode(unsigned long i, unsigned long p);

    //Restituisce il figlio (l) del nodo corrente (i) in termini di indice del vettore
    unsigned long getLabel_of_iNode(unsigned long i, unsigned long l);

    //Richiama il metodo getFigli() che ci dice se il nodo i-esimo ha figli
    bool takeChildrenFromNode(unsigned long i);

    //Il metodo getTriangleFromNode restituisce il triangolo contenuto nel nodo i-esimo
    Triangle getTriangleFromNode(unsigned long i);

private:

    //Vettore di nodi contenenti i triangoli
     std::vector<TriangleNode> dagNode;
};

#endif // DAG_H
