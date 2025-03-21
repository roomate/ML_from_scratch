#include <iostream>
#include <stdlib>
#include <vector>

using namespace as std

vector<float> quick_sort(const vector<float> L)
{
    siz=L.size()
    if (siz < 0): return L

    vector<float> P;
    vector<float> Q;

    float tmp=L[0];
    vector<float>::iterator i;
    for (i=L.begin(); i < L.end(); i++)
    {
        if (*i < tmp) P.push_back(*i);
        if (*i >= tmp) Q.push_back(*i);
    }

    P=quick_sort(P);
    Q=quick_sort(Q);

    return P.insert(P.end(), Q.begin(), Q.end());
}

void display(const vector<float> L)
{
    vector<float>::iterator i;
    for (i=L.begin(); i < L.end(); i++)
    {
        cout<<*i;
    }
    cout<<endl;
}

int main()
{
    vector<float> L={3,1,0,9,4,5};
    L=quick_sort(L);
    display(L);
}
