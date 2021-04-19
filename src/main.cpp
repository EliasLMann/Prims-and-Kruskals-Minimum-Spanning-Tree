#include <iostream>
#include <vector>
#include <set>
#include <chrono>

using std::set;
using std::vector;

using std::cout;
using std::endl;

// using std::chrono::high_resolution_clock;

#include "../include/edge.hpp"
#include "../include/graph.hpp"

int main()
{

    //// Benchmark graph implementaions
    // vector<double> times;

    // for (int i = 0; i < 10000; i++)
    // {
    //     vector<Edge> edge_list;
    //     set<int> nodes;

    //     edge_list.push_back(Edge(0, 1, 4));
    //     edge_list.push_back(Edge(0, 2, 1));
    //     edge_list.push_back(Edge(0, 3, 5));
    //     edge_list.push_back(Edge(1, 3, 2));
    //     edge_list.push_back(Edge(1, 4, 3));
    //     edge_list.push_back(Edge(1, 5, 3));
    //     edge_list.push_back(Edge(2, 3, 2));
    //     edge_list.push_back(Edge(2, 4, 8));
    //     edge_list.push_back(Edge(3, 4, 1));
    //     edge_list.push_back(Edge(4, 5, 3));

    //     for (auto edge : edge_list)
    //     {
    //         nodes.insert(edge.first_node());
    //         nodes.insert(edge.second_node());
    //     }

    //     // std::cout << std::endl;

    //     auto start_time = high_resolution_clock::now();
    //     AdjacencyList list(nodes.size());

    //     for (auto edge : edge_list)
    //     {
    //         list.add_edge(edge);
    //     }

    //     list.prims();

    //     auto end_time = high_resolution_clock::now();
    //     std::chrono::duration<double, std::nano> sort_duration = end_time - start_time;

    //     // std::cout << "Took " << sort_duration.count() << " ns" << std::endl;
    //     times.push_back(sort_duration.count());
    // }

    // double total = 0;
    // for (auto time : times)
    // {
    //     total += time;
    // }

    // auto average = total / times.size();

    // std::cout << "Average Time: " << average << " ns" << std::endl;

    Graph list(7);
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
    {
        list.add_edge(edge);
    }

    list.print();

    cout << list.prims() << endl;
}