#include <iostream>
#include <vector>

using namespace std;

template <class N, class E> class Edge;

template <class N, class E>
class Node {
public:
    N info;
    vector< Edge<N,E> > edges;
    Node(N inf) {
        info = inf;
    }
};

template <class N, class E>
class Edge {
public:
    E value;
    Node<N,E> *destination;
    Edge(Node<N,E> *dest, E val) {
        value = val;
        destination = dest;
    }
};

template <class N, class E>
class Graph {
    vector< Node<N,E> *> nodes;
public:
    Graph();
    ~Graph();
    Graph & addNode(const N &inf);
    Graph & addEdge(const N &begin, const N &end, const E &val);
    Graph & removeEdge(const N &begin, const N &end);
    E & edgeValue(const N &begin, const N &end);
    unsigned numEdges(void) const;
    unsigned numNodes(void) const;
    void print(std::ostream &os) const;
};

template <class N, class E>
std::ostream & operator<<(std::ostream &out, const Graph<N,E> &g);


// exception NodeAlreadyExists
template <class N>
class NodeAlreadyExists
{
public:
    N info;
    NodeAlreadyExists(N inf) { info=inf; }
};
template <class N>
std::ostream & operator<<(std::ostream &out, const NodeAlreadyExists<N> &no)
{ out << "Node already exists: " << no.info; return out; }


// exception NodeDoesNotExist
template <class N>
class NodeDoesNotExist {
public:
    N info;
    NodeDoesNotExist(N inf) {
        info = inf;
    }
};

template <class N>
std::ostream & operator<<(std::ostream &out, const NodeDoesNotExist<N> &no)
{ out << "Node does not exist: " << no.info; return out; }

template <class N> class EdgeAlreadyExists{
public:
    N node1, node2;
    EdgeAlreadyExists(N n1, N n2){
        this->node1 = n1, this->node2 = n2;
    }
};

template <class N> std::ostream& operator<<(std::ostream &out, const EdgeAlreadyExists<N> &edge){
    out << "Edge already exists: " << edge.node1 << " , " << edge.node2;
    return out;
}

template <class N> class EdgeDoesNotExist{
public:
    N node1, node2;
    EdgeDoesNotExist(N n1, N n2){
        this->node1 = n1, this->node2 = n2;
    }
};

template <class N> std::ostream& operator<<(std::ostream &out, const EdgeDoesNotExist<N> &edge){
    out << "Edge does not exist: " << edge.node1 << " , " << edge.node2;
    return out;
}

template <class N, class E> Graph<N, E>::Graph() {
    ;
}

template <class N, class E> Graph<N, E>::~Graph() {
    ;
    //need to free data from nodes vector
}

template <class N, class E> unsigned Graph<N, E>::numNodes() const {
    return this->nodes.size();
}

template <class N, class E> unsigned Graph<N, E>::numEdges() const {
    unsigned sum = 0;
    for(int i = 0; i < this->numNodes(); i++){
        sum += (*(this->nodes[i])).edges.size();
    }
    return sum;
}

template <class N, class E> Graph<N,E>& Graph<N, E>::addNode(const N &inf) {
    for(int i = 0; i < this->numNodes(); i++){
        if( (*(this->nodes[i])).info == inf ){
            NodeAlreadyExists<string> error(inf);
            throw error;      //stops here
        }
    }
    Node<string, int>* node = new Node<string, int>(inf);
    this->nodes.push_back(node);
    return *this;
}

template <class N, class E> Graph<N, E>& Graph<N,E>::addEdge(const N &begin, const N &end, const E &val) {
    int idxBegin = -1;
    int idxEnd = -1;
    for(int i = 0; i < this->numNodes(); i++){
        if( (*(this->nodes[i])).info == begin  )
            idxBegin = i;
        if( (*(this->nodes[i])).info == end  )
            idxEnd = i;
        if(idxBegin != -1 && idxEnd != -1)
            break;
    }

    if(idxBegin == -1){
        NodeDoesNotExist<string> error(begin);
        throw error;
    }
    if(idxEnd == -1){
        NodeDoesNotExist<string> error(end);
        throw error;
    }

    for(int i = 0; i < (*(this->nodes[idxBegin])).edges.size(); i++){
        if( (*(this->nodes[idxBegin])).edges[i].destination == this->nodes[idxEnd] ){
            EdgeAlreadyExists<string> error(begin, end);
            throw error;
        }
    }

    Edge<string ,int> edge(this->nodes[idxEnd], val);
    (*(this->nodes[idxBegin])).edges.push_back(edge);
    return *this;
}

template <class N, class E> E& Graph<N,E>::edgeValue(const N &begin, const N &end) {
    int idxBegin = -1;
    int idxEnd = -1;
    for(int i = 0; i < this->numNodes(); i++){
        if( (*(this->nodes[i])).info == begin  )
            idxBegin = i;
        if( (*(this->nodes[i])).info == end  )
            idxEnd = i;
        if(idxBegin != -1 && idxEnd != -1)
            break;
    }

    if(idxBegin == -1){
        NodeDoesNotExist<string> error(begin);
        throw error;
    }
    if(idxEnd == -1){
        NodeDoesNotExist<string> error(end);
        throw error;
    }

    for(int i = 0; i < (*(this->nodes[idxBegin])).edges.size(); i++){
        if( (*(this->nodes[idxBegin])).edges[i].destination == this->nodes[idxEnd] ){
            return (*(this->nodes[idxBegin])).edges[i].value;
        }
    }

    EdgeDoesNotExist<string> error(begin, end);         // if the edge isn't found
    throw error;
}

template <class N, class E> Graph<N, E>& Graph<N, E>::removeEdge(const N &begin, const N &end) {
    int idxBegin = -1;
    int idxEnd = -1;
    for(int i = 0; i < this->numNodes(); i++){
        if( (*(this->nodes[i])).info == begin  )
            idxBegin = i;
        if( (*(this->nodes[i])).info == end  )
            idxEnd = i;
        if(idxBegin != -1 && idxEnd != -1)
            break;
    }

    if(idxBegin == -1){
        NodeDoesNotExist<string> error(begin);
        throw error;
    }
    if(idxEnd == -1){
        NodeDoesNotExist<string> error(end);
        throw error;
    }
    for(int i = 0; i < (*(this->nodes[idxBegin])).edges.size(); i++){
        if( (*(this->nodes[idxBegin])).edges[i].destination == this->nodes[idxEnd] ){
            (*(this->nodes[idxBegin])).edges.erase((*(this->nodes[idxBegin])).edges.begin() + i);
            return *this;
        }
    }

    EdgeDoesNotExist<string> error(begin, end);         // if the edge isn't found
    throw error;
}

template <class N, class E> void Graph<N, E>::print(std::ostream &os) const {
    std::ostringstream str;
    for(int i = 0; i < this->numNodes(); i++){
        str << "( " << (*(this->nodes[i])).info;
        for(int e = 0; e < (*(this->nodes[i])).edges.size(); e++){
            N info = (*((*(this->nodes[i])).edges[e].destination )).info;
            str << "[ " << info << " " << (*(this->nodes[i])).edges[e].value << "] ";
        }
        str << ") ";
    }
    os << str.str();
}

template<class N, class E> std::ostream& operator<<(std::ostream& out, Graph<N, E> &graph){
    graph.print(out);
    return out;
}
