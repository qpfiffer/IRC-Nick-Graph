#include <algorithm>

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
    NodeInsertResult result = this->nodes.insert(node);
    Node *node_instd = *(std::get<0>(result));
    bool inserted = std::get<1>(result);

    return result;
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
    Edge *newEdge = new Edge("became", from_instd_nd, to_instd_nd);
    EdgeInsertResult edge_instd_res = this->edges.insert(newEdge);

    // Get the actual edge from the unordered_set:
    Edge *edge_instd = *(std::get<0>(edge_instd_res));

    from_instd_nd->addEdge(edge_instd);

    // If this is a non-directed graph, enable this:
    //to_instd_nd->addEdge(edge_instd);

    // If we didn't actually insert them, delete them:
    if (!std::get<1>(edge_instd_res)) {
        //std::cout << "Duplicate edge.\n";
        delete newEdge;
    }

    if (!std::get<1>(from_instd_res)) {
        //std::cout << "Duplicate node.\n";
        delete from;
    }

    if (!std::get<1>(to_instd_res)) {
        //std::cout << "Duplicate node.\n";
        delete to;
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
        FuckNamespaces::Node *node = *it;
        std::cout << (*node) << "\n";
    }
}

void Graph::printAliases() const {
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

void Graph::printSigmaGraphJS() const {
    std::cout << "{ \"nodes\": [";
    for (auto it = nodes.begin(); it != nodes.end(); it++) {
        Node *node = *it;
        size_t hash = std::hash<Node *>()(node);

        std::string replaced = node->getName();
        std::replace(replaced.begin(), replaced.end(), '\\', ' ');
        std::cout   << "{"
                    << "\"id\": \"n" << hash << "\","
                    << "\"label\": \"" << replaced << "\"";
                    //<< "\"x\": 0, \"y\": 0"
        if (it != nodes.end())
            std::cout << "},";
        else
            std::cout << "}";
    }
    std::cout << "], \"edges\": [ ";
    for (auto it = edges.begin(); it != edges.end(); it++) {
        Edge *edge = *it;
        size_t hash = std::hash<Edge *>()(edge);
        size_t from_hash = std::hash<Node *>()(edge->getFrom());
        size_t to_hash = std::hash<Node *>()(edge->getTo());

        std::cout   << "{"
                    << "\"id\": \"n" << hash << "\","
                    << "\"source\": \"" << from_hash << "\","
                    << "\"target\": \"" << to_hash << "\"";
        if (it != edges.end())
            std::cout << "},";
        else
            std::cout << "}";
    }
    std::cout << "] }";
}
