#pragma once
#include <cstring>
#include <cstdio>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

#include <unordered_map>
#include <unordered_set>
#include <string>
#include <tuple>

// this looks so fucked up with the namespacing because C++.
namespace FuckNamespaces {
    class Node;

    class Edge {
        public:
            Edge(): val(""), from(NULL), to(NULL) {};
            Edge(std::string val, Node *from, Node *to):
                val(val), from(from), to(to) {};

            std::string getVal() const {
                return this->val;
            };

            bool operator==(const Edge &other) {
                return this->val == other.getVal();
            }
        private:
            std::string val;
            Node *from, *to;
    };
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
            };
        private:
            std::string name;
            std::unordered_set<Edge> edges;
    };
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
            const size_t getNodeCount();
        private:
            std::unordered_set<Node> nodes;
    };

    typedef std::tuple<std::string, int> StringToInt;
}

