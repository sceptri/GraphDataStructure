#ifndef GRAPHSTRUCUTURE_H
#define GRAPHSTRUCUTURE_H

struct Edge
{
    Edge(int v_from, int v_to);
    Edge();

    int from;
    int to;

    bool operator==(const Edge & edge);
    friend bool operator==(const Edge & edge1, const Edge & edge2);

    Edge& operator=(const Edge & edge);
};

struct VertexEdges
{
    int num;
    Edge * edges;

    VertexEdges();
    ~VertexEdges();
};

class Graph
{
public:
    Graph();
    ~Graph();
    Graph(Graph & graph);

    bool addVertex(unsigned int value); //adds vertex with only positive value
    bool addEdge(int v, int u);
    bool removeVertex(int v);
    bool removeEdge(int v, int u);

    bool adjacent(int u, int v) const;

    VertexEdges inEdges(int v) const;
    VertexEdges outEdges(int v) const;

    int getVertexCount() const;
    int getEdgeCount() const;
    Edge& getEdge(int v, int u) const; //Returns (v,u) if it exists, never (u,v)
    int getVertex(int index) const;
    int getOpposite(int v, Edge edge) const;



private:
    template<typename T>
    void pushToArr(T* & arr, T element, int & arr_length) const;

    template<typename T>
    void pullFromArr(T* & arr, T element, int & arr_length) const;
        //sl_egdes - self loop edges
    int removeSelfLoops(Edge* & sl_edges, int & length) const;//return number of removed edges

    int removeDoubles(Edge* & d_edges, int & length) const;

    int removeFaultyVertices(int* & f_vertices, int & length) const;

    Graph & operator=(Graph & graph); //GRAPH OBJECTS CANNOT BE ASSIGNED TO EACH OTHER

    int edge_count;
    int vertex_count;
    int * vertices;
    Edge* edges;
};

#endif // GRAPHSTRUCUTURE_H
