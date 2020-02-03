#include <iostream>
#include <cstdlib>
#include <fstream>
#include <csignal>
#include "Graph.h"

using namespace std;

Graph* g;

void signalHandler( int signum )
{
    g->SaveMaxClique();
    exit( signum );
}

int main( int argc, char* argv[] )
{
    signal( SIGINT, signalHandler );
    
    int n = stoi( argv[2] );
    
    // Open the input file
    ifstream inputFile( argv[1] );
    if ( !inputFile ) {
        cerr << "Input file could not be opened!" << endl;
        exit( EXIT_FAILURE );
    }

    g = new Graph( n );
    int u, v;
    while ( inputFile >> u >> v ) g->AddEdge( u, v );

    inputFile.close();

    g->FindMaxClique();
}
