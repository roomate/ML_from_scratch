#include <stdlib.h>
#include <vector>
#include <stdio.h>
#include <iostream>
#include "merge_sort.hpp"

using namespace std;

////////////////////////////////////////////////////////////
/////////////////////Merge Sort/////////////////////////////
////////////////////////////////////////////////////////////

vector<float> merge_lists(const vector<float> L1, const vector<float> L2)
{
    vector<float> P;
    int i = 0;
    int j = 0;
    while (i < L1.size() && j < L2.size())
    {
        if (L1[i] < L2[j])
        {
            P.push_back(L1[i]);
            ++i;
        }
        else
        {
            P.push_back(L2[j]);
            ++j;
        }
    }
    if (i == L1.size()) {P.insert(P.end(), L2.begin() + j, L2.end());}
    else if (j == L2.size()) {P.insert(P.end(), L1.begin() + i, L1.end());}
    return P;
}

vector<float> merge_sort(const vector<float> L)
{
    if (L.size() == 1) {return L;}

    vector<float> L1;
    vector<float> L2;

    int i = 0;
    vector<float>::const_iterator it;

    for (it = L.begin(); it != L.end(); it++)
    {
        if (i < (L.size() + 1)/2) {L1.push_back(*it);}
        else {L2.push_back(*it);}
        ++i;
    }

    return merge_lists(merge_sort(L1), merge_sort(L2));
}
