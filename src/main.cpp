#include <iostream>
#include <vector>
#include <set>
#include <chrono>

using std::set;
using std::vector;
using std::chrono::high_resolution_clock;
using std::cout;
using std::endl;

#include "../include/edge.hpp"
#include "../include/graph.hpp"

// ./MinTree /Users/eliasmann/Desktop/Algorithms/s21-pa04-wall_mann/inputData/100-1000.dat

int main(int argc, char* const argv[])
{
    Graph graph("/Users/eliasmann/Desktop/Algorithms/s21-pa04-wall_mann/inputData/100-1000.dat");
    graph.print();

    auto start = high_resolution_clock::now();
    pair<weight,int> primData = graph.prims();
    auto end = high_resolution_clock::now();
    chrono::duration<double,std::nano> primTime = (end-start);

    start = high_resolution_clock::now();
    pair<weight,int> kruskalData = graph.kruskals();
    end = high_resolution_clock::now();
    chrono::duration<double,std::nano> kruskalTime = (end-start);

    cout << "Prim's: " << endl << "Cost: " << primData.first 
    << endl <<  " Edges: " << primData.second << endl <<"Time (ns): " <<primTime.count() << endl <<endl;

    cout << "Kruskal's: " << endl << "Cost: " << kruskalData.first 
    << endl << " Edges: " << kruskalData.second << endl <<"Time (ns): " <<kruskalTime.count()<< endl;
    return 0;
}