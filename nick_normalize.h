#pragma once
#include <cstring>
#include <cstdio>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

#include <unordered_map>
#include <unordered_set>
#include <sstream>
#include <string>
#include <tuple>

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

    std::ostream& operator<<(std::ostream& os, const Edge& edge) {
        const Node *from = edge.getFrom();
        const Node *to = edge.getTo();
        return os << from << edge.getVal() << to;
    }
}
namespace std {
    template <> struct hash<FuckNamespaces::Edge> {
        size_t operator()(const FuckNamespaces::Edge &edge) const {
            return std::hash<std::string>()(edge.getVal());
        }
    };
}

namespace FuckNamespaces {
    class Node {
        public:
            Node(std::string name): name(name), edges() {};
            std::string getName() const {
                return this->name;
            };

            bool operator==(const Node &other) const {
                return this->name == other.getName();
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

    class Graph {
        public:
            void addNode(const Node &node);
            void addEdge(const Node &from, const Node &to);
            void printNodes();
            const size_t getNodeCount();
            const size_t getEdgeCount();
        private:
            std::unordered_set<Node> nodes;
            std::unordered_set<Edge> edges;
    };

    typedef std::tuple<std::string, int> StringToInt;
}

