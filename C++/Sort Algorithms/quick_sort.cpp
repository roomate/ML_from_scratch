#include <vector>
#include "quick_sort.hpp"

////////////////////////////////////////////////////////////
/////////////////////Quick Sort/////////////////////////////
////////////////////////////////////////////////////////////
vector<float> quick_sort(const vector<float> L)
{
    if (L.size() <= 1) return L;
    vector<float> Q;
    vector<float> P;

    float a = L[0];

    for (int i = 1; i < L.size(); i++)
    {
        if (L[i] > a) {P.push_back(L[i]);}
        else {Q.push_back(L[i]);}
    }
    Q = quick_sort(Q);
    P = quick_sort(P);
    Q.push_back(a); //Put back the pivot
    Q.insert(Q.end(), P.begin(), P.end());
    return Q;
}
