#include "common.h"
#include "edge.h"
#include "node.h"
using namespace std;

size_t hash<FuckNamespaces::Edge *>::operator()(const FuckNamespaces::Edge *edge) const {
    std::stringstream val;
    val << *edge;
    return std::hash<std::string>()(val.str());
}

size_t hash<FuckNamespaces::Node *>::operator()(const FuckNamespaces::Node *node) const {
    std::string name = node->getName();
    assert(name.size() > 0);
    size_t hash = std::hash<std::string>()(name);
    return hash;
}
