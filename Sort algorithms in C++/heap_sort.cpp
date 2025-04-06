#include <iostream>
#include <cstdlib>
#include<vector>
#include<string>
#include "heap_sort.hpp"
using namespace std;

////////////////////////////////////////////////////////////
/////////////////////Heap Sort//////////////////////////////
////////////////////////////////////////////////////////////


bool is_heap(const vector<float> P, const string str)
{
    int size_ = P.size()/2;
    string state = "decrease";
    string state2 = "increase";
    if (str == state)
    {
        for (int i = 0; i < size_; i++)
        {
            if (P[2*i + 1] > P[i]) {return false;}
            if ((2*i + 2 < size_) && (P[2*i + 2] > P[i])) {return false;}
        }
    }
    else if (str == state2)
    {
        for (int i = 0; i < size_; i++)
        {
            if (P[2*i + 1] < P[i]) {return false;}
            if ((2*i + 2 < size_) && (P[2*i + 2] < P[i])) {return false;}
        }
    }
    return true;
}

void browse_tree(vector<float>* L, int root, const int length, const string order)
{
    string incr = "increase";

    string decr = "decrease";

    if (order == incr)
    {
        while (2*root + 1 < length)
        {
            int child = 2*root + 1;
            if ((child + 1 < length) && ((*L)[child + 1] > (*L)[child]))
            {
                child += 1; //Take the brother
            }
            if ((*L)[child] > (*L)[root])
            {
                float tmp = (*L)[root];

                (*L)[root] = (*L)[child];
                (*L)[child]= tmp;

                root = child;
            }
            else {return;}
        }
    }
    if (order == decr)
    {
        while (2*root + 1 < length)
        {
            int child = 2*root + 1;
            if ((child + 1 < length) && ((*L)[child + 1] < (*L)[child]))
            {
                child += 1; //Take the brother
            }
            if ((*L)[child] < (*L)[root])
            {
                float tmp = (*L)[root];

                (*L)[root] = (*L)[child];
                (*L)[child]= tmp;

                root = child;
            }
            else {return;}
        }
    }
}

void make_it_heap(vector<float>* L, const int length, const string order)
{
    int start = (length - 1 - 1)/2; //Start at the bottom of the tree
    while (start >= 0)
    {
        browse_tree(L, start, length, order);
        start -= 1;
    }
}

void heap_sort(vector<float>* L, int length, const string order)
{
    make_it_heap(L, length, order);
    while (length>0)
    {
        length -= 1;
        float tmp = (*L)[0];
        (*L)[0] = (*L)[length];
        (*L)[length] = tmp;
        make_it_heap(L, length, order);
    }
}
