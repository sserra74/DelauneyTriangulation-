#ifndef DELAUNAYTRIANGULATION_H
#define DELAUNAYTRIANGULATION_H
#include <cg3/geometry/2d/point2d.h>
#include <data_structures/dag.h>
#include <data_structures/triangle.h>

class DelaunayT
{
public:
    DelaunayT();

    /*Inserisce il nuovo punto nella triangolazione andando anche a capire se l'inserimento
     * è fatto dall'utente o da file (parametro manual)*/
    void insertPointToTriangulation(const cg3::Point2Dd& point, bool manual);

    //Il metodo permette di controllare se il punto pnew cade nel traingolo i-esimo del vettore
    bool inside(const cg3::Point2Dd& pnew, unsigned long i);

    //Il metodo permette di creare il bounding triangle e il nodo associato da inserire nel dag
    Triangle insertBoundingTriangle(const cg3::Point2Dd& p1, const cg3::Point2Dd& p2, const cg3::Point2Dd& p3);

    //Restituisce l'oggetto dag
    Dag getDag();

    //Restituisce il vettore definito nel dag
    std::vector<TriangleNode> getVector();

    //Richiama il metodo per cancellare ìl vettore dei nodi e per ognuno di essi i suoi adiacenti
    void clear();

    //Il metodo searchTriangle prende come parametro il punto che vogliamo inserire e fa una ricerca per individuare
    //il triangolo in cui cade quel punto
    unsigned long searchTriangle(const cg3::Point2Dd& point);

    //pointAlreadyExist controlla che il punto che si sta tentando di inserire non sia già presente nella triangolazione
    bool pointAlreadyExist(unsigned long i, Dag& dag, const cg3::Point2Dd& point, bool manual);

private:
     Dag dag;
};

#endif // DELAUNAYTRIANGULATION_H
