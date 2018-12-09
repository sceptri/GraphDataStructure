#include "graphstructure.h"
#include <iostream>


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

Edge& Edge::operator=(const Edge & edge)
{
    this->from = edge.from;
    this->to = edge.to;

    return *this;
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
VertexEdges::VertexEdges()
{
	Edge * err_edges  = new Edge[1];
	err_edges[0].from = -1;
	err_edges[0].to = -1;
	this->edges = err_edges;
	this->num = 1;
}

VertexEdges::~VertexEdges()
{
    std::cout << "destructor of vertexEdges" << std::endl;
    if(num > 0)
    {
        delete [] edges;
    }
}



//----------------Graph functions-------------------------
Graph::Graph() : edge_count(0), vertex_count(0)
{
	vertices = new int[++vertex_count];
	vertices[0] = -1;

	edges = new Edge[++edge_count];
	edges[0] = Edge(-1, -1);
}

Graph::~Graph()
{
    std::cout << "destructor of Graph" << std::endl;
    if(vertex_count > 0)
    {
        delete vertices;
    }
    if(edge_count > 0)
    {
        delete [] edges;
    }
}

Graph::Graph(Graph & graph) : edge_count(0), vertex_count(0)
{
	vertices = new int[++vertex_count];
	vertices[0] = -1;

	edges = new Edge[++edge_count];
	edges[0] = Edge(-1, -1);
}

Graph & Graph::operator=(Graph  & graph)
{
    return *this;
}

bool Graph::addVertex(unsigned int value)
{
	for(int i = 0; i < vertex_count; i++)
    {
		if(vertices[i] == value)
        {
			return false;
        }
    }

    pushToArr(vertices, int(value), vertex_count);


    return true;
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

    Edge edge = Edge(v, u);
    pushToArr(edges, edge, edge_count);

    std::cout <<  "Edge Count(INSIDE addEdge): " << getEdgeCount() << std::endl;

    for (int i = 0; i < edge_count; i++)
    {
        std::cout << "(" << edges[i].from << ", " << edges[i].to << ")" << std::endl; 
    }

    removeDoubles(edges, edge_count);
    for (int i = 0; i < edge_count; i++)
    {
        std::cout << "(" << edges[i].from << ", " << edges[i].to << ")" << std::endl; 
    }

    removeSelfLoops(edges, edge_count);
    for (int i = 0; i < edge_count; i++)
    {
        std::cout << "(" << edges[i].from << ", " << edges[i].to << ")" << std::endl; 
    }


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

    pullFromArr(vertices, v, vertex_count);

    Edge* edges_to_delete = 0;
    int length = 0;

    for(int i = 0; i < vertex_count; i++)
    {
        if(adjacent(i, v))
        { 
            pushToArr(edges_to_delete, getEdge(i, v), length);
            pushToArr(edges_to_delete, getEdge(v, i), length);
        }
    }
    for(int i = 0; i < length; i++)
    {
        pullFromArr(edges, edges_to_delete[i], edge_count);
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

    Edge edge = Edge(v, u);
    pullFromArr(edges, edge, edge_count);

    return true;
}

bool Graph::adjacent(int u, int v)
{
    Edge edge1 = Edge(u, v);
    Edge edge2 = Edge(v, u);
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

    VertexEdges v_edges = VertexEdges();

    for(int i = 0; i < edge_count; i++)
    {
        if(edges[i].to == v)
        {
            pushToArr(v_edges.edges, edges[i], v_edges.num);
        }
    }
    removeSelfLoops(v_edges.edges, v_edges.num);

    return v_edges;
}

VertexEdges Graph::outEdges(int v)
{
	VertexEdges v_edges = VertexEdges();

    for(int i = 0; i < edge_count; i++)
    {
       if(edges[i].from == v)
        {
            pushToArr(v_edges.edges, edges[i], v_edges.num);
        }
    }
    removeSelfLoops(v_edges.edges, v_edges.num);
    return v_edges;
}

Edge& Graph::getEdge(int v, int u)
{
    Edge edge = Edge(v, u);
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

// ------------------ getters -----------------------

int Graph::getVertexCount()
{
    return vertex_count;
}

int Graph::getEdgeCount()
{
    return edge_count;
}

// ------------------- private ----------------------
template<typename T>
void Graph::pushToArr(T* & arr, T element, int & arr_length)
{
    if(arr_length == 0)
    {
        arr = new T[++arr_length];
        arr[0] = element;
    }
    else
    {
        T * temp_arr = arr;
        arr = new T[++arr_length];

        for(int i = 0; i < arr_length; i++)
        {
        	if(i == arr_length-1)
        	{
        		arr[i] = element;
        	}
        	else
        	{
        		arr[i] = temp_arr[i];
        	}
        }

        delete [] temp_arr;
    }

}

template<typename T>
void Graph::pullFromArr(T* & arr, T element, int & arr_length)
{
    if(arr_length < 1)
    {
       return;
    }
    else
    {
        T * temp_arr = arr;
        arr = new T[--arr_length];

        bool isRemoved = false;

        int index = 0;
        for(int i = 0; i <= arr_length; i++)
        {
            if(temp_arr[i] == element && !isRemoved)
            {
            	isRemoved = true;
                continue;
            }
            else
            {
                arr[index++] = temp_arr[i];
            }
        }

        delete [] temp_arr;

    }
}

int Graph::removeSelfLoops(Edge* & sl_edges, int & length)
{
    int removed = 0;

    for(int i = 0; i < length; i++)
    {
        if(sl_edges[i].to == sl_edges[i].from)
        {
            pullFromArr(sl_edges, sl_edges[i], length);
            removed++;
        }
    }
    std::cout << "Removed self loops: " << removed << std::endl;
    
    return removed;
}

int Graph::removeDoubles(Edge* & d_edges, int & length)
{
    std::cout << "Removed doubles: " << std::endl;
    std::cout << "length: " << length << std::endl;
    int removed = 0;

    for (int i = 0; i < length; i++)
    {
        std::cout << "(" << d_edges[i].from << ", " << d_edges[i].to << ")" << std::endl; 
    }

    for(int i = 0; i < length; i++)
    {
        std::cout << "i: " << i <<std::endl;

        for(int j = i+1; j < length; j++)
        {
            std::cout << "j: " << j <<std::endl;
            if(d_edges[j] == d_edges[i])
            {
                pullFromArr(d_edges, d_edges[j], length);
                removed++;

                for (int i = 0; i < length; i++)
                {
                    std::cout << "(" << d_edges[i].from << ", " << d_edges[i].to << ")" << std::endl; 
                }
            }
        }
    }
    std::cout << "Removed doubles: " << removed << std::endl;
    return removed;
}
