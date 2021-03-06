#pragma once
#include "common.h"

namespace FuckNamespaces {
    class Edge;
    class Node {
        public:
            Node(const Node *other);
            Node(const std::string name): name(name), edges() {};

            std::string getName() const;
            EdgeSet getEdges() const;
            bool operator==(const Node &other) const;
            bool operator==(const Node *other) const;

            const size_t getEdgeCount() const;

            void printAliases() const;

            EdgeInsertResult addEdge(Edge *edge);
            const std::string nodeID() const;
        private:
            std::string name;
            EdgeSet edges;
    };

    std::ostream& operator<<(std::ostream& os, const Node& node);
}
