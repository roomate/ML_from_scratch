#include <stdio.h>
#include <iostream>
#include <cmath>
#include <random>
#include "kmean.hpp"
#include <vector>
#include <cassert>
#include <tuple>
#include <limits>



//========================================================================================================
//=========================================Point==========================================================
//========================================================================================================

Point::Point(const unsigned int d): dim(d), val(0) {if (d==0) {return;}; val=new float[d];}
Point::Point(const unsigned int d, const float value)
{
    if (d==0) {return;}
    dim=d;
    val=new float[dim];
    for (int i=0; i<d; ++i) {val[i]=value;}
}

//Destructor
Point::~Point()
{
    if (val) {delete[] val;} //Delete pointer
}

void Point::set_dim(int d)
{
    dim=d;
}

//Copy constructor
Point::Point(const Point& Q)
{
    dim=Q.dim;
    val= new float[dim];
    for (int i=0; i<dim; ++i) {val[i]=Q.val[i];}
}

//Getter of Point's dimension
int Point::dimension() const {return dim;}
//Accessor for reading
float Point::operator[](int i) const {if (i>dim) {std::cout<<"You index exceeds the dimension of the Point"<<std::endl;exit(-1);} return val[i];}
//Accessor for writing/reading
float& Point::operator[](int i) {if (i>dim) {std::cout<<"You index exceeds the dimension of the Point"<<std::endl;exit(-1);} return val[i];}

Point& Point::operator=(const Point& Q)
{
    if (dim != Q.dimension()) { if (val) {delete[] val;} val=new float[Q.dimension()];}
    dim=Q.dimension();
    for (int i=0; i<dim; ++i) {val[i]=Q[i];}
    return *this;
}

Point& Point::operator+=(const Point& Q)
{
    if (dim != Q.dim) 
    {
        std::cout<<"P and Q should have same dimensions"<<std::endl;
        exit(1);
    }
    for (int i=0; i<dim; ++i)
    {
        val[i]+= Q[i];
    }
    return *this;
}

Point& Point::operator+=(const float a)
{
    for (int i=0; i<dim; ++i)
    {
        val[i]+= a;
    }
    return *this;

}


Point& Point::operator-=(const Point& Q)
{
    if (dim != Q.dim) 
    {
        std::cout<<"P and Q should have same dimensions"<<std::endl;
        exit(1);
    }
    for (int i=0; i<dim; ++i)
    {
        val[i]-= Q[i];
    }
    return *this;
}

Point& Point::operator-=(const float a)
{
    for (int i=0; i<dim; ++i)
    {
        val[i]-= a;
    }
    return *this;

}

Point& Point::operator/=(const Point& Q)
{
    if (dim != Q.dim) 
    {
        std::cout<<"P and Q should have same dimensions"<<std::endl;
        exit(1);
    }
    for (int i=0; i<dim; ++i)
    {
        if (Q[i]==0) {std::cout<<"Warning, division by 0"<<std::endl; exit(1);}
        val[i]/= Q[i];
    }
    return *this;
}

Point& Point::operator/=(const float a)
{
    if (a==0) {std::cout<<"You want to divide by 0."<<std::endl; exit(1);}
    for (int i=0; i<dim; ++i)
    {
        val[i]+= a;
    }
    return *this;
}


Point& Point::operator*=(const Point& Q)
{
    if (dim != Q.dim) 
    {
        std::cout<<"P and Q should have same dimensions"<<std::endl;
        exit(1);
    }
    for (int i=0; i<dim; ++i)
    {
        val[i]*= Q[i];
    }
    return *this;
}

Point& Point::operator*=(const float a)
{
    for (int i=0; i<dim; ++i)
    {
        val[i]*= a;
    }
    return *this;

}

bool Point::operator==(const Point& Q) const
{
    if (dim != Q.dimension()) {return false;}
    for (int i=0; i<dim; ++i)
    {
        if (val[i] != Q[i]) {return false;}
    }
    return true;
}

Point operator+(const Point& P, const Point& Q)
{
    Point A(P);
    return A+=Q;
}

Point operator+(const Point& P, const float a)
{
    Point A(P);
    return A+=a;
}

Point operator*(const Point& P, const Point& Q)
{
    Point A(P);
    return A*=Q;
}

Point operator*(const Point& P, const float a)
{
    Point A(P);
    return A*=a;
}

Point operator/(const Point& P, const Point& Q)
{
    Point A(P);
    return A/=Q;
}

Point operator/(const Point& P, const float a)
{
    Point A(P);
    return A/=a;
}

Point operator-(const Point& P, const Point& Q)
{
    Point A(P);
    return A-=Q;
}

Point operator-(const Point& P, const float a)
{
    Point A(P);
    return A-=a;
}


float Point::euclid_distance(const Point& P) const
{
    if (dim != P.dimension()) {std::cout<<"The points should have the same dimension:"<<dim<<"!="<<P.dimension()<<std::endl; exit(1);}
    float dist=0;
    for (int i=0; i<dim; ++i) { dist += (val[i] - P[i])*(val[i] - P[i]);}
    return std::sqrt(dist);
}

float Point::dot_product(const Point& P) const
{
    if (P.dimension() != dim) 
    {
        std::cout<<"Points do not live in the same dimension."<<dim<<"!="<<P.dimension()<<std::endl;
        exit(1);
    }
    float value=0;
    for (int i=0; i<P.dimension(); ++i)
    {
        value += val[i]*P[i];
    }
    return value;
}

//========================================================================================================
//=========================================Cluster========================================================
//========================================================================================================

Cluster::Cluster(const Point& P, int id):  Id(id), dim(P.dimension())
{
    Points.push_back(P); //Ensure no memory error
    centroid=P; //Call copy constructor
}

Cluster::Cluster(const Cluster& C, int id): Id(id)
{
    dim=C.dim;
    centroid=C.centroid;
    Points=C.Points;
}

Cluster::Cluster(const Cluster& C)
{
    Id=C.Id;
    dim=C.dim;
    centroid=C.centroid;
    Points=C.Points;
}

Cluster::~Cluster(){}

int Cluster::get_id() const
{
    return Id;
}

int Cluster::get_size() const
{
    return Points.size();
}


Cluster& Cluster::operator=(const Cluster& C)
{
    Points=C.Points; //Call vector's = operator overloading
    Id=C.Id;
    dim=C.dim;
    centroid=C.centroid;
    return *this;
}

void Cluster::compute_centroid()
{
    float x_coord=0;
    float y_coord=0;
    for (int i=0; i<Points.size(); ++i) {x_coord += Points[i][0]; y_coord += Points[i][1];}
    centroid[0]=x_coord/Points.size();
    centroid[1]=y_coord/Points.size();
}

bool Cluster::add_Point(const Point& P)
{
    Points.push_back(P); //Should call Copy constructor
    compute_centroid(); //Update centroid
    return 0;
}

bool Cluster::remove_Point(const Point& P)
{
    if (Points.size()==0) {std::cout<<"Cluster is empty."<<std::endl; exit(1);}
    std::vector<Point>::iterator it;
    for (it=Points.begin(); it<Points.end(); ++it)
    {
        if (P==*it) {Points.erase(it); compute_centroid(); return 0;}
    }
    std::cout<<"Point is not in the cluster."<<std::endl;
    return 1;
}

bool Cluster::remove_Index(int index)
{
    if (Points.size()==0) {std::cout<<"Cluster is empty."<<std::endl; exit(1);}
    if (index >= Points.size()) {std::cout<<"You index exceeds the number of elements in the Cluster."<<std::endl; return 1;}
    std::vector<Point>::iterator it=Points.begin() + index;
    Points.erase(it);
    compute_centroid();
    return 0;
}

Cluster& Cluster::merge_clusters(const Cluster& C)
{   
    for (int i=0; i<C.Points.size(); ++i)
    {
        add_Point(C.Points[i]);
    }
    compute_centroid();
    return *this;
}

float Cluster::dist_Point_to_Cluster(const Point& P) const
{
    return P.euclid_distance(centroid);
}

float Cluster::dist_Cluster_to_Cluster(const Cluster& Q) const
{
    return euclid_distance(centroid, Q.centroid);
}

float Cluster::inertia()
{
    float var=0;
    std::vector<Point>::iterator it;
    for (it=Points.begin(); it<Points.end(); ++it)
    {
        for (int j=0; j<dim; ++j) {var+=((*it)[j]-centroid[j])*((*it)[j]-centroid[j]);}
    }
    return var;
}

void Cluster::display()
{
    for (int i=0; i<Points.size(); ++i)
    {
        std::cout<<Points[i];
    }
}

//========================================================================================================
//=========================================KMEAN==========================================================
//========================================================================================================

KMEAN::~KMEAN(){
    if (Clusters != nullptr)
    {
        delete[] Clusters; //Delete array of Cluster
    }
}

KMEAN::KMEAN(int n_cluster, int n_iter_max, float eps, const std::vector<Point> List_Points): epsilon(eps), nb_cluster(n_cluster), Nb_iter_max(n_iter_max)
{
    std::random_device rd;  // a seed source for the random number engine
    std::mt19937 gen(rd()); // mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> distrib(0,  List_Points.size()-1);

    Dataset=List_Points;

    int k=1; //Counts the number of clusters filled.
    std::vector<int> visited;
    int origin_center=distrib(gen); //Samples a point randomly
    visited.push_back(origin_center);

    Clusters=new Cluster[n_cluster]; //Calls the default constructor, which do basically nothing

    data_in_cluster current_data; current_data.Id=0; current_data.data=List_Points[origin_center];
    Points_in_cluster.push_back(current_data);

    Clusters[0]=Cluster(List_Points[origin_center], 0); //Calls the Cluster constructor

    while (k<n_cluster)
    {
        std::vector<float> distance;
        // List all indices that belong to no cluster
        std::vector<int> index;
        // For each non-assigned data point, find the closest cluster.
        for (int i=0; i<List_Points.size(); ++i)
        {
            if (!is_in(i, visited))
            {
                index.push_back(i);
                Point P=List_Points[i];
                float min_dist=std::numeric_limits<int>::max();
                // Find the closest cluster to P.
                for (int j=0; j<k; ++j)
                {
                    //Compute distance Point-Cluster
                    float candidate=dist_Point_to_Cluster(Clusters[j], P);
                    //Test if it is the closest yet
                    if (candidate<min_dist) {min_dist=candidate;}
                }
                //Store the distance to the closest cluster
                distance.push_back(min_dist);
            }
        }
        float sum_element=0;
        //Normalization distance vector, it is not necessary, it is actually done automatically.
        for (int i=0; i<distance.size(); ++i)
        {
            sum_element+=distance[i];
        }
        divide(distance, sum_element); //Divide
        
        //Sample a random number
        std::discrete_distribution<int> dist(distance.begin(), distance.end());
        int new_cluster_id=index[dist(gen)]; //Sample the centroid of the new cluster.
        visited.push_back(new_cluster_id); //Append it to the list of visited nodes.

        //Add the cluster's center
        data_in_cluster current_data; current_data.Id=k; current_data.data=List_Points[new_cluster_id]; 
        Points_in_cluster.push_back(current_data);

        Cluster tmp(List_Points[new_cluster_id], k);
        Clusters[k]=tmp; //Define a new cluster with id k
        k++;
    }
    for (int i=0; i<List_Points.size(); ++i)
    {
        if (!is_in(i, visited))
        {
            float min_dist=std::numeric_limits<int>::max();
            int closest_cluster;
            float candidate;
            for (int j=0; j<k; ++j)
            {
                Cluster c=Clusters[j]; Point p=List_Points[i];
                candidate=dist_Point_to_Cluster(c, p);
                if (candidate<min_dist) {min_dist=candidate; closest_cluster=j;}
            }
            Clusters[closest_cluster].add_Point(List_Points[i]);
            data_in_cluster current_data; current_data.Id=Clusters[closest_cluster].get_id(); current_data.data=List_Points[i]; 
            Points_in_cluster.push_back(current_data);
        }
    }
    update_inertia();
}

//Find closest cluster
void KMEAN::E_step()
{
    assert (Points_in_cluster.size() == Dataset.size());
    //Find the closest cluster for each data point.
    for (int i=0; i<Dataset.size(); ++i)
    {
        float min_dist=std::numeric_limits<int>::max();
        int closest_cluster;
        float candidate_min;
        for (int j=0; j<nb_cluster; ++j)
        {
            candidate_min=dist_Point_to_Cluster(Clusters[j], Points_in_cluster[i].data);
            if (candidate_min<min_dist) {min_dist=candidate_min; closest_cluster=j;}
        }

        //Remove data point from previous cluster
        int old_cluster=Points_in_cluster[i].Id;
        Clusters[old_cluster].remove_Point(Points_in_cluster[i].data);

        //Change the Id of the closest cluster
        int id_closest=Clusters[closest_cluster].get_id();
        Points_in_cluster[i].Id=id_closest;

        //Add a point to the closest cluster
        Clusters[closest_cluster].add_Point(Points_in_cluster[i].data);
    }
}

void KMEAN::M_step()
{
    //Update the centroids of each cluster
    for (int i=0; i<nb_cluster; ++i)
    {
        Clusters[i].compute_centroid();
    }
}

void KMEAN::fit()
{
    int nb_iter=0;
    float delta=std::numeric_limits<int>::max();;
    while (nb_iter<Nb_iter_max && delta > epsilon)
    {
        ++nb_iter;
        Cluster* Prev_clusters=new Cluster[nb_cluster];
        for (int i=0; i<nb_cluster; ++i) {Prev_clusters[i]=Clusters[i];} //Call copy constructor on each cluster
        E_step(); //Assign the closest cluster to each point
        M_step(); //Update the centroid of the clusters
        delta=0;
        for (int i=0; i<nb_cluster; ++i)
        {
            delta += dist_Cluster_to_Cluster(Prev_clusters[i], Clusters[i]);
        }
    }
    std::cout<<"Kmean algorithm took "<<nb_iter<<" iteration(s) to converge."<<std::endl;
}

float KMEAN::compute_inertia()
{
    float inertia_tmp=0;
    for (int i=0; i<nb_cluster; ++i)
    {
        inertia_tmp += Clusters[i].inertia();
    }
    return inertia_tmp;
}

void KMEAN::update_inertia()
{
    inertia=compute_inertia();
}

void KMEAN::display_clusters()
{
    for (int i=0; i<nb_cluster; ++i)
    {
        std::cout<<"Cluster N°"<<i<<std::endl;
        Clusters[i].display();
        std::cout<<"--------"<<std::endl;
    }
}

//========================================================================================================
//=========================================Functions======================================================
//========================================================================================================


float dist_Point_to_Cluster(const Cluster& C, const Point& P)
{
    return C.dist_Point_to_Cluster(P);
}

float dist_Point_to_Cluster(const Point& P, const Cluster& C)
{
    return C.dist_Point_to_Cluster(P);
}

float dist_Cluster_to_Cluster(const Cluster& P, const Cluster& Q)
{
    Point centroid_P=P.centroid;
    Point centroid_Q=Q.centroid;
    return euclid_distance(centroid_P, centroid_Q);
}

float euclid_distance(const Point& P, const Point& Q) 
{
    return P.euclid_distance(Q);
}

float dot_product(const Point& P, const Point& Q)
{
    return P.dot_product(Q);
}

template<typename T>
void divide(std::vector<T>& V, const float a)
{
    if (a==0) {std::cout<<"Division by 0 impossible"<<std::endl;}
    typename std::vector<T>::iterator it;
    for (it=V.begin(); it<V.end(); ++it) {*it /= a;}
}

template<typename T>
bool is_in(const T& id, std::vector<T> V)
{
    typename std::vector<T>::iterator it;
    for (it=V.begin(); it<V.end(); ++it)
    {
        if (id==*it) {return true;}
    }
    return false;
}

std::ostream& operator<<(std::ostream& os, const Point& P)
{
    if (P.is_nullptr()) {os<<"Point has not yet been initialized"; os<<std::endl; return os;}
    os<<"(";
    for (int i=0; i<P.dimension() - 1; ++i)
    {
        os<<P[i]<<" ";
    }
    os<<P[P.dimension()-1]<<")"<<std::endl;
    return os;
}
