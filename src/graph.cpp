#include "edge.h"
#include "node.h"
#include "graph.h"
using namespace FuckNamespaces;

Graph::~Graph() {
    while(!nodes.empty()) {
        auto it = nodes.begin();
        Node *node = *it;
        delete node;
        nodes.erase(it);
    }

    while(!edges.empty()) {
        auto it = edges.begin();
        Edge *edge = *it;
        delete edge;
        edges.erase(it);
    }
}

NodeInsertResult Graph::addNode(Node *node) {
    if (this->nodes.find(node) == this->nodes.end()) {
        Node *copiedNode = new Node(node);
        return this->nodes.insert(copiedNode);
    }

    return this->nodes.insert(node);
}

EdgeInsertResult Graph::insertEdge(Edge *edge) {
    if (this->edges.find(edge) == this->edges.end()) {
        Edge *copied = new Edge(edge);
        return this->edges.insert(copied);
    }

    return this->edges.insert(edge);
}

void Graph::addEdge(Node *from, Node *to, const std::string &label) {
    // Make sure we're inserting something:
    assert(to != NULL);
    assert(from != NULL);

    // Make sure both nodes are in the graph:
    NodeInsertResult from_instd_res = this->addNode(from);
    NodeInsertResult to_instd_res = this->addNode(to);

    // Get the actual nodes out of the unordered_set:
    // Fucking C++, look at this:
    Node *from_instd_nd = *(std::get<0>(from_instd_res));
    Node *to_instd_nd = *(std::get<0>(to_instd_res));

    // Create a new edge:
    Edge newEdge(label, from_instd_nd, to_instd_nd);
    EdgeInsertResult edge_instd_res = this->insertEdge(&newEdge);

    // Get the actual edge from the unordered_set:
    Edge *edge_instd = *(std::get<0>(edge_instd_res));

    // Add the newly created edge to both Nodes:
    from_instd_nd->addEdge(edge_instd);
    to_instd_nd->addEdge(edge_instd);

    // If we didn't actually insert them, delete them:
    if (!std::get<1>(edge_instd_res)) {
        //std::cout << "Duplicate edge.\n";
        //delete newEdge;
    }
}

const size_t Graph::getNodeCount() {
    return this->nodes.size();
};

const size_t Graph::getEdgeCount() {
    return this->edges.size();
};

void Graph::printNodes() const {
    for (auto it = nodes.begin(); it != nodes.end(); it++) {
        Node *node = *it;
        std::cout << (*node) << "\n";
    }
}

void Graph::printEdges() const {
    for (auto it = edges.begin(); it != edges.end(); it++) {
        Edge *edge = *it;
        std::cout << (*edge) << "\n";
    }
}
