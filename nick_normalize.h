#pragma once
#include <cstdio>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

#include <unordered_map>
#include <unordered_set>
#include <string>
#include <tuple>

class Edge;

class Node {
    private:
        std::unordered_set<Edge> edges;
};

class Edge {
    private:
        std::unordered_set<Node> nodes;
};

class Graph {
    private:
        std::unordered_set<Node> nodes;
};

typedef std::tuple<std::string, int> StringToInt;
