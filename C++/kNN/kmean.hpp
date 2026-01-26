#ifndef kmean_HPP
#define kmean_HPP

#include <stdio.h>
#include <iostream>
#include <cmath>
#include <vector>

class Point
{
    private:
        unsigned int dim;
        float* val;
    public:
        //Constructor
        Point(const unsigned int d=0);
        Point(const unsigned int d, const float val);

        ~Point();

        //Copy constructor
        Point(const Point& Q);

        //Accessor
        int dimension() const;
        float operator[](int i) const;

        //Settor
        float& operator[](int i);
        void set_dim(int d);

        //Overloading
        Point& operator=(const Point& Q);
    
        Point& operator+=(const Point& Q);
        Point& operator+=(const float a);
    
        Point& operator-=(const Point& Q);
        Point& operator-=(const float a);
    
        Point& operator/=(const Point& Q);
        Point& operator/=(const float a);

        Point& operator*=(const Point& Q);
        Point& operator*=(const float a);
    
        bool operator==(const Point& Q) const;
        float dot_product(const Point& P) const;

        float euclid_distance(const Point& P) const;

        bool is_nullptr() const {return val==nullptr;}
};

Point operator+(const Point& P, const Point& Q);
Point operator*(const Point& P, const Point& Q);
Point operator/(const Point& P, const Point& Q);
Point operator-(const Point& P, const Point& Q);

std::ostream& operator<<(std::ostream& os, const Point& P);
class Cluster
{
    private:
    int Id; ///Cluster's ID
    public:
        std::vector<Point> Points; //Array of Points, not yet initialized
        Point centroid; //Cluster's Centroid
        int dim;

        Cluster(){};
        Cluster(int id, int d): Id(id), dim(d) {}
        Cluster(const Point& P, int id);

        //Copy constructor
        Cluster(const Cluster& C);
        Cluster(const Cluster& C, int id);

        Cluster& operator=(const Cluster& C);

        //Destructor
        ~Cluster();

        //Getter
        int get_id() const;

        int get_size() const;

        Cluster& merge_clusters(const Cluster& C);
        Cluster& operator+(const Cluster& C) {return merge_clusters(C);}
        void compute_centroid();

        bool add_Point(const Point& P);
        bool remove_Point(const Point& P);
        bool remove_Index(int index);

        float dist_Point_to_Cluster(const Point& P) const;
        float dist_Cluster_to_Cluster(const Cluster& Q) const;

        float inertia(); //Compute inertia of a cluster

        void display();
};

typedef struct
{
    Point data;
    int Id; //Id of the cluster data is attached to
} data_in_cluster;

class KMEAN
{
    private:
        int nb_cluster; //current number of clusters
        int Nb_iter_max; //Maximum number of iterations
        float epsilon; //Convergence criteria
    public:
        std::vector<Point> Dataset; //All data points
        Cluster* Clusters=nullptr; //Array of cluster
        bool is_fitted=false;
        std::vector<data_in_cluster> Points_in_cluster;
        float inertia=0;

        int get_nb_cluster() const {return nb_cluster;}
        int get_N_iter_max() const {return Nb_iter_max;}
        float get_epsilon() const {return epsilon;}

        KMEAN(){};
        KMEAN(int n_cluster, int n_iter_max, float eps): nb_cluster(n_cluster), Nb_iter_max(n_iter_max), epsilon(eps) {}

        ~KMEAN();

        //Apply kmean++ algorithm.
        KMEAN(int n_cluster, int n_iter_max, float eps, const std::vector<Point> List_Points);

        void display_clusters();

        float compute_inertia();
        void update_inertia();


        void E_step();
        void M_step();
        void fit();
};

//Return the distance between a point and a cluster's centroid
float dist_Point_to_Cluster(const Cluster& C, const Point& P);
float dist_Point_to_Cluster(const Point& P, const Cluster& C);

float dist_Cluster_to_Cluster(const Cluster& P, const Cluster& Q);
//Return the euclidian distance between two points.
float euclid_distance(const Point& P, const Point& Q);

//Perform the scalar product between two points.
float dot_product(const Point& P, const Point& Q);

//Divide a vector by a float.
template<typename T>
void divide(std::vector<T>& V, const float a);

//Check if element id is in vector V
template<typename T>
bool is_in(const T& id, std::vector<T> V);

#endif