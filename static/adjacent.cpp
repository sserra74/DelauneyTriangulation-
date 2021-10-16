#include "adjacent.h"

Adjacent::Adjacent()
{

}

/*Setta i primi adiacenti dei figli del nodo: inizialmente si considerano i fratelli dei figli del nodo.Prende
 *come parametro il padre dei nuovi nodi (triangolo) inseriti, il dag e un parametro flip che ci dice
 *se l'adiacenza è dovuta al flip (true) oppure no (false)*/
void Adjacent::setBrotherAdjacent(unsigned long parent, std::vector<TriangleNode>& dag, bool flip)
{
    unsigned long f1, f2, f3=0;

    //Si accede al nodo genitore ottenendo gli indici in cui sono salvati i figli
    f1= dag.at(parent).getLabelF1();
    f2=dag.at(parent).getLabelF2();
    if(dag.at(parent).getLabelF3()>0)//Se il nodo ha anche un terzo figlio (impostato a 0 se non ha quel figlio)
        f3= dag.at(parent).getLabelF3();

    if(flip==false) //se l'adiacenza non è dovuta al flip, avremo 3 figli e ognuno prenderà i suoi fratelli come adiacenti
    {
        dag.at(f1).addAdjacent(f2);
        dag.at(f1).addAdjacent(f3);

        dag.at(f2).addAdjacent(f1);
        dag.at(f2).addAdjacent(f3);

        dag.at(f3).addAdjacent(f1);
        dag.at(f3).addAdjacent(f2);
    }

    else //altrimenti, se l'adiacenza si considera l'adiacenza dopo un flip, avremo solo 2 figli, ognuno con adiacente il fratello
    {
        dag.at(f1).addAdjacent(f2);
        dag.at(f2).addAdjacent(f1);
    }

    //Una volta che si creano i nuovi triangoli dentro un triangolo, questi triangoli avranno degli adiacenti del genitore
    if(parent > 0 && flip==false)
    {
        addAdjacentinCommonwithParent(parent, f1, dag);
        addAdjacentinCommonwithParent(parent, f2, dag);
        addAdjacentinCommonwithParent(parent, f3, dag);
    }

}

/*Va alla ricerca degli adiacenti dei nuovi nodi che possono avere in comune con il padre. Prende come parametro il padre
 *dei nuovi triangoli inseriti, il figlio di cui si stanno verificando le adiacenze in comune con il padre, e il dag*/
void Adjacent:: addAdjacentinCommonwithParent(unsigned long parent, unsigned long child, std::vector<TriangleNode>& dag)
{
    //Prendo gli adiacenti del padre
    unsigned long adjacent1= dag.at(parent).getAdjacent(0);
    unsigned long adjacent2= dag.at(parent).getAdjacent(1);
    unsigned long adjacent3 = 0;
    bool check=false;

    if(dag.at(parent).getAdjacentVectorSize()==3)//se il padre ha anche un terzo adiacente
        adjacent3=dag.at(parent).getAdjacent(2);

    /*Vediamo se gli adiacenti del padre hanno un lato in comune con il figlio passato per parametro
     *in modo da aggiornare gli adiacenti*/
    check=checkAdjacency(dag, adjacent1,parent, child);
    if(check==false)
        check=checkAdjacency(dag, adjacent2,parent, child);
    if(check==false && adjacent3!=0)
        check=checkAdjacency(dag, adjacent3,parent, child);


}

/*Permette di associare le adiacenze del padre ai figli. Avrà per parametro il dag, l'indice dell'adiacente del padre,
 *l'indice del padre e l'indice del figlio*/
bool Adjacent::checkAdjacency(std::vector<TriangleNode>& dag,unsigned long adjacentP, unsigned long parent, unsigned long child)
{
    cg3::Point2Dd thisA, thisB, thisC; //punti di questo triangolo
    cg3::Point2Dd a, b, c;

    //prendo i punti del nodo adiancente al padre
    a=dag.at(adjacentP).get_Triangle().getFirstPoint();
    b=dag.at(adjacentP).get_Triangle().getSecondPoint();
    c=dag.at(adjacentP).get_Triangle().getThirdPoint();

    //prendo i punti del figlio
    thisA=dag.at(child).get_Triangle().getFirstPoint();
    thisB=dag.at(child).get_Triangle().getSecondPoint();
    thisC=dag.at(child).get_Triangle().getThirdPoint();

    //Se hanno qualche lato in comune
    if (
         ((thisA==a || thisA==b || thisA==c) && ((thisB==a || thisB==b || thisB==c) || (thisC==a || thisC==b || thisC==c)))
         || ((thisB==a || thisB==b || thisB==c) && ((thisA==a || thisA==b || thisA==c) || (thisC==a || thisC==b || thisC==c)))
         ||((thisC==a || thisC==b || thisC==c)&& ((thisB==a || thisB==b || thisB==c)||(thisA==a || thisA==b || thisA==c)))
       )
    {


        //Individuo la posizione in cui l'adiacente contiene come adiacente il padre e sostituisco con il figlio
        if(dag.at(adjacentP).getAdjacent(0)==parent)
            dag.at(adjacentP).replaceAdjacent(0,child);
        else if (dag.at(adjacentP).getAdjacent(1)==parent)
             dag.at(adjacentP).replaceAdjacent(1,child);
        else if (dag.at(adjacentP).getAdjacentVectorSize()==3  )
            if (dag.at(adjacentP).getAdjacent(2)==parent)
             dag.at(adjacentP).replaceAdjacent(2,child);

        //Faccio il procedimento inverso: aggiungo al figlio l'adiacente del padre
         dag.at(child).addAdjacent(adjacentP);
         return true;
    }
    else
        return false;
}

//Permette di modificare le adiacenze una volta che si è verificato il flip
void Adjacent::FlipAdjacence(unsigned long parent, unsigned long dagSize, unsigned long parent2, std::vector<TriangleNode>& dag)
{
    unsigned long adjP1, adjP2, adjP3=0;

    //I due nuovi triangoli avranno ora due padri. Inoltre i padri saranno "saltabili" durante la stampa
    dag.at(parent).setFigli(true, dagSize, dagSize+1, 0);
    dag.at(parent).setSalta();
    dag.at(parent2).setFigli(true, dagSize, dagSize+1, 0);
    dag.at(parent2).setSalta();

    //Prendo gli adiacenti del primo padre
    adjP1=dag.at(parent).getAdjacent(0);
    adjP2=dag.at(parent).getAdjacent(1);
    if(dag.at(parent).getAdjacentVectorSize()==3)
        adjP3= dag.at(parent).getAdjacent(2);

    setBrotherAdjacent(parent,dag,true); //per prima cosa inserisco come adiacenti dei nuovi nodi i rispettivi fratelli

    /*Cerco gli adiacenti del padre che siano diversi dal secondo padre dei nuovi nodi, perchè ora questi adiacenti
     * saranno adiacenti dei nuovi nodi inseriti*/

    if(adjP1!=parent2)
    {
        checkAdjacency(dag, adjP1, parent, dagSize);
        checkAdjacency(dag, adjP1, parent, dagSize+1);
    }
    if(adjP2!=parent2)
    {
        checkAdjacency(dag, adjP2, parent, dagSize);
        checkAdjacency(dag, adjP2, parent, dagSize+1);
    }
    if(adjP3!=parent2 && adjP3!=0)
    {
        checkAdjacency(dag, adjP3, parent, dagSize);
        checkAdjacency(dag, adjP3, parent, dagSize+1);
    }

    //Ripeto il procedimento con il secondo padre
    adjP1=dag.at(parent2).getAdjacent(0);
    adjP2=dag.at(parent2).getAdjacent(1);
    adjP3=0;
    if(dag.at(parent2).getAdjacentVectorSize()==3)
        adjP3= dag.at(parent2).getAdjacent(2);

    if(adjP1!=parent)
    {
        checkAdjacency(dag, adjP1, parent2, dagSize);
        checkAdjacency(dag, adjP1, parent2, dagSize+1);
    }
    if(adjP2!=parent)
    {
        checkAdjacency(dag, adjP2, parent2, dagSize);
        checkAdjacency(dag, adjP2, parent2, dagSize+1);
    }
    if(adjP3!=parent && adjP3!=0)
    {
        checkAdjacency(dag, adjP3, parent2, dagSize);
        checkAdjacency(dag, adjP3, parent2, dagSize+1);
    }
}
