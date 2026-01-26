#ifndef HEAP_SORT_H
#define HEAP_SORT_H

#include <vector>
#include <string>

using namespace std;

bool is_heap(const vector<float> P, const string str);
void browse_tree(vector<float>* L, int root, const int length, const string order);
void make_it_heap(vector<float>* L, const int length, const string order);
void heap_sort(vector<float>* L, int length, const string order);

#endif