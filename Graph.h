#ifndef GRAPH_H
#define GRAPH_H

#include <vector>

class Vertex
{
    friend class Graph;
    friend struct MCRComparator;
public:
    Vertex(): index( 0 ), degree( 0 ), nebDeg( 0 ) {}
    Vertex( const int idx, const int deg ): index( idx ), degree( deg ), nebDeg( 0 ) {}
    Vertex( const Vertex& v ): index( v.index ), degree( v.degree ), nebDeg( v.nebDeg ) {}
    bool operator < ( Vertex v )
    {
        if ( degree < v.degree || ( degree == v.degree && index > v.index ) ) return true;
        else return false;
    }
private:
    int index;
    int degree;
    int nebDeg;
};

struct MCRComparator
{
    bool operator () ( const Vertex& u, const Vertex& v )
    {
        if ( u.degree < v.degree || ( u.degree == v.degree && u.nebDeg < v.nebDeg ) || ( u.degree == v.degree && u.nebDeg == v.nebDeg && u.index > v.index ) )
            return true;
        else return false;
    }
};

class Graph
{
public:
    Graph( const int n );
    ~Graph();
    void AddEdge( const int u, const int v );
    void FindMaxClique();
    void SaveMaxClique();
private:
    std::vector<std::vector<char>> adjMatrix;
    std::vector<int> degree;
    int V;
    /* For MCS */
    int maxCliqueSize;
    std::vector<std::vector<int>> colorClasses;
    std::vector<bool> maxClique;  // solution to maximum clique problem

    void NumberSort( std::vector<int>& ColOrd, std::vector<int>& P, std::vector<int>& color );
    bool Conflict( int v, std::vector<int>& colorClass );
    void OrderVertices( std::vector<int>& ColOrd );
    void Expand( std::vector<int>& C, std::vector<int>& P, std::vector<int>& ColOrd );
};

#endif // GRAPH_H
