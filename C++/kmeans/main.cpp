#include "kmean.hpp"
#include <vector>
#include <stdio.h>
#include <random>

int main()
{
    // Uniform pseudo-random generator
    std::default_random_engine generator;
    std::uniform_real_distribution<double> distribution_real(0.0,1.0);
    std::uniform_int_distribution<int> distribution_int(0,3);
    
    Point P(2);
    std::vector<Point> L(100000);
    std::vector<Point>::iterator it;
    int i=0;
    for (it=L.begin(); it<L.end(); ++it)
    {
        if (i%10==0) {P[0]=distribution_int(generator); P[1]=distribution_int(generator);}
        (*it)=Point(2);
        (*it)[0]= P[0] + distribution_real(generator)*3; (*it)[1]=P[1] + distribution_real(generator)*4;
        i++;
    }
    std::cout<<L.size()<<std::endl;
    KMEAN kmean(50, 1000, .00000001, L);
    kmean.fit();
    return 0;
}