#include "trianglenode.h"
#include <data_structures/triangle.h>

TriangleNode::TriangleNode()
{
}
//TriangleNode::TriangleNode( DrawableTriangle* triangle, const int etichetta, const int etichetta_f1, const int etichetta_f2,const int etichetta_f3)
//{
//    this->triangle=triangle;
//    this->etichetta_p=etichetta;
//    this->etichetta_f1=etichetta_f1;
//    this->etichetta_f2=etichetta_f2;
//    this->etichetta_f3=etichetta_f3;
//}

TriangleNode::TriangleNode(Triangle* triangle, unsigned long etichetta, unsigned long etichetta_f1, unsigned long etichetta_f2, unsigned long etichetta_f3)
{
    this->triangle=triangle;
    this->etichetta_p=etichetta;
    this->etichetta_f1=etichetta_f1;
    this->etichetta_f2=etichetta_f2;
    this->etichetta_f3=etichetta_f3;
}
//DrawableTriangle* TriangleNode::  get_Triangle()
//{
//    return this->triangle;
//}
Triangle* TriangleNode::  get_Triangle() const
{
    return this->triangle;
}
int  TriangleNode:: getLabelF1()
{
       return this->etichetta_f1;
}
unsigned long    TriangleNode:: getLabelF2()
{
       return this->etichetta_f2;
}
unsigned long   TriangleNode:: getLabelF3()
{
       return this->etichetta_f3;
}
unsigned long TriangleNode::getLableP()
{
    return this->etichetta_p;
}
bool TriangleNode:: getFigli()
{
    return this->figli;
}
void TriangleNode:: setFigli(bool set,unsigned long a, unsigned long b,  unsigned long c)
{
    this->figli=set;
    this->etichetta_f1=a;
    this->etichetta_f2=b;
    this->etichetta_f3=c;

}

bool TriangleNode::assignPoint(unsigned long adjacent, std::vector<TriangleNode>& dag, unsigned long i, unsigned long loc,bool flip)
{

    cg3::Point2Dd thisA, thisB, thisC; //punti di questo triangolo
    cg3::Point2Dd a, b, c;

    //prendo i punti del nodo adiancente al padre
    a=dag.at(adjacent).get_Triangle()->getFirstPoint();
    b=dag.at(adjacent).get_Triangle()->getSecondPoint();
    c=dag.at(adjacent).get_Triangle()->getThirdPoint();
    if(flip==false)
    {
        thisA=this->get_Triangle()->getFirstPoint();
        thisB=this->get_Triangle()->getSecondPoint();
        thisC=this->get_Triangle()->getThirdPoint();
    }
    else
    {
        //prendo i punti del nuovo nodo creato
        thisA=dag.at(loc).get_Triangle()->getFirstPoint();
        thisB=dag.at(loc).get_Triangle()->getSecondPoint();
        thisC=dag.at(loc).get_Triangle()->getThirdPoint();
    }
    //Si controlla se un edge del triangolo corrente ha dei punti in comune con l'adiacente del padre
    if (
         ((thisA==a || thisA==b || thisA==c) && ((thisB==a || thisB==b || thisB==c) || (thisC==a || thisC==b || thisC==c)))
         || ((thisB==a || thisB==b || thisB==c) && ((thisA==a || thisA==b || thisA==c) || (thisC==a || thisC==b || thisC==c)))
         ||((thisC==a || thisC==b || thisC==c)&& ((thisB==a || thisB==b || thisB==c)||(thisA==a || thisA==b || thisA==c)))
       )
    {

        /*Cerco il padre (i) del triangolo corrente (in posizione loc)tra gli adiacenti dell'adiacente in questione
        Quando lo trovo sostituisco negli adiacenti il padre (i) con il suo figlio (loc) e viceversa
        Se prima avevo 1->2,3 e per 2->1,3, se 1 si divide in 3 figli, (4,5,6), nel 2 al posto di 1 ci andrà uno di questi
        nuovi figli. Poniamo che sia il quarto. 2 avrà adiacenti 4 (non più 1 ma il suo figlio) e 3. Mentre 4
        avrà tra i suoi adiacenti il 2*/
        if(dag.at(adjacent).adjacent.at(0)==i)
            dag.at(adjacent).adjacent[0]=loc;
        else if (dag.at(adjacent).adjacent.at(1)==i)
             dag.at(adjacent).adjacent[1]=loc;
        else if (dag.at(adjacent).getAdjacentVectorSize()==3  )
            if (dag.at(adjacent).adjacent.at(2)==i)
             dag.at(adjacent).adjacent[2]=loc;

         dag.at(loc).adjacent.push_back(adjacent);
         return true;
    }
    else //se un edge del triangolo corrente non ha dei punti in comune con l'adiacente del padre, restituisco false
    {
       // std::cout<<"Per il nodo "<<loc<<" non c'è nessun lato in comune con l'adiacente "<<adjacent<<std::endl;
        return false;
    }

//    if( (thisA==a && thisB==b) || (thisA==b && thisB==a) ||
//            (thisA==b && thisB==c) || (thisA==c && thisB==b) ||
//            (thisA==c && thisB==a) || (thisA==a && thisB==c))
//        {
//        if(dag.at(adjacent).adjacent.at(0)==i)
//                    dag.at(adjacent).adjacent[0]=loc;
//                else if (dag.at(adjacent).adjacent.at(1)==i)
//                     dag.at(adjacent).adjacent[1]=loc;
//                else if (dag.at(adjacent).getAdjacentVectorSize()==3  )
//                    if (dag.at(adjacent).adjacent.at(2)==i)
//                     dag.at(adjacent).adjacent[2]=loc;

//                 dag.at(loc).adjacent.push_back(adjacent);

//            return true;
//        }

//        //Check if the triangle t2 is adjacent to t1 on the edge BC

//        if( (thisB==a && thisC==b) || (thisB==b && thisC==a) ||
//            (thisB==b && thisC==c) || (thisB==c && thisC==b) ||
//            (thisB==c && thisC==a) || (thisB==a && thisC==c))
//        {
//            if(dag.at(adjacent).adjacent.at(0)==i)
//                        dag.at(adjacent).adjacent[0]=loc;
//                    else if (dag.at(adjacent).adjacent.at(1)==i)
//                         dag.at(adjacent).adjacent[1]=loc;
//                    else if (dag.at(adjacent).getAdjacentVectorSize()==3  )
//                        if (dag.at(adjacent).adjacent.at(2)==i)
//                         dag.at(adjacent).adjacent[2]=loc;

//                     dag.at(loc).adjacent.push_back(adjacent);

//            return true;
//        }

//        //Check if the triangle t2 is adjacent to t1 on the edge CA

//        if( (thisC==a && thisA==b) || (thisC==b && thisA==a) ||
//            (thisC==b && thisA==c) || (thisC==c && thisA==b) ||
//            (thisC==c && thisA==a) || (thisC==a && thisA==c))
//        {
//            if(dag.at(adjacent).adjacent.at(0)==i)
//                        dag.at(adjacent).adjacent[0]=loc;
//                    else if (dag.at(adjacent).adjacent.at(1)==i)
//                         dag.at(adjacent).adjacent[1]=loc;
//                    else if (dag.at(adjacent).getAdjacentVectorSize()==3  )
//                        if (dag.at(adjacent).adjacent.at(2)==i)
//                         dag.at(adjacent).adjacent[2]=loc;

//                     dag.at(loc).adjacent.push_back(adjacent);
//                     return true;

//        }

//        return false;





}
//void TriangleNode::addAdjacent()
//{
//    adjacent.push_back(0);
//    adjacent.push_back(0);
//    adjacent.push_back(0);
//}

//setAdjacent:
// - i: indice che indca il padre
// - dag: vettore contenente i nodi
// - loc: nuovo nodo inserito (figlio di i)
void TriangleNode::setAdjacent(unsigned long i, std::vector<TriangleNode>& dag, unsigned long loc, bool flip)
{
   unsigned long parent;
   unsigned long adjacent1, adjacent2;
//   int adjacent3=-1;
   unsigned long adjacent3=0;
   unsigned stop=false; //era bool
   cg3::Point2Dd thisA, thisB, thisC; //punti di questo triangolo

   parent=this->getLableP();//parent prende l'etichetta del padre, uguale a i

   //A seconda che il figlio del padre indicato da i sia il primo, il secondo o il terzo,
   //questo avrà come adiacenti i suoi fratelli

   //A seconda che il figlio dell'i-esimo padre sia il primo, il secondo o il terzo, inserisco
   //per quel figlio i suoi adiacenti in un vettore adjacent. I suoi adiacenti saranno innanzi tutto i suoi fratelli
   //Esempio: 0  1  2  3
   //         BT T1 T2 T3
   // 1 -> 2, 3 / 2 -> 1, 3 / 3-> 1, 2 come adiacenti
//   if(loc==1 || loc==2 || loc==3)
//        dag.at(loc).adjacent.push_back(0);
   if(dag.at(i).getLabelF1()==loc)
   {

       if(dag.at(i).getLabelF2()!=0)
            dag.at(loc).adjacent.push_back(dag.at(i).getLabelF2());
       if(dag.at(i).getLabelF3()!=0)
            dag.at(loc).adjacent.push_back(dag.at(i).getLabelF3());
   }
   else if(dag.at(i).getLabelF2()==loc)
   {
       if(dag.at(i).getLabelF1()!=0)
            dag.at(loc).adjacent.push_back(dag.at(i).getLabelF1());
       if(dag.at(i).getLabelF3()!=0)
            dag.at(loc).adjacent.push_back(dag.at(i).getLabelF3());
   }
   else if(dag.at(i).getLabelF3()==loc)
   {
       if(dag.at(i).getLabelF1()!=0)
            dag.at(loc).adjacent.push_back(dag.at(i).getLabelF1());
       if(dag.at(i).getLabelF2()!=0)
            dag.at(loc).adjacent.push_back(dag.at(i).getLabelF2());
   }

   //Se i nuovi triangoli inseriti non sono figli del Bounfing Triangle (i=0),
   //gli adicenti non saranno solo i fratelli
   if(i>0 && flip==false)
   {
       parent=this->getLableP();//parent prende l'etichetta del padre, uguale a i

       //andiamo a vedere quali sono i fratelli del padre
       adjacent1=dag.at(parent).adjacent.at(0);
       adjacent2=dag.at(parent).adjacent.at(1);

//       for(int i=1;i<loc;i++)
//       {
//           std::cout << "///////////////////////////////////////////////"<<std::endl;
//           std::cout << "adiacente di: " <<i <<" : "<<dag.at(i).adjacent.at(0)<<std::endl;
//           std::cout << "adiacente di: " <<i <<" : "<<dag.at(i).adjacent.at(1)<<std::endl;
//           if(dag.at(i).adjacent.size()==3)
//               std::cout << "adiacente di: " <<i <<" : "<<dag.at(i).adjacent.at(2)<<std::endl;
//            std::cout << "///////////////////////////////////////////////"<<std::endl;
//       }
//       std::cout << "adiacente di: " <<parent <<" : "<<adjacent1<<std::endl;
//       std::cout << "adiacente di: " <<parent <<" : "<<adjacent2<<std::endl;


       //A seconda dei casi, il nodo può avere 2 o 3 adiacenti
       if(dag.at(parent).adjacent.size()==3)
           adjacent3=dag.at(parent).adjacent.at(2);

       //adiacent1 è il primo adiacente del padre
       //dag è il vettore
       //i è il padre
       //loc è l'indice del nuovo nodo inserito
       stop=assignPoint(adjacent1, dag, i, loc, false);
       if(stop==false)
            stop=assignPoint(adjacent2, dag, i, loc,false);//punti del secondo fratello del padre
        if(stop==false && adjacent3!=0 )
            assignPoint(adjacent3, dag, i, loc, false);
   }
//   std::cout << "padre: " <<parent<<std::endl;
//   std::cout << "adjacent1: " << adjacent1<<std::endl;
//   std::cout << "adjacent2: " << adjacent2<<std::endl;
//   std::cout << "adjacent3: " << adjacent3<<std::endl;
//   std::cout << "figlio corrente: " <<loc<<std::endl;
//   std::cout << "Fadj1: " <<  dag.at(loc).adjacent.at(0)<<std::endl;
//   std::cout << "Fadj2: " << dag.at(loc).adjacent.at(1)<<std::endl;
//   if(dag.at(loc).adjacent.size()==3)
//   std::cout << "Fadj3: " << dag.at(loc).adjacent.at(2)<<std::endl;
//    std::cout << "------------------------------------------- " <<std::endl;
////   for(unsigned j=0;j<dag.at(loc).adjacent.size();j++)
////         std::cout <<"figlio "<<i<<": adiacente " << j<< " = "<<adjacent.at(j)<<std::endl ;
}
unsigned long TriangleNode::getAdjacent(unsigned long i)
{
    return this->adjacent.at(i);
}
unsigned long TriangleNode::getAdjacentVectorSize()
{
    return adjacent.size();
}
const cg3::Point2Dd TriangleNode::getThirdPoint(const cg3::Point2Dd& pr, const cg3::Point2Dd& p2, const cg3::Point2Dd& p3, unsigned long adjacent, std::vector<TriangleNode>& dag)
{
//    if(dag.at(adjacent).get_Triangle()->getFirstPoint() != pr && dag.at(adjacent).get_Triangle()->getFirstPoint()!=p2 && dag.at(adjacent).get_Triangle()->getFirstPoint()!=p3)
//        return dag.at(adjacent).get_Triangle()->getFirstPoint();
//    else
//       if(dag.at(adjacent).get_Triangle()->getSecondPoint() != pr && dag.at(adjacent).get_Triangle()->getSecondPoint()!=p2 && dag.at(adjacent).get_Triangle()->getSecondPoint()!=p3)
//           return dag.at(adjacent).get_Triangle()->getSecondPoint();
//       else
//          if(dag.at(adjacent).get_Triangle()->getThirdPoint() != pr && dag.at(adjacent).get_Triangle()->getThirdPoint()!=p2 && dag.at(adjacent).get_Triangle()->getThirdPoint()!=p3)
//              return dag.at(adjacent).get_Triangle()->getThirdPoint();

    if((dag.at(adjacent).get_Triangle()->getFirstPoint()==p2 && dag.at(adjacent).get_Triangle()->getSecondPoint()==p3) || (dag.at(adjacent).get_Triangle()->getFirstPoint()==p3 && dag.at(adjacent).get_Triangle()->getSecondPoint()==p2))
        {

            return dag.at(adjacent).get_Triangle()->getThirdPoint();
        }

        if((dag.at(adjacent).get_Triangle()->getFirstPoint()==p2 && dag.at(adjacent).get_Triangle()->getThirdPoint()==p3) || (dag.at(adjacent).get_Triangle()->getFirstPoint()==p3 && dag.at(adjacent).get_Triangle()->getThirdPoint()==p2))
        {

            return dag.at(adjacent).get_Triangle()->getSecondPoint();
        }

        if((dag.at(adjacent).get_Triangle()->getSecondPoint()==p2 && dag.at(adjacent).get_Triangle()->getThirdPoint()==p3) || (dag.at(adjacent).get_Triangle()->getSecondPoint()==p3 && dag.at(adjacent).get_Triangle()->getThirdPoint()==p2))
        {

            return dag.at(adjacent).get_Triangle()->getFirstPoint();
        }
}
void TriangleNode::setAdjacentFlip(std::vector<TriangleNode>& dag, unsigned long size, unsigned long adjacent)
{

    unsigned long adj1=0, adj2=0;
//    int adj3=-1;
    unsigned long adj3=0;
    //setto i figli dei padri



    if(size==23)
    {
        dag.at(dag.at(size).getLableP()).setSalta(dag);
        dag.at(adjacent).setSalta(dag);
    //     dag.at(size).setSalta(dag, false);
    //     dag.at(adjacent).setSalta(dag, true);

         //Imposto come figli del padre di questo nodo, i due nuovi nodi creati che saranno figli anche
         //dell'adiacente
         dag.at(dag.at(size).getLableP()).setFigli(true,size, size+1, 0);
         dag.at(adjacent).setFigli(true,size,size+1,0);


        //A questo punto prendo gli adiacenti a questo nodo
        adj1=this->adjacent.at(0);
        adj2=this->adjacent.at(1);
        if(this->adjacent.size()==3)//un triangolo potrebbe avere solo 2 adiacenti
            adj3=this->adjacent.at(2);

        //Setto gli adiacenti
         dag.at(size).setAdjacent(dag.at(size).getLableP(),dag,size, true);


         dag.at(size+1).setAdjacent(dag.at(size+1).getLableP(),dag,size+1, true);//size

        if(adjacent!=adj1)
        {
            dag.at(size).assignPoint(adj1, dag, dag.at(size).getLableP(), size, true);
            dag.at(size+1).assignPoint(adj1, dag, dag.at(size+1).getLableP(), size+1, true);
        }

        if(adjacent!=adj2)
        {
            dag.at(size).assignPoint(adj2, dag, dag.at(size).getLableP(), size, true);
            dag.at(size+1).assignPoint(adj2, dag, dag.at(size+1).getLableP(), size+1, true);
        }
        if(adj3!=0 && adj3!=adjacent)
        {
            dag.at(size).assignPoint(adj3, dag, dag.at(size).getLableP(), size, true);
            dag.at(size+1).assignPoint(adj3, dag, dag.at(size+1).getLableP(), size+1, true);
        }

        //controllo il secondo padre
        adj1=dag.at(adjacent).getAdjacent(0);
        adj2=dag.at(adjacent).getAdjacent(1);

        adj3=0;
        if(dag.at(adjacent).getAdjacentVectorSize()==3)
            adj3=dag.at(adjacent).getAdjacent(2);

        if(adj1!=dag.at(size).getLableP())//se qualche adiacente di 2 è diverso a 5
        {
             dag.at(size).assignPoint(adj1, dag,  adjacent, size, true);//2 come padre: adjacnet
             dag.at(size+1).assignPoint(adj1, dag,  adjacent, size+1, true);//2 come padre: adjacnet

        }
        if(adj2!=dag.at(size).getLableP())//se qualche adiacente di 2 è diverso a 5
        {
            dag.at(size).assignPoint(adj2, dag,  adjacent, size, true);//2 come padre: adjacnet
            dag.at(size+1).assignPoint(adj2, dag,  adjacent, size+1, true);//2 come padre: adjacnet
        }
        if(adj3!=0 && adj3!=dag.at(size).getLableP())//se qualche adiacente di 2 è diverso a 5
        {
            dag.at(size).assignPoint(adj3, dag,  adjacent, size, true);//2 come padre: adjacnet
            dag.at(size+1).assignPoint(adj3, dag,  adjacent, size+1, true);//2 come padre: adjacnet
        }
    }
    else {






















    //Per quanto riguarda la stampa dei triangoli, vengono settati a false i triangoli che non devono
    //essere saltati e a true quelli da saltare.
    //In generale si può dire che, quando per esempio nel triangolo 1 viene posto punto, vengono creati
    //3 nuovi traingoli che andranno a sostituire nella stampa il genitore.
    dag.at(dag.at(size).getLableP()).setSalta(dag);
    dag.at(adjacent).setSalta(dag);
//     dag.at(size).setSalta(dag, false);
//     dag.at(adjacent).setSalta(dag, true);

     //Imposto come figli del padre di questo nodo, i due nuovi nodi creati che saranno figli anche
     //dell'adiacente
     dag.at(dag.at(size).getLableP()).setFigli(true,size, size+1, 0);
     dag.at(adjacent).setFigli(true,size,size+1,0);


    //A questo punto prendo gli adiacenti a questo nodo
    adj1=this->adjacent.at(0);
    adj2=this->adjacent.at(1);
    if(this->adjacent.size()==3)//un triangolo potrebbe avere solo 2 adiacenti
        adj3=this->adjacent.at(2);

    //Setto gli adiacenti
     dag.at(size).setAdjacent(dag.at(size).getLableP(),dag,size+1, true);


     dag.at(size+1).setAdjacent(dag.at(size+1).getLableP(),dag,size, true);//size

    if(adjacent!=adj1)
    {
        dag.at(size).assignPoint(adj1, dag, dag.at(size).getLableP(), size, true);
        dag.at(size+1).assignPoint(adj1, dag, dag.at(size+1).getLableP(), size+1, true);
    }

    if(adjacent!=adj2)
    {
        dag.at(size).assignPoint(adj2, dag, dag.at(size).getLableP(), size, true);
        dag.at(size+1).assignPoint(adj2, dag, dag.at(size+1).getLableP(), size+1, true);
    }
    if(adj3!=0 && adj3!=adjacent)
    {
        dag.at(size).assignPoint(adj3, dag, dag.at(size).getLableP(), size, true);
        dag.at(size+1).assignPoint(adj3, dag, dag.at(size+1).getLableP(), size+1, true);
    }

    //controllo il secondo padre
    adj1=dag.at(adjacent).getAdjacent(0);
    adj2=dag.at(adjacent).getAdjacent(1);

    adj3=0;
    if(dag.at(adjacent).getAdjacentVectorSize()==3)
        adj3=dag.at(adjacent).getAdjacent(2);

    if(adj1!=dag.at(size).getLableP())//se qualche adiacente di 2 è diverso a 5
    {
         dag.at(size).assignPoint(adj1, dag,  adjacent, size, true);//2 come padre: adjacnet
         dag.at(size+1).assignPoint(adj1, dag,  adjacent, size+1, true);//2 come padre: adjacnet

    }
    if(adj2!=dag.at(size).getLableP())//se qualche adiacente di 2 è diverso a 5
    {
        dag.at(size).assignPoint(adj2, dag,  adjacent, size, true);//2 come padre: adjacnet
        dag.at(size+1).assignPoint(adj2, dag,  adjacent, size+1, true);//2 come padre: adjacnet
    }
    if(adj3!=0 && adj3!=dag.at(size).getLableP())//se qualche adiacente di 2 è diverso a 5
    {
        dag.at(size).assignPoint(adj3, dag,  adjacent, size, true);//2 come padre: adjacnet
        dag.at(size+1).assignPoint(adj3, dag,  adjacent, size+1, true);//2 come padre: adjacnet
    }

    }
}
void TriangleNode::setSalta(std::vector<TriangleNode>& dag /*,bool exception*/)
{
//    int label;
//    if(exception==true)
        this->salta=true;

//    label=getLableP();
//     dag.at(label).salta=true;

//     std::cout<<"label: "<<label<<std::endl;
//    while(label>0)
//    {
//        dag.at(label).salta=true;
//        label=dag.at(label).getLableP();
//    }

}
bool TriangleNode::getSalta() const
{
    return this->salta;
}

void TriangleNode::clearAdjacentVector()
{
    adjacent.clear();
}
