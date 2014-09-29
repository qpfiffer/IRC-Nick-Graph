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

#include "tst_set.h"


namespace FuckNamespaces {
    // Forward declarations because C++.
    class Node;
    class Edge;
}

namespace std {
    // Hashing function declarations for Edge and Node
    template <> struct hash<FuckNamespaces::Edge *> {
        size_t operator()(const FuckNamespaces::Edge *edge) const;
    };

    template <> struct hash<FuckNamespaces::Node *> {
        size_t operator()(const FuckNamespaces::Node *node) const;
    };
}

namespace FuckNamespaces {
    // Some helper typedefs because C++ LOL
    typedef std::pair<std::unordered_set<Edge *>::iterator, bool> EdgeInsertResult;
    typedef std::pair<std::unordered_set<Node *>::iterator, bool> NodeInsertResult;

    // Comparing pointers in unordered_set by default just checks to see if they're
    // the same address so we define custom functions that check the toString() value.
    // (actually checks << but close enough)
    typedef struct {
        bool operator() (const Edge *x, const Edge *y) const;
    } EdgeEqualTo;

    typedef struct {
        bool operator() (const Node *x, const Node *y) const;
    } NodeEqualTo;

    // Set of edges, set of nodes.
    typedef std::unordered_set<Edge *, std::unordered_set<Edge *>::hasher, EdgeEqualTo> EdgeSet;
    typedef std::unordered_set<Node *, std::unordered_set<Node *>::hasher, NodeEqualTo> NodeSet;
}
