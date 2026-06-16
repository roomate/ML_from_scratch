#include <stdlib.h>
#include <iostream>
#include <limits>
#include "Graph.h"

#define INF std::numeric_limits<double>::infinity();

Graph::Graph(int Nb): nb_point(Nb)
{
    if (Nb ==0) {nodes=nullptr;}
    else
    {
        nodes=new Node[Nb];
    }
}

Graph::Graph(int Nb, Node& nod, int val): nb_point(Nb)
{
    nodes=new Node[Nb];
    for (int i=0; i<Nb; ++i) {nodes[i].val=val;}
}