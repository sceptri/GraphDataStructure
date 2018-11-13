#include "graphstructure.h"


//-----------------Edge functions-------------------------
bool Edge::operator==(const Edge & edge)
{
    if(edge.from == this->from && edge.to == this->to)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool operator==(const Edge & edge1, const Edge & edge2)
{
    if(edge1.from == edge2.from && edge1.to == edge2.to)
    {
        return true;
    }
    else
    {
        return false;
    }
}

Edge::Edge(int v_from, int v_to)
{
    from = v_from;
    to = v_to;
}

Edge::Edge() : to(0), from(0)
{
}

//----------------VertexEdges functions-------------------
VertexEdges::~VertexEdges()
{
    delete [] edges;
}



//----------------Graph functions-------------------------
Graph::Graph() : edge_count(0), vertex_count(0)
{
}

Graph::~Graph()
{
    delete vertices;
    delete [] edges;
}

Graph::Graph(Graph & graph) : edge_count(0), vertex_count(0)
{
}

Graph & Graph::operator=(Graph  & graph)
{
    return *this;
}

void Graph::addVertex(int value)
{
    if(vertex_count > 0)
    {
        for(int i = 0; i < vertex_count; i++)
        {
            if(vertices[i] == value)
            {
                return;
            }
        }

        vertices = pushToArr(vertices, value, vertex_count++);
    }
    else
    {
        vertices = new int[1];
        vertices[0] = value;
        vertex_count++;
    }
}

bool Graph::addEdge(int v, int u)
{
    {
        bool v_exists = false;
        bool u_exists = false;

        for(int i = 0; i < vertex_count; i++)
        {
            if(vertices[i] == v)
            {
                v_exists = true;
            }
            if(vertices[i] == u)
            {
                u_exists = true;
            }
        }

        if(!v_exists || !u_exists)
        {
            return false;
        }
    }

    Edge edge = {v, u};
    edges = pushToArr(edges, edge, edge_count++);

    return true;
}

bool Graph::removeVertex(int v)
{
    bool v_exists = false;
    int v_index = -1;

    for(int i = 0; i < vertex_count; i++)
    {
        if(vertices[i] == v)
        {
            v_exists = true;
            v_index = i;
        }
    }

    if(!v_exists)
    {
        return false;
    }

    vertices = pullFromArr(vertices, v, vertex_count--);

    Edge* edges_to_delete = 0;
    int length = 0;

    for(int i = 0; i < vertex_count; i++)
    {
        if(adjacent(i, v))
        {
            edges_to_delete = pushToArr(edges_to_delete, getEdge(i, v), length++);
            edges_to_delete = pushToArr(edges_to_delete, getEdge(v, i), length++);
        }
    }

    length -= removeSelfLoops(edges_to_delete, length);
    for(int i = 0; i < length; i++)
    {
        edges = pullFromArr(edges, edges_to_delete[i], edge_count--);
    }

    return true;
}

bool Graph::removeEdge(int v, int u)
{
    {
        bool v_exists = false;
        bool u_exists = false;

        for(int i = 0; i < vertex_count; i++)
        {
            if(vertices[i] == v)
            {
                v_exists = true;
            }
            if(vertices[i] == u)
            {
                u_exists = true;
            }
        }

        if(!v_exists || !u_exists)
        {
            return false;
        }
    }

    Edge edge = {v, u};
    edges = pullFromArr(edges, edge, edge_count--);

    return true;
}

bool Graph::adjacent(int u, int v)
{
    Edge edge1 = {u, v};
    Edge edge2 = {v, u};
    for(int i = 0; i < edge_count; i++)
    {
        if(edges[i] == edge1 || edges[i] == edge2)
        {
            return true;
        }
    }

    return false;
}

VertexEdges Graph::inEdges(int v)
{
    VertexEdges v_edges = {0,0};

    for(int i = 0; i < edge_count; i++)
    {
        if(edges[i].to == v)
        {
            v_edges.edges = pushToArr(v_edges.edges, edges[i], v_edges.num++);
        }
    }

    return v_edges;
}

VertexEdges Graph::outEdges(int v)
{
    VertexEdges v_edges = {0,0};

    for(int i = 0; i < edge_count; i++)
    {
        if(edges[i].from == v)
        {
            v_edges.edges = pushToArr(v_edges.edges, edges[i], v_edges.num++);
        }
    }

    return v_edges;
}

Edge& Graph::getEdge(int v, int u)
{
    Edge edge = {v, u};
    for(int i = 0; i < edge_count; i++)
    {
        if(edges[i] == edge)
        {
            return edges[i];
        }
    }

    static Edge error = {-1, -1};
    return error;
}

//private
template<typename T>
T* & Graph::pushToArr(T* & arr, T element, int old_arr_length)
{
    if(old_arr_length == 0)
    {
        arr = new T[old_arr_length+1];
        arr[old_arr_length] = element;
    }
    else
    {
        T * temp_arr = arr;
        arr = new T[old_arr_length+1];

        for(int i = 0; i < old_arr_length; i++)
        {
            arr[i] = temp_arr[i];
        }

        arr[old_arr_length] = element;

        delete [] temp_arr;
    }

    return arr;
}

template<typename T>
T* & Graph::pullFromArr(T* & arr, T element, int old_arr_length)
{
    if(old_arr_length < 1)
    {
       return  arr;
    }
    else
    {
        T * temp_arr = arr;
        arr = new T[old_arr_length-1];

        int index = 0;
        for(int i = 0; i < old_arr_length; i++)
        {
            if(temp_arr[i] == element)
            {
                continue;
            }
            else
            {
                arr[index++] = temp_arr[i];
            }
        }

        delete [] temp_arr;

        return arr;
    }
}

int Graph::removeSelfLoops(Edge* & sl_edges, int length)
{
    int removed = 0;

    for(int i = 0; i < length; i++)
    {
        if(sl_edges[i].to == sl_edges[i].from)
        {
            sl_edges = pullFromArr(sl_edges, sl_edges[i], length--);
            removed++;
        }
    }

    return removed;
}
