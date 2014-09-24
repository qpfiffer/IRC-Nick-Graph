#include "edge.h"
#include "node.h"
using namespace FuckNamespaces;

bool NodeEqualTo::operator() (const Node *x, const Node *y) const {
        return x->getName() == y->getName();
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
