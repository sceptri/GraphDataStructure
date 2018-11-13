#ifndef GRAPHSTRUCUTURE_H
#define GRAPHSTRUCUTURE_H
#pragma once

//Add function called removeDoubles, check memory

struct Edge
{
    Edge(int v_from, int v_to);
    Edge();

    int from;
    int to;

    bool operator==(const Edge & edge);
    friend bool operator==(const Edge & edge1, const Edge & edge2);
};

struct VertexEdges
{
    int num;
    Edge * edges;

    ~VertexEdges();
};

class Graph
{
public:
    Graph();
    ~Graph();
    Graph(Graph & graph);

    Graph & operator=(Graph & graph);

    bool adjacent(int u, int v);
    VertexEdges inEdges(int v);
    VertexEdges outEdges(int v);
    //int getOpposite(int v, int* edge);
    Edge& getEdge(int v, int u); //Returns (v,u) if it exists, never (u,v)
    void addVertex(int value);
    bool addEdge(int v, int u);
    bool removeVertex(int v);
    bool removeEdge(int v, int u);

private:
    template<typename T>
    T* & pushToArr(T* & arr, T element, int old_arr_length);

    template<typename T>
    T* & pullFromArr(T* & arr, T element, int old_arr_length);
        //sl_egdes - self loop edges
    int removeSelfLoops(Edge* & sl_edges, int length);//return number of removed edges

    int edge_count;
    int vertex_count;
    int * vertices;
    Edge* edges;
};

#endif // GRAPHSTRUCUTURE_H
