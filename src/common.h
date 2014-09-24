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

#define JOINED_OFFSET 24
#define KNOWN_AS_OFFSET 23

namespace FuckNamespaces {
    class Node;
    class Edge;
}

namespace std {
    template <> struct hash<FuckNamespaces::Edge> {
        size_t operator()(const FuckNamespaces::Edge &edge) const;
    };

    template <> struct hash<FuckNamespaces::Node *> {
        size_t operator()(const FuckNamespaces::Node *node) const;
    };
}

namespace FuckNamespaces {
    typedef std::pair<std::unordered_set<Edge *>::iterator, bool> EdgeInsertResult;
    typedef std::pair<std::unordered_set<Node *>::iterator, bool> NodeInsertResult;

    typedef struct {
        bool operator() (const Node *x, const Node *y) const;
    } NodeEqualTo;


    typedef struct {
        bool operator() (const Edge *x, const Edge *y) const;
    } EdgeEqualTo;

    typedef std::unordered_set<Edge *, std::unordered_set<Edge *>::hasher, EdgeEqualTo> EdgeSet;
    typedef std::unordered_set<Node *, std::unordered_set<Node *>::hasher, NodeEqualTo> NodeSet;
}
