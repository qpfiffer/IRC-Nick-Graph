#pragma once
#include "common.h"

namespace FuckNamespaces {
    class Node;

    class Graph {
        public:
            ~Graph();
            NodeInsertResult addNode(Node *node);
            void addEdge(Node *from, Node *to, const std::string &label);
            void printEdges() const;
            void printNodes() const;
            void printAliases() const;
            void printSigmaGraphJS() const;
            const size_t getNodeCount();
            const size_t getEdgeCount();
        private:
            EdgeInsertResult insertEdge(Edge *edge);
            NodeSet nodes;
            EdgeSet edges;
    };
}
