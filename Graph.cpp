#include <iostream>
#include <fstream>
#include <cstdlib>
#include <algorithm>
#include "Graph.h"

using namespace std;

Graph::Graph( const int n ): V( n ), maxCliqueSize( 0 )
{
    adjMatrix.resize( n, vector<char>( n, '0' ) );
    degree.resize( n, 0 );
    maxClique.resize( n, false );
}

Graph::~Graph()
{

}

void Graph::AddEdge( const int u, const int v )
{
    if ( u == v ) return;
    adjMatrix[u][v] = '1';
    adjMatrix[v][u] = '1';
    degree[u]++;
    degree[v]++;
}

/* MCS Algorithm */
void Graph::FindMaxClique()
{
    colorClasses.resize( V );
    vector<int> C;  // current clique
    vector<int> P;  // candidate set of vertices
    vector<int> ColOrd;
    OrderVertices( ColOrd );
    Expand( C, P, ColOrd );
}

void Graph::NumberSort( vector<int>& ColOrd, vector<int>& P, vector<int>& color )
{
    int colors = 0, m = ColOrd.size();
    for ( int i = 0; i < m; ++i ) colorClasses[i].clear();
    for ( int i = 0; i < m; ++i ) {
        int v = ColOrd.at( i );
        int k = 0;
        while ( Conflict( v, colorClasses[k] ) ) k++;
        colorClasses[k].push_back( v );
        colors = max( colors, k + 1 );
    }
    P.clear();
    int i = 0;
    for ( int k = 0; k < colors; ++k ) {
        for ( int j = 0; j < colorClasses[k].size(); ++j ) {
            int v = colorClasses[k].at( j );
            P.push_back( v );
            color[i++] = k + 1;
        }
    }
}

bool Graph::Conflict( int v, vector<int>& colorClass )
{
    for ( int i = 0; i < colorClass.size(); ++i ) {
        int w = colorClass.at( i );
        if ( adjMatrix[v][w] == '1' ) return true;
    }
    return false;
}

void Graph::OrderVertices( vector<int>& ColOrd )
{
    vector<Vertex> vert( V );
    for ( int i = 0; i < V; ++i ) vert[i] = Vertex( i, degree[i] );
    for ( int i = 0; i < V; ++i )
        for ( int j = 0; j < V; ++j )
            if ( adjMatrix[i][j] == '1' ) vert[i].nebDeg += degree[j];
    stable_sort( vert.begin(), vert.end(), MCRComparator() );
    for ( int i = 0; i < V; ++i ) ColOrd.push_back( vert[i].index );
}

void Graph::Expand( vector<int>& C, vector<int>& P, vector<int>& ColOrd )
{
    int m = ColOrd.size();
    vector<int> color( m );
    NumberSort( ColOrd, P, color );
    for ( int i = m - 1; i >= 0; --i ) {
        int v = P.at( i );
        if ( C.size() + color[i] <= maxCliqueSize ) return;
        C.push_back( v );
        vector<int> newP;
        vector<int> newColOrd;
        for ( int j = 0; j <= i; ++j ) {
            int u = P.at( j );
            int w = ColOrd.at( j );
            if ( adjMatrix[v][u] == '1' ) newP.push_back( u );
            if ( adjMatrix[v][w] == '1' ) newColOrd.push_back( w );
        }
        if ( /*newP.empty() &&*/ C.size() > maxCliqueSize ) {
            fill( maxClique.begin(), maxClique.end(), false );
            for ( auto k : C ) maxClique[k] = true;
            maxCliqueSize = C.size();
            if ( newP.empty() ) SaveMaxClique();
        }
        if ( !newP.empty() ) Expand( C, newP, newColOrd );
        C.pop_back();
        P.erase( P.begin() + i );
        for ( auto it = ColOrd.begin(); it != ColOrd.end(); ++it ) {
            if ( *it == v ) {
                ColOrd.erase( it );
                break;
            }
        }
    }
}

void Graph::SaveMaxClique()
{
    ofstream outputFile( "clique.txt" );
    if ( !outputFile ) {
        cerr << "Output file could not be opened!" << endl;
        exit( EXIT_FAILURE );
    }
    for ( int i = 0; i < maxClique.size(); ++i )
        if ( maxClique[i] ) outputFile << i << '\n';
    outputFile.close();
}
