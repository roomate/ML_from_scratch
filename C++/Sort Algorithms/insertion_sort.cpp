#include <vector>
#include <cstdlib>
#include "insertion_sort.hpp"

////////////////////////////////////////////////////////////
/////////////////////Insertion Sort/////////////////////////
////////////////////////////////////////////////////////////

vector<float> insertion_sort(const vector<float> L)
{
    vector<float> P(L);
    for (int i = 1; i < L.size(); i++)
    {
        float tmp = P[i];
        int j = i - 1;
        while ((j >= 0) && (tmp < P[j]))
        {
            P[j + 1] = P[j];
            P[j] = tmp;
            --j;
        }
    }
    return P;
}
