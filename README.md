# Solving Maximum Clique Problem
Given an undirected unweighted graph and the number of vertices, this program uses MCS algorithm to find the maximum size of clique in the limited time and outputs all vertices that are in this clique. 
## Compilation
```
$ make
```
## Running
```
$ timeout -s SIGINT [time_limit(secs)] ./clique_find [input_file_name] [number_of_vertices]
```
Example:
```
$ timeout -s SIGINT 180 ./clique_find testcase.txt 82168
```
## Input File Format
If there are n vertices, vertex IDs are 0 ~ n-1. In the input file, each line consists of two integers u and v separated by a space, meaning that there exists an edge between u and v.

Example:
```
0 1
0 2
0 3
0 4
1 2
1 3
1 4
2 3
2 4
3 4
```
## Output File Format
The output file is named "clique.txt". In this file, each line consists of a vertex ID, and vertex IDs are sorted in ascending order.
```
0
1
2
3
4
```
## Testcase Information
An undirected unweighted graph with 82168 vertices and 2072442 edges
## References
E. Tomita and T. Kameda. An Efficient Branch-and-Bound Algorithm for Finding a Maximum Clique with Computational Experiments. Journal of Global Optimization, 37: 95-111, 2007.

E. Tomita, Y. Sutani, T. Higashi, S. Takahashi, and M. Wakatsuki. A Simple and Faster Branch-and-Bound Algorithm for Finding a Maximum Clique. Proceedings of WALCOM 2010, LNCS 5942, pp. 191-203, 2010. 
