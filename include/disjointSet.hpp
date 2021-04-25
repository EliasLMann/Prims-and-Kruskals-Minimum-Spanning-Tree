/* Elias Mann - SMU CS 3353 2021 Spring PA04
 * 
 * A disjoint set data structure used to implement kruskal's algorithm*/

//lesson on Disjoint sets from: https://www.youtube.com/watch?v=wU6udHRIkcc

#pragma once

#include <iostream>
using namespace std;

class DisjointSet {
private:
    //array of parents, declared in heap. If parent is negative, it represents the wight of the set
    //the greater the absolute value of the weight, the more weight the given set has.
    int* mParent;
    //counting number of sets
    //int mMaxWeight = -1;
    int mNumV = 0;

public:
    int edgeCount;
    //Constructor passing in number of vertices
    DisjointSet(int numV){
        //setting numSets to total number of vertices
        mNumV = numV;
        edgeCount = 0;
        //mMaxWeight = -1;
        //setting all vertices to subsets with weight of -1
        mParent = new int[numV];
        for (int i = 0; i < numV; i++) {
            mParent[i] = -1;
        }
    }

    //destructor
    ~DisjointSet(){ delete [] mParent;}
  
    //collapsing find method:
    //when the root of a given subset containing the vertex is found, 
    //the parent of the vertex is set to the root node for constant lookup time
    int find(int v){

        //flag for if a given index has a parent index
        bool hasParent = false;

        //saving initial vertex for collapse
        int initialVertex = v;

        //finds root node of subset containing given vertex
        while(mParent[v] >= 0){
            v = mParent[v];
            hasParent = true;
        }

        //collapses subset by setting parent of initial 
        //vertex to the root node of the subset
        if(hasParent){
            mParent[initialVertex] = v;
        }
        return v;
    }
  
    //weighted union function returns whether or not union was created
    bool Union(int v1, int v2){
        // Find the root nodes of the sets containing v1 and v2
        int v1Root = find(v1);
        int v2Root = find(v2);

        //indicates whether vertex union created cycle
        bool isCycle = true;
  
        //If v1 and v1 are in the same subset, this 
        // union creates a cycle is not formed 
        if (v1Root != v2Root){

            //increments the number of edges when union is formed
            edgeCount++;

            //if v1 and v2 are in different subsets,
            //the union will formed
            isCycle = false;
            
            //if the root of set1 has more weight than, or equal weight to, the root of set 2
            if (mParent[v1Root] <= mParent[v2Root]) {

                //the weight of set 2 is added to the weight of set 1
                mParent[v1Root] += mParent[v2Root];

                //the mParent of the root of set 2 is set to the root of set 1
                mParent[v2Root] = v1Root;

                //sets the weight of the largest subset
                // if(mParent[v1Root] < mMaxWeight){
                //     mMaxWeight = mParent[v1Root];
                // }
            }

            //if the root of set1 has less weight than the root of set 2
            else{

                //the weight of set 2 is added to the weight of set 1
                mParent[v2Root] += mParent[v1Root];

                //the mParent of the root of set 1 is set to the root of set 2
                mParent[v1Root] = v2Root;

                //sets the weight of the largest subset
                // if(mParent[v2Root] < mMaxWeight){
                //     mMaxWeight = mParent[v2Root];
                // }
            }
        }

        //if the desired union is not a cycle, the union was formed
        return !isCycle;
    }

    //returns whether or not the minimum spanning tree has been created
    // bool isComplete() {return mMaxWeight == -(mNumV);}
};