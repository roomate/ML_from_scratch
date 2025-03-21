#include <iostream>
#include <cstdlib>
#include<vector>
#include<string.h>
using namespace std;

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

void display(const vector<float> P)
{
    vector<float>::const_iterator it;
    for (it=P.begin(); it != P.end(); it++)
    {
        cout<<*it;
    }
    cout<<endl;
}

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

int main()
{
    string a;
    cin>>a;

    string b; //Increasing or Decreasing order
    cin>>b;

    if (b == "D") {b = "decrease";}
    else if (b == "I") {b = "increase";}

    vector<float> Q;
    vector<float> L(a.size());
    for (int i = 0; i < a.size(); ++i)
    {
        L[i] = float(a[i]) - 48;
    }
    heap_sort(&L, L.size(), b);
    display(L);
    return 0;
}
