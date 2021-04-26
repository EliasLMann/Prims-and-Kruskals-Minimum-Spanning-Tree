// Elias Mann, Nick Wall - SMU CS 3353 2021 Spring PA04

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

int main(int argc, char* const argv[])
{
    //speed test
    if(strcmp(argv[1], "-b") == 0){
        //creating graph
        Graph graph(argv[2]);
        //running kruskal's algorithm and returning cost and sum
        pair<weight,int> kruskalData = graph.kruskals();
        cout << "Count: " << kruskalData.second << " Sum: " << kruskalData.first << endl;

        //full test
    } else if(strcmp(argv[1], "-f") == 0) {
        //creating graph
        Graph graph(argv[2]);

        ofstream output;
        output.open("../Data_Analysis.txt",fstream::app);
        //graph label
        output << "Size: " << graph.getSize() << " Density: " << graph.getDensity() << endl << endl;

        //timing prim's algorithm
        auto start = high_resolution_clock::now();
        pair<weight, int> primData = graph.prims();
        auto end = high_resolution_clock::now();
        chrono::duration<double, std::milli> primTime = (end - start);

        //timing kruskal's algorithm
        start = high_resolution_clock::now();
        pair<weight, int> kruskalData = graph.kruskals();
        end = high_resolution_clock::now();
        chrono::duration<double, std::milli> kruskalTime = (end - start);

        //prims data
        output << "\tPrim's: " << endl << "\t\tCost: " << primData.first
             << endl << "\t\tEdges: " << primData.second << endl << "\t\tTime (ms): " << primTime.count() << endl << endl;

        //kruskal's data
        output << "\tKruskal's: " << endl << "\t\tCost: " << kruskalData.first
             << endl << "\t\tEdges: " << kruskalData.second << endl << "\t\tTime (ms): " << kruskalTime.count() << endl << endl;
        output.close();

    }else{
        cout << "ERROR: Invalid Command Line Arguments" << endl;
        cout << argv[1] << endl;
    }
    return 0;
}