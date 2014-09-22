#pragma once
#include <cstring>
#include <cstdio>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

#include <cassert>
#include <iostream>
#include <sstream>
#include <string>
#include <tuple>
#include <unordered_set>
#include <vector>

// this looks so fucked up with the namespacing because C++.
namespace FuckNamespaces {
    class Node;

    class Edge {
        public:
            Edge(): val(""), from(NULL), to(NULL) {};
            Edge(std::string val, const Node *from, const Node *to):
                val(val), from(from), to(to) {};

            std::string getVal() const {
                return this->val;
            }

            const Node *getFrom() const {
                return this->from;
            }

            const Node *getTo() const {
                return this->to;
            }

            bool operator==(const Edge &other) const;
        private:
            std::string val;
            const Node *from;
            const Node *to;
    };

    std::ostream& operator<<(std::ostream& os, const Edge& edge);
}
namespace std {
    template <> struct hash<FuckNamespaces::Edge> {
        size_t operator()(const FuckNamespaces::Edge &edge) const {
            std::stringstream val;
            val << edge;
            return std::hash<std::string>()(val.str());
        }
    };
}

namespace FuckNamespaces {
    typedef std::pair<std::unordered_set<Edge>::iterator, bool> EdgeInsertResult;

    class Node {
        public:
            Node(std::string name): name(name), edges() {};
            std::string getName() const {
                return this->name;
            };

            bool operator==(const Node &other) const {
                return this->name == other.getName();
            }

            const size_t getEdgeCount() const {
                return this->edges.size();
            }

            EdgeInsertResult addEdge(const Edge &edge) {
                std::cout << "Adding edge " << edge << "\n";
                return this->edges.insert(edge);
            }
        private:
            std::string name;
            std::unordered_set<Edge> edges;
    };

    std::ostream& operator<<(std::ostream& os, const Node& node) {
        return os << node.getName();
    }
}

namespace std {
    template <> struct hash <FuckNamespaces::Node> {
        size_t operator()(const FuckNamespaces::Node &node) const {
            return std::hash<std::string>()(node.getName());
        }
    };
}

namespace FuckNamespaces {
    typedef std::pair<std::unordered_set<Node>::iterator, bool> NodeInsertResult;

    class Graph {
        public:
            NodeInsertResult addNode(const Node &node);
            void addEdge(Node *from, Node *to);
            void printNodes();
            void printAliases();
            const size_t getNodeCount();
            const size_t getEdgeCount();
        private:
            std::unordered_set<Node> nodes;
            std::unordered_set<Edge> edges;
    };

    typedef std::tuple<std::string, int> StringToInt;
}

