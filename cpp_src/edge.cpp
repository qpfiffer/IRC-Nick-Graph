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

const std::string Edge::toString() const {
    const std::string from_name = from->getName();
    const std::string to_name = to->getName();
    const std::string my_val = this->val;

    // The 4 here is two spaces, a \n and a null-terminator.
    const size_t buf_size = from_name.size() + my_val.size() + to_name.size() + 4;

    char buf[buf_size];
    assert(memset(buf, '\0', buf_size) == buf);

    const int ret = snprintf(buf, buf_size, "%s %s %s\n",
            from_name.c_str(), my_val.c_str(), to_name.c_str());
    assert(ret > 0);

    return std::string(buf);
}

bool Edge::operator==(const Edge &other) const {
    std::string my_str = this->toString();
    std::string other_str = other.toString();

    return my_str == other_str;
}

bool Edge::operator==(const Edge *other) const {
    return *this == *other;
}

bool EdgeEqualTo::operator()(const Edge *x, const Edge *y) const {
    return *x == *y;
}

std::ostream& FuckNamespaces::operator<<(std::ostream& os, const Edge& edge) {
    return os << edge.toString();
}

std::ostream& FuckNamespaces::operator<<(std::ostream& os, const Edge *edge) {
    return os << *edge;
}
