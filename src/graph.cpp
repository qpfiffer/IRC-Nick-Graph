#include "edge.h"
#include "node.h"
#include "graph.h"
using namespace FuckNamespaces;

Graph::~Graph() {
    /*
    while (!nodes.empty()) {
        auto it = nodes.begin();
        FuckNamespaces::Node *node = *it;
        delete node;
    }

    while (!edges.empty()) {
        auto it = edges.begin();
        FuckNamespaces::Edge *edge = *it;
        delete edge;
    }
    */
}

NodeInsertResult Graph::addNode(Node *node) {
    return this->nodes.insert(node);
}

void Graph::addEdge(Node *from, Node *to) {
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
    Edge *newEdge = new Edge("became", from, to);
    EdgeInsertResult edge_instd_res = this->edges.insert(newEdge);

    // Get the actual edge from the unordered_set:
    Edge *edge_instd = *(std::get<0>(edge_instd_res));

    from_instd_nd->addEdge(edge_instd);
    // If this is a non-directed graph, enable this:
    //to_instd_nd->addEdge(edge_instd);

    // If we didn't actually insert them, delete them:
    if (std::get<1>(edge_instd_res)) {
        //std::cout << "Duplicate edge.\n";
        //delete newEdge;
    }

    if (std::get<1>(from_instd_res)) {
        //delete from_instd_nd;
    }

    if (std::get<1>(to_instd_res)) {
        //delete to_instd_nd;
    }
}

const size_t Graph::getNodeCount() {
    return this->nodes.size();
};

const size_t Graph::getEdgeCount() {
    return this->edges.size();
};

void Graph::printNodes() {
    for (auto it = nodes.begin(); it != nodes.end(); it++) {
        FuckNamespaces::Node *node = *it;
        std::cout << (*node) << "\n";
    }
}

void Graph::printAliases() {
    for (auto it = nodes.begin(); it != nodes.end(); it++) {
        FuckNamespaces::Node *node = *it;
        if (node->getEdgeCount() > 0) {
            printf("%s has the following %zu aliases:\n",
                    node->getName().c_str(),
                    node->getEdgeCount());
            node->printAliases();
        } else {
            //printf("%s has no aliases.\n", node->getName().c_str());
        }
    }
}
