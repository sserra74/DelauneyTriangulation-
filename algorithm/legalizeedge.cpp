#include "legalizeedge.h"
#include <cg3/geometry/2d/utils2d.h>
#include <utils/delaunay_checker.h>
#include <Eigen/Geometry>
#include <static/adjacent.h>

LegalizeEdge::LegalizeEdge()
{

}

/*Il metodo isLegal permette di controllare la legalità del lato effettuando flip se necessario.Per ogni nuovo nodo
 *inserito si richiama isLegal, a cui si passano i punti del triangolo associato a  quel nodo, la posizione corrente
 *di quel nodo (index) nel vettore, e il vettore*. pr è il punto che è stato inserito, mentre p2 e p3 sono i punti
 *che formano l'edge su cui eseguire il flip se necessario*/
void LegalizeEdge::isLegal(const cg3::Point2Dd& pr, const cg3::Point2Dd& p2, const cg3::Point2Dd& p3, unsigned long index,Dag& dag)
{

  cg3::Point2Dd pk;

  /*Di questi nuovi nodi creati (contenenti i triangoli), findAdjacent trova l'adiacente che ha l'edge (p2,p3)
   *in comune con il il triangolo associato al nodo corrente (index)*/
  unsigned long adjacent =dag.get_nodes(index).findAdjacent(dag.getVector(), p2, p3);

  if(adjacent!=0) //se ce n'è uno
  {
      //prendo il terzo punto (quello non in comune) del triangolo adiacente a quello corrente
      pk=dag.getTriangleFromNode(adjacent).getOppositePoint(p2,p3);

      if(cg3::isPointLyingInCircle(pr,p2,p3, pk, false)) //Se l'edge non è legale
      {

          //Creo due nuovi triangoli e due nuovi nodi con le nuove informazioni
          Triangle newT1(pr,p2,pk);
          TriangleNode sub1(newT1, index,0,0, 0);

          Triangle newT2(pr,pk,p3);
          TriangleNode sub2(newT2, index,0, 0, 0);

          //Aggiungo i nodi al dag
          dag.addToDag(sub1);
          dag.addToDag(sub2);


          /*Modifico le adiacenze in base ai nuovi nodi inseriti prendendo come riferimento la posizione del primo nuovo nodo
           *inserito nel dag. Per le nuove adiacenze ci sarà bisogno di considerare il nodo da cui si è richiamato
           * il legalize (index), la posizione del primo triangolo creato da quest'ultimo (dag.getsize()-2),
           * l'adiacente trovato con findAdjacent, e il dag */
          Adjacent::FlipAdjacence(index, static_cast<unsigned long>(dag.getSize()-2), adjacent, dag.getVector());

          //Richiamo il legalize sui nuovi triangoli
          isLegal(newT1.getFirstPoint(),newT1.getSecondPoint(),newT1.getThirdPoint(),
                  dag.getLabel_of_iNode(index,1),dag);
          isLegal(newT2.getFirstPoint(),newT2.getSecondPoint(),newT2.getThirdPoint(),
                  dag.getLabel_of_iNode(index,2),dag );
      }
  }
}



