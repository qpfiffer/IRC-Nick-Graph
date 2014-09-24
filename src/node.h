#pragma once
#include "common.h"

namespace FuckNamespaces {
    class Edge;
    class Node {
        public:
            Node(const std::string name): name(name), edges() {};
            std::string getName() const {
                return name;
            };

            bool operator==(const Node &other) const {
                return name == other.getName();
            }

            bool operator==(const Node *other) const {
                return name == other->getName();
            }

            const size_t getEdgeCount() const {
                return this->edges.size();
            }

            void printAliases() const;

            EdgeInsertResult addEdge(Edge *edge) {
                //std::cout << "Adding edge " << edge << "\n";
                return this->edges.insert(edge);
            }
        private:
            std::string name;
            EdgeSet edges;
    };

    std::ostream& operator<<(std::ostream& os, const Node& node);
}
