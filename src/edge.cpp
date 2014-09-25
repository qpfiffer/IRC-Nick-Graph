#include "node.h"
#include "edge.h"
using namespace FuckNamespaces;

Edge::Edge(): val(NULL), from(NULL), to(NULL) {
}

Edge::Edge(const Edge *other):
    val(other->getVal()), from(other->getFrom()), to(other->getTo())
{
}

Edge::Edge(const std::string val, const Node *from, const Node *to):
    val(val), from(from), to(to) {
}

Edge::~Edge() {
}

std::string Edge::getVal() const {
    return this->val;
}

const Node *Edge::getFrom() const {
    return this->from;
}

const Node *Edge::getTo() const {
    return this->to;
}

bool Edge::operator==(const Edge &other) const {
    std::stringstream my_stream;
    my_stream << *this;
    std::string my_str = my_stream.str();

    std::stringstream other_stream;
    other_stream << other;
    std::string other_str = other_stream.str();

    return my_str == other_str;
}

bool Edge::operator==(const Edge *other) const {
    return *this == *other;
}

bool EdgeEqualTo::operator()(const Edge *x, const Edge *y) const {
    return *x == *y;
}

std::ostream& FuckNamespaces::operator<<(std::ostream& os, const Edge& edge) {
    const Node from = (*edge.getFrom());
    const Node to = (*edge.getTo());
    return os << from << " " << edge.getVal() << " " << to << "\n";
}

std::ostream& FuckNamespaces::operator<<(std::ostream& os, const Edge *edge) {
    return os << *edge;
}
