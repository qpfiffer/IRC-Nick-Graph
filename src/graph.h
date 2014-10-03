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
            void printSigmaGraphJS() const;
            void printCSV() const;
            const size_t getNodeCount();
            const size_t getEdgeCount();
        protected:
            EdgeInsertResult insertEdge(Edge *edge);

            // Ternary search trees to quickly find nodes/edges. They
            // simply hold pointers to nodes/edges in the set.
            TST::map<Node *> node_refs;
            TST::map<Edge *> edge_refs;

            NodeSet nodes;
            EdgeSet edges;
    };
}
