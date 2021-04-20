#include <iostream>
#include <vector>
#include <set>

using std::set;
using std::vector;

using std::cout;
using std::endl;

#include "../include/edge.hpp"
#include "../include/graph.hpp"

int main()
{
    /// First Test Case
    Graph graph(7);
    vector<Edge> edge_list;

    edge_list.push_back(Edge(0, 1, 1));
    edge_list.push_back(Edge(0, 2, 2));
    edge_list.push_back(Edge(0, 3, 1));
    edge_list.push_back(Edge(0, 4, 1));
    edge_list.push_back(Edge(0, 5, 2));
    edge_list.push_back(Edge(0, 6, 1));

    edge_list.push_back(Edge(1, 0, 1));
    edge_list.push_back(Edge(1, 2, 2));
    edge_list.push_back(Edge(1, 6, 2));

    edge_list.push_back(Edge(2, 0, 2));
    edge_list.push_back(Edge(2, 1, 2));
    edge_list.push_back(Edge(2, 3, 1));

    edge_list.push_back(Edge(3, 0, 1));
    edge_list.push_back(Edge(3, 2, 1));
    edge_list.push_back(Edge(3, 4, 2));

    edge_list.push_back(Edge(4, 0, 1));
    edge_list.push_back(Edge(4, 3, 2));
    edge_list.push_back(Edge(4, 5, 2));

    edge_list.push_back(Edge(5, 0, 2));
    edge_list.push_back(Edge(5, 4, 2));
    edge_list.push_back(Edge(5, 6, 1));

    edge_list.push_back(Edge(6, 0, 1));
    edge_list.push_back(Edge(6, 2, 2));
    edge_list.push_back(Edge(6, 5, 1));

    for (auto edge : edge_list)
        graph.add_edge(edge);

    graph.print();
    cout << "Prim's: " << graph.prims() << endl;
    cout << "Kruskal's: " << graph.kruskals() << endl;
    

    /// Second Test Case
    Graph graph2(6);
    vector<Edge> edge_list2;

    edge_list2.push_back(Edge(0, 1, 4));
    edge_list2.push_back(Edge(0, 2, 1));
    edge_list2.push_back(Edge(0, 3, 5));
    edge_list2.push_back(Edge(1, 3, 2));
    edge_list2.push_back(Edge(1, 4, 3));
    edge_list2.push_back(Edge(1, 5, 3));
    edge_list2.push_back(Edge(2, 3, 2));
    edge_list2.push_back(Edge(2, 4, 8));
    edge_list2.push_back(Edge(3, 4, 1));
    edge_list2.push_back(Edge(4, 5, 3));

    for (auto edge : edge_list2)
        graph2.add_edge(edge);

    graph2.print();
    cout << "Prim's: " << graph2.prims() << endl;
    cout << "Kruskal's: " << graph2.kruskals() << endl;
}