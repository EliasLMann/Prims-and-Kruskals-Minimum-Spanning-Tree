/* Nick Wall, Elias Mann - SMU CS 3353 2021 Spring PA04
 * 
 * Graph representation of a weighted undirected graph using an adjacency list. Implements prim's and kruskal's algorithms
 * to find the minimum spanning tree. */

#pragma once

// STL Dependencies
#include <iostream>
#include <fstream>
#include <queue>
#include <algorithm>
#include <cstring>
#include <sstream>  


using std::greater;
using std::priority_queue;
using std::vector;

// Local Dependencies
#include "edge.hpp"
#include "disjointSet.hpp"

class Graph
{
private:
    /**
     * The adjacency list representation of the graph which is defined by the list of weighted edges.
     * The vector is keyed by the first node and contains another vector of <weight, node> pairs that
     * describe how far adjacent nodes are from the origin node.
     **/
    vector<vector<NodeDistance>> adj;

    /**
     * A min Heap of edges in the graph
     */
    priority_queue<Edge, vector<Edge>, greater<Edge>> edgeMinHeap;

public:
    /**
     * An undirected weighted graph implemented on-top of an adjacency list.
     * @constructor
     **/
    Graph(int num_nodes) { adj.resize(num_nodes); };

    /**
     * An undirected weighted graph implemented on-top of an adjacency list.
     * @constructor
     **/
    Graph(string filePath)
    {
        std::ifstream input;
        //opening file as write binary
        input.open(filePath, ios::out | ios::binary);
        if (!input)
        {
            cout << "Cannot Find Input File" << endl;
        }

        //initializing adjacency list to size of 5,000,000
        int allocSize = 5000000;
        adj.resize(allocSize);
        int largest = 0;
        while (!input.eof())
        {
            string currLine;
            getline(input, currLine);
            if(currLine.length() > 0 ) {
                std::stringstream lineStream(currLine);

                //buffer string
                string currElement;

                //getting the first vertex
                getline(lineStream, currElement, ' ');
                int v1 = stoi(currElement);

                if (v1 > largest) {
                    largest = v1;
                }

                //getting the second vertex
                getline(lineStream, currElement, ' ');
                int v2 = stoi(currElement);

                if (v2 > largest) {
                    largest = v2;
                }

                //getting the weight
                getline(lineStream, currElement, ' ');
                double w = stod(currElement);

                //if there are more than 5,000,000 vertices, double the size
                if (largest > allocSize) {
                    allocSize = (largest * 2);
                    adj.resize(allocSize);
                }

                //adding edge to graph
                add_edge(Edge(v1, v2, w));
            }
        }
        input.close();
        adj.resize(largest+1);
    }

    /**
     * An undirected weighted graph implemented on-top of an adjacency list.
     * @constructor
     **/
    Graph(const Graph &src)
    {
        adj = src.adj;
        edgeMinHeap = src.edgeMinHeap;
    };

    /**
     * An undirected weighted graph implemented on-top of an adjacency list.
     * @destructor
     **/
    ~Graph(){};

    /**
     * An undirected weighted graph implemented on-top of an adjacency list.
     * @param {const Graph &} src - The object to copy
     **/
    void operator=(const Graph &src) { adj = src.adj; };

    /**
     * Add an pair of nodes and the weight that constitutes their edge to the graph
     * Add the edge to the minimum heap of edges
     * @param {Edge &} edge - the edge to add to the graph
     **/
    void add_edge(Edge edge)
    {
        adj[edge.first_node()].push_back(edge.distance());
        adj[edge.second_node()].push_back(make_pair(edge.getWeight(), edge.first_node()));
        edgeMinHeap.push(edge);
    }

    /**
     * returns the number of vertices in the graph
     * @return {int}
     **/
    int getSize(){return adj.size();}

    /**
     * returns the ratio of edges per vertex in the graph
     * @return {double}
     **/
    double getDensity(){return (double(edgeMinHeap.size())/double(adj.size()));}

    /**
     * Display the graph by displaying all origin nodes and their adjacent nodes with
     * respect to the weight of the edge.
     **/
    void print()
    {
        for (size_t i = 0; i < adj.size(); i++)
        {
            auto &nodes = adj[i];
            if (nodes.size() > 0)
            {
                std::cout << i << " -> ";
                for (auto node : nodes)
                {
                    // (weight, destination)
                    std::cout << "(" << node.first << "," << node.second << ")"
                              << " ";
                }
                std::cout << std::endl;
            }
        }
    }

    /**
     * Implement Prim's algorithm to find the cost of a minimum spanning tree from an undirected graph.
     * Continually adds the least expensive edge until all edges are added to the tree.
     * @return {pair<weight,int>} - first: the cost of the minimum spanning tree second: number of edges in MST
     **/
    pair<weight, int> prims()
    {
        // Store the distances of nodes and the destination in a priority queue for more performant traversal
        // the values are sorted by the first value in the NodeDistance, which is the weight
        priority_queue<NodeDistance, vector<NodeDistance>, greater<NodeDistance>> heap;

        // The original node (0) has no distance from itself
        heap.push(make_pair(0, 0));

        // Track visited nodes
        vector<bool> added(adj.size(), false);

        // The total cost of the minimum spanning tree
        weight cost = 0;

        //must start at -1 to account for default initial [0,0] edge
        int mst_size = -1;

        //accounting for early exit when mst is complete
        while (mst_size != (adj.size() - 1) && !heap.empty())
        {
            // Find the least-costly edge
            NodeDistance edge;
            edge = heap.top();
            heap.pop();

            weight weight = edge.first;
            int destination_node = edge.second;

            // If the node is not in the tree: add it and increase the cost of the tree
            if (!added[destination_node])
            {
                cost += weight;
                added[destination_node] = true;
                mst_size++;

                // Traverse the adjacent nodes and add all nodes missing from the tree
                for (auto &node_distance : adj[destination_node])
                {
                    int adj_node = node_distance.second;
                    if (added[adj_node] == false)
                        heap.push(node_distance);
                }
            }
        }
        return make_pair(cost, mst_size);
    }

    /**
     * Implement Kruskal's algorithm to find the cost of a minimum spanning tree from an undirected graph.
     * @return {pair<weight,int>} - first: the cost of the minimum spanning tree second: number of edges in MST
     **/
    pair<weight, int> kruskals()
    {
        //set cost to 0
        weight cost = 0;

        //creating disjoint set with number of vertices
        DisjointSet dSet(adj.size());

        //continues creating unions until the mst is complete
        //unoptimized: !edgeMinHeap.empty()
        //optimized: dSet.edgeCount != (adj.size() - 1)
        while (dSet.edgeCount != (adj.size() - 1))
        {

            //getting the fist edge in min heap
            Edge currEdge = edgeMinHeap.top();

            //removing edge from min heap
            edgeMinHeap.pop();

            //adds the cost of the edge if a union is created
            if (dSet.Union(currEdge.first_node(), currEdge.second_node()))
            {
                cost += currEdge.getWeight();
            }
        }
        return make_pair(cost, dSet.edgeCount);
    }
};