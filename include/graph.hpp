/* Nick Wall - SMU CS 3353 2021 Spring PA04
 * 
 * Graph representation of a weighted undirected graph using an adjacency list. Implements prim's and kruskal's algorithms
 * to find the minimum spanning tree. */

#pragma once

// STL Dependencies
#include <iostream>
#include <queue>
#include <algorithm>
#include <cstring>

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
    priority_queue<Edge, vector<Edge>, greater<Edge>> edgeMinHeap;;


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
    Graph(const Graph &src) { adj = src.adj; edgeMinHeap = src.edgeMinHeap; };

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
     * Add an pair of nodes and the wieght that constitutes their edge to the graph
     * @param {Edge &} edge - the edge to add to the graph
     **/
    void add_edge(Edge &edge) {
         adj[edge.first_node()].push_back(edge.distance());
         //adds edge to min heap
         edgeMinHeap.push(edge);
         }

    void testQueue(){
        while(!edgeMinHeap.empty()){
            Edge currEdge = edgeMinHeap.top();
            edgeMinHeap.pop();
            std:: cout <<  currEdge.weight() << std::endl;
        }
    }

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
     * @return {int} - the cost of the minimum spanning tree
     **/
    int prims()
    {
        // Store the distances of nodes and the destination in a priority queue for more performant traversal
        // the values are sorted by the first value in the NodeDistance, which is the weight
        priority_queue<NodeDistance, vector<NodeDistance>, greater<NodeDistance>> heap;

        // The original node (0) has no distance from itself
        heap.push(make_pair(0, 0));

        // Track visited nodes
        vector<bool> added(adj.size(), false);

        // The total cost of the minimum spanning tree
        int cost = 0;

        while (!heap.empty())
        {

            // Find the least-costly edge
            NodeDistance edge;
            edge = heap.top();
            heap.pop();

            int weight = edge.first;
            int destination_node = edge.second;

            // If the node is not in the tree: add it and increase the cost of the tree
            if (!added[destination_node])
            {
                cost += weight;
                added[destination_node] = true;

                // Traverse the adjacent nodes and add all nodes missing from the tree
                for (auto &node_distance : adj[destination_node])
                {
                    if (added[node_distance.second] == false)
                        heap.push(node_distance);
                }
            }
        }
        return cost;
    }

    int kruskals(){
        //set cost to 0
        int cost = 0;

        //creating disjoint set with number of vertices
        DisjointSet dSet(adj.size());

        //continues cretig unions until the mst is complete
        while(!dSet.isComplete()){

            //getting the fist edge in min heap
            Edge currEdge = edgeMinHeap.top();

            //removing edge from min heap
            edgeMinHeap.pop();

            //adds the cost of the edge if a union is created
            if(dSet.Union(currEdge.first_node(), currEdge.second_node())){
                cost += currEdge.weight();
            }
        }
        return cost;
    }
};