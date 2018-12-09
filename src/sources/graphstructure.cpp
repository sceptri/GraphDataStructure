#include "graphstructure.h"
#include <iostream>


//-----------------Edge functions-------------------------

//compares if both 'to' and 'from' of both edges are the same
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

//compares if both 'to' and 'from' of both edges are the same ||friend version
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

//assigns 'to' and 'from' of one edge ot another
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

//sets default edge to be a self loop with faulty values
VertexEdges::VertexEdges()
{
	Edge * err_edges  = new Edge[1];
	err_edges[0].from = -1;
	err_edges[0].to = -1;
	this->edges = err_edges;
	this->num = 1;
}

//destructor for vertex_edges
VertexEdges::~VertexEdges()
{
    if(num > 0)
    {
        delete [] edges;
    }
}


//----------------Graph functions-------------------------

//constructor, which sets all variables, 'edges' and 'vertices' is set to faulty values, later to be managed by code
Graph::Graph() : edge_count(0), vertex_count(0)
{
	vertices = new int[++vertex_count];
	vertices[0] = -1;

	edges = new Edge[++edge_count];
	edges[0] = Edge(-1, -1);
}

//deletes all dynamically assigned variables
Graph::~Graph()
{
    if(vertex_count > 0)
    {
        delete vertices;
    }
    if(edge_count > 0)
    {
        delete [] edges;
    }
}

//constructor, which sets all variables, 'edges' and 'vertices' is set to faulty values, later to be managed by code
Graph::Graph(Graph & graph) : edge_count(0), vertex_count(0)
{
	vertices = new int[++vertex_count];
	vertices[0] = -1;

	edges = new Edge[++edge_count];
	edges[0] = Edge(-1, -1);
}

//ONE CAN NOT assign one graph object to another, if tried, none of those object is changed
Graph & Graph::operator=(Graph  & graph)
{
    return *this;
}

//checks if vertex with given value already exists, if so returns error, else adds vertex to vertices array and removes all faulty vertices from array in question
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
    removeFaultyVertices(vertices, vertex_count);

    return true;
}

//adds edge only if both vertices exist, after adding edge checks if it's not duplicate or self-loop
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

    removeDoubles(edges, edge_count);
    removeSelfLoops(edges, edge_count);

    return true;
}

//removes vertex from vertices, if it exists, and any associated edge
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

    VertexEdges edges_to_delete = VertexEdges();

    for(int i = 0; i < vertex_count; i++)
    {
    	if(i == v_index)
    	{
    		continue;
    	}
    	else if(adjacent(vertices[i], v)) //checks if there exist an edge with this vertex, if so adds it to edges to delete array
        { 
            pushToArr(edges_to_delete.edges, getEdge(i, v), edges_to_delete.num);
            pushToArr(edges_to_delete.edges, getEdge(v, i), edges_to_delete.num);
        }
    }

    removeSelfLoops(edges_to_delete.edges, edges_to_delete.num); //removes all self-loops, mainly error one created when constructing object

    for(int i = 0; i < edges_to_delete.num; i++)
    {
        pullFromArr(edges, edges_to_delete.edges[i], edge_count);
    }

    pullFromArr(vertices, v, vertex_count); //Needs to be removed after edges, otherwise adjacency test will fail

    return true;
}

//removes edge from 'edges'
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

//checks if there exists edge(u,v) or (v, u)
bool Graph::adjacent(int u, int v) const
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

//returns all edges that have 'v' as 'to' variable
VertexEdges Graph::inEdges(int v) const
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

//returns all edges that have 'v' as 'from' variable
VertexEdges Graph::outEdges(int v) const
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

// ------------------ getters -----------------------

//returns opposite vertex of an edge if the first one is part of the edge
int Graph::getOpposite(int v, Edge edge) const
{
	if(edge.from == v)
	{
		return edge.to;
	}
	else if(edge.to == v)
	{
		return edge.from;
	}
	else
	{
		return -1;
	}
}

int Graph::getVertexCount() const
{
    return vertex_count;
}

int Graph::getEdgeCount() const
{
    return edge_count;
}

Edge& Graph::getEdge(int v, int u) const
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

int Graph::getVertex(int index) const
{
	if(index < vertex_count)
	{
		return this->vertices[index];
	}
	else
	{
		return -1;
	}
}

// ------------------- private ----------------------

//copies arrayPointer to a tempArray pointer, then on arrayPointer creates a new, one longer array, copies all elements there and on the last spot a new one, deleting tempArray at the end
template<typename T>
void Graph::pushToArr(T* & arr, T element, int & arr_length) const
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

//copies arrayPointer to a tempArray pointer, then on arrayPointer creates a new, one shorter, array, omitting the element that was to be removed, deleting tempArray at the end
template<typename T>
void Graph::pullFromArr(T* & arr, T element, int & arr_length) const
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

//removes all self-loop edges e.g.(u, u)
int Graph::removeSelfLoops(Edge* & sl_edges, int & length) const
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
    
    return removed;
}

//removes all duplicates
int Graph::removeDoubles(Edge* & d_edges, int & length) const
{
    int removed = 0;

    for(int i = 0; i < length; i++)
    {
        for(int j = i+1; j < length; j++)
        {
            if(d_edges[j] == d_edges[i])
            {
                pullFromArr(d_edges, d_edges[j], length);
                removed++;
            }
        }
    }
    return removed;
}


//removes all integers lower than one
int Graph::removeFaultyVertices(int* & f_vertices, int & length) const
{
	int removed = 0;

	for(int i = 0; i < length; i++)
	{
		if(f_vertices[i] < 0)
		{
			pullFromArr(f_vertices, f_vertices[i], length);
			removed++;
		}
		else
		{
			continue;
		}
	}

	return removed;
}




