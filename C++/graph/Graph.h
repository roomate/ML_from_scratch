#ifndef Graph_H
#define Graph_H

#include <stdlib.h>
#include <iostream>
#include <limits>

#define INF std::numeric_limits<double>::infinity();

typedef struct
{
    int id;//Node's ID.
    float val; //The value stored by the node.
    Node* next; //Pointer to its neighbors.
} Node;


class Graph{
public:
    int nb_point;
    Node* nodes;

    Graph(int Nb=0);
    Graph(int Nb, Node& nod, int val=0);

    void add_node(Node& node);
};

#endif