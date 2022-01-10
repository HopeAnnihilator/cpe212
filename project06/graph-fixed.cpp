#include "graph.h"

// constructor function for new vertices
VertexNode* new_vertice(string s, VertexNode* vertex) {
    VertexNode* ptr = new VertexNode;
    ptr->vname = s;
    ptr->mark = false;
    ptr->edgePtr = NULL;
    ptr->nextVertex = vertex;
    return ptr;
}

// constructor function for new edges
EdgeNode* new_edge(VertexNode* node, int weight, EdgeNode* edge) {
    EdgeNode *ptr = new EdgeNode;
    ptr->destination = node;
    ptr->weight = weight;
    ptr->nextPtr = edge;
    return ptr;
}

// constructor for empty graph
Graph::Graph() {
    vertices = NULL;
}

// deconstructor for graph
Graph::~Graph() {
    VertexNode* ptr = vertices;
    VertexNode* nextPtr;
    for (; ptr; ptr = nextPtr) {
        if (ptr->edgePtr) {
            // delete edge pointers before vertices
            EdgeNode* ptrEdge;
            EdgeNode* nextEdge;
            ptrEdge = ptr->edgePtr;
            for (; ptrEdge; ptrEdge = nextEdge) {delete ptrEdge; nextEdge = ptrEdge->nextPtr;}
        }
        nextPtr = ptr->nextVertex; delete ptr;
    }
}

// add new vertex with value v
void Graph::AddVertex(string v) {vertices = new_vertice(v, vertices);}

// add new edge for node1 to node2 with weight
void Graph::AddEdge(string s, string d, int w) {
    VertexNode* ptr = WhereIs(s);
    VertexNode* end = WhereIs(d);
    ptr->edgePtr = new_edge(end, w, ptr->edgePtr);
}

// verify vertex is in data
bool Graph::IsPresent(string v) {
    VertexNode* ptr = vertices;
    for (; ptr->nextVertex && ptr->vname != v; ptr = ptr->nextVertex) {}
    if (ptr->vname == v) return true;
    else return false;
}

// find vertex in data
VertexNode* Graph::WhereIs(string v) {
    VertexNode* ptr = vertices;
    for (; ptr->nextVertex && ptr->vname != v; ptr = ptr->nextVertex) {}
    if (ptr->vname == v) return ptr;
    else throw GraphVertexNotFound();
}

// find weight from node1 to node2
int Graph::WeightIs(string s, string d) {
    VertexNode* ptrA = WhereIs(s);
    VertexNode* ptrB = WhereIs(d);

    // verify node has an edge
    if (!ptrA->edgePtr) throw GraphEdgeNotFound();

    // trace edges of node
    EdgeNode* tmpEdge = ptrA->edgePtr;
    for (; tmpEdge->nextPtr && tmpEdge->destination != ptrB; tmpEdge = tmpEdge->nextPtr) {}
    // if node1 doesnt attach to node2 throw error
    if (tmpEdge->destination != ptrB) throw GraphEdgeNotFound();
    else return tmpEdge->weight;
}

// set all node marks to false
void Graph::ClearMarks() {
    for (VertexNode* tmpPtr = vertices; tmpPtr; tmpPtr = tmpPtr->nextVertex) {tmpPtr->mark = false;}
}

// set node mark to true
void Graph::MarkVertex(string v) {
    VertexNode* tmpPtr = vertices;
    for (; tmpPtr->nextVertex && tmpPtr->vname != v; tmpPtr = tmpPtr->nextVertex) {}
    if (tmpPtr->vname == v) tmpPtr->mark = true;
}

// check if node is marked
bool Graph::IsMarked(string v) {
    VertexNode* tmpPtr = vertices;
    for (; tmpPtr->nextVertex && tmpPtr->vname != v; tmpPtr = tmpPtr->nextVertex) {}
    if (tmpPtr->vname == v) return tmpPtr->mark;
    return false;
}

// find branches from node
void Graph::GetToVertices(string V, queue<string>& q) {
    VertexNode* ptr = WhereIs(V);
    if (ptr->edgePtr) {
        for (EdgeNode* tmpEdge = ptr->edgePtr; tmpEdge; tmpEdge = tmpEdge->nextPtr) {
            // check if destination node is marked before adding to queue
            if(!tmpEdge->destination->mark) q.push(tmpEdge->destination->vname);
        }
    }
}

// find path from node1 to node 2 if it exists
// i dont have the book so i hope this is close enough	
void Graph::DepthFirstSearch(string startVertex, string endVertex, queue<string>& path) {
    VertexNode* ptr;
    stack<string> edges;
    queue<string> q;
    deque<string> blackMagic;

    // verify both nodes exist and clear all marks
    if (!(IsPresent(startVertex) && IsPresent(endVertex))) throw GraphVertexNotFound();
    ClearMarks();

    // push starting node to beginning of path and begin traversing it
    for (edges.push(startVertex); !edges.empty() && edges.top() != endVertex;) {
        // if return to a node do not add it to path
        if (!IsMarked(edges.top())) {
            MarkVertex(edges.top());
            blackMagic.push_back(edges.top());
        }
        // get edges of current node, if none pop stack to return to previous node
        // else push queue to stack and clear queue
        GetToVertices(edges.top(), q);
        if (q.empty()) {
            edges.pop();
            if (!blackMagic.empty()) blackMagic.pop_back();
        }
        else for (; !q.empty(); q.pop()) {edges.push(q.front());}
    }
    // if no edges, return empty path
    // else push ending node to deque and set path
    if (!edges.empty()) {
        for (blackMagic.push_back(edges.top()); !blackMagic.empty(); blackMagic.pop_front()) {path.push(blackMagic.front());}
    }
}