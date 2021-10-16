#include "delaunayt.h"
#include <cg3/geometry/2d/utils2d.h>
#include <utils/delaunay_checker.h>
#include <algorithm/legalizeedge.h>
#include <QMessageBox>

DelaunayT::DelaunayT()
{

}

//Il metodo permette di creare il bounding triangle e il nodo associato da inserire nel dag
Triangle DelaunayT::insertBoundingTriangle(const cg3::Point2Dd& p1, const cg3::Point2Dd& p2, const cg3::Point2Dd& p3)
{
    Triangle boundingTriangle(p1,p2, p3); //p1,p2 e p3 sono i punti del triangolo

    //il nodo prende come parametro il triangolo, l'etichetta del padre e quelle dei figli (che saranno 1,2,3)
    TriangleNode boundingT(boundingTriangle, 0, 1,2,3);

    //si aggiunge il nodo al dag
    this->dag.addToDag(boundingT);

    return boundingTriangle;
}

//Il metodo permette di controllare se il punto pnew cade nel traingolo i-esimo del vettore
bool DelaunayT::inside(const cg3::Point2Dd& pnew, unsigned long i)
{

   //La funzione getPoint_ofInode restituisce i punti del triangolo i. Con il secondo parametro viene indicato quale
   //punto restiuire: 1 per il first point del triangolo i, 2 per il second e 3 per il third.
   return cg3::isPointLyingInTriangle(dag.getPoint_of_iNode(i,1), dag.getPoint_of_iNode(i,2), dag.getPoint_of_iNode(i,3),pnew, true);

}

//Restituisce l'oggetto dag
Dag DelaunayT::getDag()
{
    return dag;
}

//Il metodo searchTriangle prende come parametro il punto che vogliamo inserire e fa una ricerca per individuare
//il triangolo in cui cade quel punto
unsigned long DelaunayT::searchTriangle(const cg3::Point2Dd& point)
{
    unsigned long i=0;
    unsigned long k=0;
    bool check=false;

    //scorro il vettore fino a quando il nodo i-esimo ha dei figli.
    for(i=0;dag.takeChildrenFromNode(i)==true;i=k)
    {

        //Controllo se il punto è dentro al 1° figlio del nodo i
        check=inside(point, dag.getLabel_of_iNode(i,1));

        //se è così, aggiorno k con l'indice del figlio del nodo i-esimo. Nel for i=k in modo tale da
        //andare in profondità considerando solo i figli dei nodi e non i fratelli
        if(check==true)
            k=dag.getLabel_of_iNode(i,1);
        else //altrimenti considero gli altri figli
        {
            check=inside(point, dag.getLabel_of_iNode(i,2));
            if(check==false)
            {
                check=inside(point, dag.getLabel_of_iNode(i,3));
                if(check==true)
                    k=dag.getLabel_of_iNode(i,3);
            }
            else
                k=dag.getLabel_of_iNode(i,2);
        }
    }
    return i;
}


//pointAlreadyExist controlla che il punto che si sta tentando di inserire non sia già presente nella triangolazione
//Il metodo avrà come parametri i per indicare il triangolo che si sta esaminando, il dag per recuperare
//dal nodo il triangolo, il punto che si sta tentando di inserire e la modalità di inserimento:
//manual=true se l'inserimento del punto è fatto dall'utente, false se è fatto da file
bool DelaunayT::pointAlreadyExist(unsigned long i, Dag& dag, const cg3::Point2Dd& point, bool manual)
{
    if(manual==true)//se l'inserimento è fatto dall'utente
    {
        //controllo che il punto sia diverso da quelli che compongono il triangolo i-esimo. Dal dag accedo al nodo
        //i-esimo che conterrà il triangolo di cui si vogliono controllare i punti
        if(dag.get_nodes(i).get_Triangle().getFirstPoint()!=point && dag.get_nodes(i).get_Triangle().getSecondPoint()!=point
            && dag.get_nodes(i).get_Triangle().getThirdPoint()!=point)
             return false;
        else {
            QMessageBox::warning(nullptr,"Point is already exists","Non puoi inserire un punto nelle stesse coordinate");
            return true;
        }
    }
    else //se invece l'inserimento viene fatto tramite file
    {
        if(dag.get_nodes(i).get_Triangle().getFirstPoint()!=point && dag.get_nodes(i).get_Triangle().getSecondPoint()!=point
            && dag.get_nodes(i).get_Triangle().getThirdPoint()!=point)
             return false;
        else {

            return true;
        }
    }
    return false;


}

/*Inserisce il nuovo punto nella triangolazione andando anche a capire se l'inserimento
 * è fatto dall'utente o da file (parametro manual)*/
void DelaunayT::insertPointToTriangulation(const cg3::Point2Dd& point, bool manual)
{

    unsigned long i=0;
    unsigned long index;
    bool check=false;

    if(dag.getSize()==1)//Se il vettore ha un triangolo (all'inizio avrà solo il Bounding Triangle)
         check=inside(point, 0);//controllo che il punto inserito sia dentro quel triangolo (in posizione 0 del vettore)
    else // Dal momento che si è inserito il primo punto creando quindi 3 triangoli + il bounding Triangle
        i=searchTriangle(point); //Cerco l'indice del triangolo in cui cade il punto

    check=false;
    //Per evitare punti doppi, controllo se il punto è già stato inserito
    check=pointAlreadyExist(i, dag, point, manual);

    if(check==false) //se il punto non è già stato inserito
    {
        dag.updateDag(point, i); //Aggiorno il dag con i nuovi nodi e le corrette relazioni tra di essi

        //Legalize
        index=static_cast<unsigned long>(dag.getSize()-3); //index indica il primo dei nuovi nodi inseriti nel vettore

        /*Per ogni nuovo nodo inserito si richiama isLegal, a cui si passano i punti del triangolo associati a quel
         *nodo, la posizione corrente di quel nodo (index) e il vettore. Il primo punto passato è quello inserito
         *mentre, il secondo e il terzo punto sono quelli che formano l'edge su cui eseguire il flip se necessario*/
        LegalizeEdge::isLegal(dag.getPoint_of_iNode(index,1),
                             dag.getPoint_of_iNode(index,2),
                             dag.getPoint_of_iNode(index,3), index, dag);
        index=index+1;
        LegalizeEdge::isLegal(dag.getPoint_of_iNode(index,1),
                             dag.getPoint_of_iNode(index,2),
                             dag.getPoint_of_iNode(index,3), index, dag);

       index=index+1;
        LegalizeEdge::isLegal(dag.getPoint_of_iNode(index,1),
                             dag.getPoint_of_iNode(index,2),
                             dag.getPoint_of_iNode(index,3), index, dag);
    }


}

//Richiama il metodo per cancellare ìl vettore dei nodi e per ognuno di essi i suoi adiacenti
void DelaunayT::clear()
{
    dag.clearDagNode();
}

//Restituisce il vettore definito nel dag
std::vector<TriangleNode> DelaunayT::getVector()
{
    return dag.getVector();
}
