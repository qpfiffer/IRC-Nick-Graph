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
    Node *copiedNode = node;
    const std::string node_name = node->getName();

    if (nodes.find(node) == nodes.end()) {
        if (node_refs.get(node_name) != nullptr) {
            const bool mismatched = node_refs.get(node_name);
        }
    }

    if (node_refs.get(node_name) == nullptr) {
        copiedNode = new Node(node);
        if (!node_refs.insert(node_name, copiedNode))
            node_refs.get(node_name);
    }

    return this->nodes.insert(copiedNode);
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

void Graph::printCSV() const {
    int nodes_fd = open("/tmp/nodes.csv", O_RDWR | O_CREAT, S_IWUSR | S_IRUSR);
    assert(nodes_fd > 0);
    write(nodes_fd, "id,name\n", strlen("id,name\n"));
    for (auto it = nodes.begin(); it != nodes.end(); it++) {
        char words[1024] = {0};
        const Node *node = *it;
        size_t hash = std::hash<Node *>()(node);
        const int num_written = snprintf(words, 1024, "%zu,%s\n", hash, node->getName().c_str());
        assert(num_written > 0);

        const int written = write(nodes_fd, words, num_written);
        assert(written > 0);
    }
    fsync(nodes_fd);
    close(nodes_fd);

    int edges_fd = open("/tmp/edges.csv", O_RDWR | O_CREAT, S_IWUSR | S_IRUSR);
    assert(nodes_fd > 0);
    const char schema_str[] = "source,target,verb\n";
    write(nodes_fd, schema_str, strlen(schema_str));
    for (auto it = edges.begin(); it != edges.end(); it++) {
        char words[1024] = {0};
        const Edge *edge = *it;
        size_t from_hash = std::hash<Node *>()(edge->getFrom());
        size_t to_hash = std::hash<Node *>()(edge->getTo());
        const int num_written = snprintf(words, 1024, "%zu,%zu,%s\n", from_hash, to_hash, edge->getVal().c_str());
        assert(num_written > 0);

        const int written = write(nodes_fd, words, num_written);
        assert(written > 0);
    }
    fsync(edges_fd);
    close(edges_fd);
}

void Graph::printSigmaGraphJS() const {
    std::cout   << "{ \"nodes\": [";
    for (auto it = nodes.begin(); it != nodes.end(); it++) {
        if (it != nodes.begin())
            std::cout << ",";
        Node *node = *it;

        // Get some stuff that we're going to print
        size_t hash = std::hash<Node *>()(node);
        std::string node_id = node->nodeID();
        std::string replaced = node->getName();

        // Replace some stuff for JSON's sake
        std::replace(replaced.begin(), replaced.end(), '\\', ' ');
        std::replace(replaced.begin(), replaced.end(), '\t', ' ');
        std::replace(replaced.begin(), replaced.end(), '"', '\'');

        std::cout   << "{\n"
                    << "    \"id\": \"" << node_id << "\",\n"
                    << "    \"label\": \"" << replaced << "\",\n"
                    << "    \"x\": " << hash % 431 << ",\n"
                    << "    \"y\": " << hash % 467 << ",\n"
                    //<< "    \"size\": " << hash % 25 << "\n"
                    << "    \"size\": 20\n"
                    << "}\n";
    }
    std::cout << "], \"edges\": [ \n";
    for (auto it = edges.begin(); it != edges.end(); it++) {
        if (it != edges.begin())
            std::cout << ",";
        Edge *edge = *it;
        size_t hash = std::hash<Edge *>()(edge);

        std::cout   << "{\n"
                    << "    \"id\": \"e" << hash << "\",\n"
                    << "    \"source\": \"" << edge->getFrom()->nodeID() << "\",\n"
                    << "    \"target\": \"" << edge->getTo()->nodeID() << "\"\n";
        std::cout << "}\n";
    }
    std::cout << "] }";
}
