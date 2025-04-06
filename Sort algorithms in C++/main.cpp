#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include "heap_sort.hpp"
#include "quick_sort.hpp"
#include "insertion_sort.hpp"
#include "merge_sort.hpp"

void display(const vector<float> P)
{
    vector<float>::const_iterator it;
    for (it=P.begin(); it != P.end(); it++)
    {
        cout<<*it;
    }
    cout<<endl;
}

char HEAP_SORT[15] = "heap_sort";
char QUICK_SORT[15] = "quick_sort";
char INSERTION_SORT[15] = "insertion_sort";
char MERGE_SORT[15]= "merge_sort";


int main(int argc, char* argv[])
{
    if (argc == 1)
    {
        printf("Not enough argument.");
        return 1;
    }
    else if (argc > 2)
    {
        printf("too much arguments");
        return 1;
    }
    string a;
    cin>>a;

    string b; //Increasing or Decreasing order
    cin>>b;

    if (b == "D") {b = "decrease";}
    else if (b == "I") {b = "increase";}
    else
    {
        printf("You should choose 'I' for ascending order, or 'D' for descending order.");
    }

    vector<float> Q;
    vector<float> L(a.size());
    for (int i = 0; i < a.size(); ++i)
    {
        L[i] = float(a[i]) - 48;
    }
    if (strcmp(argv[1], HEAP_SORT) == 0)
    {
        heap_sort(&L, L.size(), b);
    }
    else if (strcmp(argv[1], MERGE_SORT) == 0)
    {
        L = merge_sort(L);
    }
    else if (strcmp(argv[1], INSERTION_SORT) == 0)
    {
        L = insertion_sort(L);
    }
    else if (strcmp(argv[1], QUICK_SORT) == 0)
    {
        L = quick_sort(L);
    }
    else
    {
        printf("you should choose a sort algorithm among insertion, quick, merge and heap sort.");
    }
    display(L);
    return 0;
}