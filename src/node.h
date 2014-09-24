#pragma once
#include "common.h"

namespace FuckNamespaces {
    class Edge;
    class Node {
        public:
            Node(const std::string name): name(name), edges() {};

            std::string getName() const;
            bool operator==(const Node &other) const;
            bool operator==(const Node *other) const;

            const size_t getEdgeCount() const;

            void printAliases() const;

            EdgeInsertResult addEdge(Edge *edge);
        private:
            std::string name;
            EdgeSet edges;
    };

    std::ostream& operator<<(std::ostream& os, const Node& node);
}
