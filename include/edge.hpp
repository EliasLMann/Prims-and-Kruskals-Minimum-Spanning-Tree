/* Nick Wall, Elias Mann - SMU CS 3353 2021 Spring PA04
 * 
 * Edge is a class that describes a connection between two nodes on a graph, edges are graph class agnostic
 * and only serve to encapsulate a weight and a node pairing. */

#pragma once

// STL Dependencies
#include <utility>
#include <ostream>

using std::make_pair;
using std::ostream;
using std::pair;

typedef double weight;
typedef int first_node;
typedef int second_node;
typedef pair< first_node, second_node > Nodes;
typedef pair< weight, second_node > NodeDistance;

class Edge
{

private:
    /**
     * The nodes that define the edge
     */
    int v1, v2;

    /**
     * The the weight of an edge, used to calculate the min tree
     */
    weight edge_weight;

public:
    /**
     * Definition for a pair of nodes and their weight on a graph.
     * @constructor
     */
    Edge(){};

    /**
     * Definition for a pair of nodes and their weight on a graph.
     * @constructor
     * @param {int} first_node - the origin node
     * @param {int} second_node - the destination node
     * @param {int} weight - the weight of the connection between the nodes
     */
    Edge(int first_node, int second_node, weight weight) : v1(first_node), v2(second_node), edge_weight(weight){};

    /**
     * Definition for a pair of nodes and their weight on a graph.
     * @constructor
     * @param {const Edge&} src - The object to copy
     */
    Edge(const Edge &src)
    {
        v1 = src.v1;
        v2 = src.v2;
        edge_weight = src.edge_weight;
    };

    /**
     * Definition for a pair of nodes and their weight on a graph.
     * @destructor
     */
    ~Edge(){};

    /**
     * Definition for a pair of nodes and their weight on a graph.
     * @param {const Edge&} src - The object to copy
     */
    void operator=(const Edge &src)
    {
        v1 = src.v1;
        v2 = src.v2;
        edge_weight = src.edge_weight;
    };

    /**
     * > operator for edge for use in priority queue. compares by edge weight
     */
    bool operator>(const Edge &rhs) const { return (edge_weight > rhs.edge_weight); }

    /**
     * The weight of a connection between the nodes that makeup the edge.
     */
    weight getWeight() const { return edge_weight; };

    /**
     * The origin node
     * @return {int} - the first node used to construct the edge
     */
    int first_node() const { return v1; };

    /**
     * The destination node
     * @return {int} - the second node used to construct the edge
     **/
    int second_node() const { return v2; };

    /**
     * The distance and secondary node that describes the cost from origin
     * to destination
     * @return {pair<int, int>} - the <weight, destination> pair
     **/
    NodeDistance distance() const { return make_pair(edge_weight, v2); };
};

/**
 * Insert description of the edge to an output stream
 * @param {ostream &} os - the stream to write to
 * @param {const Edge&} edge - the edge to describe
 * @return {ostream&} - the modified stream
 **/
ostream &operator<<(ostream &os, const Edge &edge)
{
    os << edge.first_node() << " <- " << edge.getWeight() << " -> " << edge.second_node();
    return os;
}