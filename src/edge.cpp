#include "node.h"
#include "edge.h"
using namespace FuckNamespaces;

bool Edge::operator==(const Edge &other) const {
    std::stringstream my_stream;
    my_stream << this;

    std::stringstream other_str;
    other_str << other;

    return my_stream.str() == other_str.str();
}

bool EdgeEqualTo::operator()(const Edge *x, const Edge *y) const {
    std::stringstream lhs;
    lhs << *x;
    std::string lhs_string(lhs.str());

    std::stringstream rhs;
    rhs << *y;
    std::string rhs_string(rhs.str());

    const char *lhs_str = lhs_string.c_str();
    const char *rhs_str = rhs_string.c_str();

    bool result = lhs_string == rhs_string;
    return result;
}

std::ostream& FuckNamespaces::operator<<(std::ostream& os, const Edge& edge) {
    const Node from = (*edge.getFrom());
    const Node to = (*edge.getTo());
    return os << from << " " << edge.getVal() << " " << to << "\n";
}

std::ostream& FuckNamespaces::operator<<(std::ostream& os, const Edge *edge) {
    return os << *edge;
}
