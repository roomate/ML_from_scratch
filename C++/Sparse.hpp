#ifndef TP7_HPP
#define TP7_HPP
#include <iostream>
#include <map>
#include <vector>
#include <utility>
using namespace std;

class IJ
{
    public:
    int i, j;
    IJ(int r, int c) : i(r), j(c) {};
};

ostream& operator<<(ostream& out, const IJ& t)
{
    out<<"("<<t.i<<","<<t.j<<")";
    return out;
}

bool operator<(const IJ& t, const IJ& s)
{
    if (t.i < s.i) return true;
    else if (t.i == s.i) {if (t.j < s.j) return true;}
    return false;
}

template <typename T>
class Sparse: public map<IJ, T>
{
    public: 
    int m, n;

    Sparse(int length=0, int width=0): m(width), n(length) {}

    T& operator()(const IJ& s); //For writing and reading
    T operator()(const IJ& s) const; //For reading only

    T& operator()(int i, int j); //For writing and reading
    T operator()(int i, int j) const; //For reading only

    Sparse<T>& operator+=(const Sparse<T> O);
    Sparse<T>& operator-=(const Sparse<T> O);

    Sparse<T>& operator*=(const T& scal);
    Sparse<T>& operator/=(const T& scal);
    void remplissage() const;
};

template <typename T>
T Sparse<T>::operator()(const IJ& s) const
{
    typename map<IJ,T>::const_iterator out=this->find(s);
    if (out==this->end())
    {
        return 0;
    }
    return out->second;
}

template <typename T>
T& Sparse<T>::operator()(const IJ& s)
{
    typename map<IJ,T>::iterator out=this->find(s);
    if (out==this->end())
    {
        if (n<s.i) {n=s.i;}
        if (m<s.j) {m=s.j;}
        this->insert(pair<IJ, T>(s, 0.));
    }
    return (*this)[s];
}

template <typename T>
T Sparse<T>::operator()(int i, int j) const
{
    IJ pos(i, j);
    return (*this)(pos);
}

template <typename T>
T& Sparse<T>::operator()(int i, int j)
{
    IJ pos(i, j);
    return (*this)(pos);
}

template <typename T>
ostream& operator<<(ostream& out, const Sparse<T> test)
{
    out<<"Matrice sparse "<<test.m<<"x"<<test.n<<", "<<"nb coeff= "<<test.size()<<endl;
    typename map<IJ,T>::const_iterator it=test.begin();
    for (it=test.begin(); it!=test.end(); ++it)
    {
        out<<it->first<<" : "<<it->second<<endl;
    }
    return out;
}

template<typename T>
void Sparse<T>::remplissage() const
{
    cout<<" ";
    for (int i=0; i<=this->n; ++i)
    {
        cout<<" "<<i<<" ";
    }
    cout<<endl;
    for (int j=1; j<=this->m; ++j)
    {
        cout<<j;
        for (int i=1; i<=this->n; ++i)
        {
            IJ pos(j, i);
            if (this->find(pos) == this->end())
            {
                cout<<"   ";
            }
            else
            {
                cout<<" "<<(*this)(pos)<<" ";
            }
        }
        cout<<endl;
    }
}

template <typename T>
Sparse<T>& Sparse<T>::operator+=(const Sparse<T> O)
{
    if (m!=O.m || n!=O.n)
    {
        cout<<"Erreur, les matrices n'ont pas les mêmes dimensions."<<endl;
        exit(1);
    }
    typename map<IJ,T>::const_iterator It;
    for (It=O.begin(); It!=O.end(); ++It)
    {
        (*this)[It->first] += It->second;
    }
    return *this;
}

template <typename T>
Sparse<T>& Sparse<T>::operator-=(const Sparse<T> O)
{
    if (m!=O.m || n!=O.n)
    {
        cout<<"Erreur, les matrices n'ont pas les mêmes dimensions."<<endl;
        exit(1);
    }
    typename map<IJ,T>::const_iterator It;
    for (It=O.begin(); It!=O.end(); ++It)
    {
        (*this)[It->first] -= It->second;
    }
    return *this;
}

template <typename T>
Sparse<T>& Sparse<T>::operator*=(const T& scal)
{
    typename map<IJ, T>::iterator It;
    for (It=this->begin(); It!=this->end(); ++It)
    {
        It->second*= scal;
    }
    return *this;
}

template <typename T>
Sparse<T>& Sparse<T>::operator/=(const T& scal)
{
    if (scal==0) {cout<<"Erreur: division par 0 impossible."; exit(1);}
    typename map<IJ, T>::iterator It;
    for (It=this->begin(); It!=this->end(); ++It)
    {
        It->second/= scal;
    }
    return *this;
}

template <typename T>
Sparse<T> operator+(const Sparse<T>& I, const Sparse<T>& P)
{
    Sparse<T> O=I;
    return O+=P;
}

template <typename T>
Sparse<T> operator-(const Sparse<T>& I, const Sparse<T>& P)
{
    Sparse<T> O=I;
    return O-=P;
}

template <typename T>
Sparse<T> operator*(const Sparse<T>& I, const T& s)
{
    Sparse<T> O=I;
    return O*=s;
}

template <typename T>
Sparse<T> operator*(const T& s, const Sparse<T>& I)
{
    return I*s;
}

template <typename T>
Sparse<T> operator/(const Sparse<T>& I, const T& s)
{
    Sparse<T> O=I;
    return O/=s;
}

template <typename T>
ostream& operator<<(ostream& out, vector<T> vec)
{
    typename vector<T>::const_iterator It;
    out<<"(";
    for (It=vec.begin(); It!=vec.end()-1; ++It)
    {
        out<<*It<<",";
    }
    out<<*(vec.end()-1)<<')'<<endl;
    return out;
}

template <typename T>
vector<T> operator*(const Sparse<T>& M, const vector<T>& b)
{
    vector<T> Out(b.size(), 0);
 
    for (int i=1; i<=b.size(); ++i)
    {
        for (int j=1; j<M.n; ++j)
        {
            const IJ pos(i, j);
            typename map<IJ, T>::const_iterator It=M.find(pos);
            if (It!=M.end())
            {
                Out[i] += M(pos)*b[j];
            }
        }
    }
    return Out;
}

#endif