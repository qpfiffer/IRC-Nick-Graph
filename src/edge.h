#pragma once
#include "common.h"

// this looks so fucked up with the namespacing because C++.
namespace FuckNamespaces {
    class Node;

    class Edge {
        public:
            Edge();
            Edge(const Edge *other);
            Edge(const std::string val, const Node *from, const Node *to);
            ~Edge();

            std::string getVal() const;
            const Node *getFrom() const;
            const Node *getTo() const;

            bool operator==(const Edge &other) const;
            bool operator==(const Edge *other) const;
        private:
            std::string val;
            const Node *from;
            const Node *to;
    };

    std::ostream& operator<<(std::ostream& os, const Edge &edge);
    std::ostream& operator<<(std::ostream& os, const Edge *edge);
}
