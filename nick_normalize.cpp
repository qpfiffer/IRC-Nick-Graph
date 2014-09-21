#include <cstdio>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

#include <unordered_map>
#include <unordered_set>

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

int parse(const char *mmapd_log_file) {

    return 0;
}

int main(int argc, char *argv[]) {
    if (argc < 2)
        return 1;

    int log_file = open(argv[1], O_RDONLY);
    printf("Opening %s\n", argv[1]);
    if (log_file < 0) {
        printf("Could not open log file.\n");
        return 1;
    }

    struct stat sb = {0};
    if (fstat(log_file, &sb) == -1) {
        printf("Could not get filesize.");
        return -1;
    }

    void *mmapd_log_file = mmap(NULL, sb.st_size, PROT_READ, MAP_SHARED, log_file, 0);
    parse((const char *)mmapd_log_file);

    munmap(mmapd_log_file, sb.st_size);
    close(log_file);

    return 0;
}
