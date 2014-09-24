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
            Edge(): val(NULL), from(NULL), to(NULL) {};
            Edge(const std::string &val, const Node *from, const Node *to):
                val(NULL), from(from), to(to) {
                this->val = new std::string(val);
            };
            ~Edge() {
                delete this->val;
            }

            std::string getVal() const {
                return *this->val;
            }

            const Node *getFrom() const {
                return this->from;
            }

            const Node *getTo() const {
                return this->to;
            }

            bool operator==(const Edge &other) const;
        private:
            std::string *val;
            const Node *from;
            const Node *to;
    };

    typedef struct {
        bool operator() (const Edge *x, const Edge *y) const {
            std::stringstream lhs;
            lhs << x;

            std::stringstream rhs;
            rhs << y;

            return rhs.str() == lhs.str();
        }
    } EdgeEqualTo;

    typedef std::unordered_set<Edge *, std::unordered_set<Edge *>::hasher, EdgeEqualTo> EdgeSet;

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
    typedef std::pair<std::unordered_set<Edge *>::iterator, bool> EdgeInsertResult;

    class Node {
        public:
            Node(const std::string &name): name(NULL), edges() {
                assert(name.size() > 0);
                this->name = new std::string(name.c_str());
            };
            ~Node() {
                delete this->name;
            }
            std::string getName() const {
                return *this->name;
            };

            bool operator==(const Node &other) const {
                return *this->name == other.getName();
            }

            bool operator==(const Node *other) const {
                return *this->name == other->getName();
            }

            const size_t getEdgeCount() const {
                return this->edges.size();
            }

            EdgeInsertResult addEdge(Edge *edge) {
                std::cout << "Adding edge " << edge << "\n";
                return this->edges.insert(edge);
            }
        private:
            std::string *name;
            EdgeSet edges;
    };

    std::ostream& operator<<(std::ostream& os, const Node& node) {
        return os << node.getName() << ", " << node.getEdgeCount();
    }
}

namespace std {
    template <> struct hash <FuckNamespaces::Node *> {
        size_t operator()(const FuckNamespaces::Node *node) const {
            std::string name = node->getName();
            assert(name.size() > 0);
            size_t hash = std::hash<std::string>()(name);
            return hash;
        }
    };
}

namespace FuckNamespaces {
    typedef struct {
        bool operator() (const Node *x, const Node *y) const {
            return x->getName() == y->getName();
        }
    } NodeEqualTo;

    typedef std::unordered_set<Node *, std::unordered_set<Node *>::hasher, NodeEqualTo> NodeSet;

    typedef std::pair<std::unordered_set<Node *>::iterator, bool> NodeInsertResult;

    class Graph {
        public:
            ~Graph();
            NodeInsertResult addNode(Node *node);
            void addEdge(Node *from, Node *to);
            void printNodes();
            void printAliases();
            const size_t getNodeCount();
            const size_t getEdgeCount();
        private:
            NodeSet nodes;
            EdgeSet edges;
    };

    typedef std::tuple<std::string, int> StringToInt;
}

