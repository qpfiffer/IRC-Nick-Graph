#include "edge.h"
#include "node.h"
using namespace FuckNamespaces;

Node::Node(const Node *other):
    name(other->getName()), edges(other->getEdges())
{
}

std::string Node::getName() const {
    return name;
}

EdgeSet Node::getEdges() const {
    return this->edges;
}

bool Node::operator==(const Node &other) const {
    return name == other.getName();
}

bool Node::operator==(const Node *other) const {
    return name == other->getName();
}

const size_t Node::getEdgeCount() const {
    return this->edges.size();
}

EdgeInsertResult Node::addEdge(Edge *edge) {
    //std::cout << "Adding edge " << edge << "\n";
    return this->edges.insert(edge);
}

void Node::printAliases() const {
    for (auto it = edges.begin(); it != edges.end(); it++) {
        const Edge *edge = *it;
        if (*this == *edge->getFrom())
            std::cout << "* " << *edge;
        //std::cout << "* " << *edge;
    }
}

std::ostream& FuckNamespaces::operator<<(std::ostream& os, const Node& node) {
    //return os << node.getName() << ", " << node.getEdgeCount();
    return os << node.getName();
}

bool NodeEqualTo::operator() (const Node *x, const Node *y) const {
    return x->getName() == y->getName();
}
