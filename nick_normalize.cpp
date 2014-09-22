#include "nick_normalize.h"
using namespace FuckNamespaces;

#define JOINED_OFFSET 24
#define KNOWN_AS_OFFSET 23

void Graph::addNode(const Node &node) {
    this->nodes.insert(node);
}

void Graph::addEdge(const Node &from, const Node &to) {
    this->addNode(from);
    this->addNode(to);

    Edge newEdge("became", &from, &to);
    this->edges.insert(newEdge);
}

const size_t Graph::getNodeCount() {
    return this->nodes.size();
};

const size_t Graph::getEdgeCount() {
    return this->edges.size();
};

bool Edge::operator==(const Edge &other) const {
    std::stringstream my_stream;
    my_stream << this;

    std::stringstream other_str;
    other_str << other;

    return my_stream.str() == other_str.str();
}

void Graph::printNodes() {
    for (auto it = nodes.begin(); it != nodes.end(); it++) {
        FuckNamespaces::Node node = *it;
        printf("%s\n", node.getName().c_str());
    }
}

StringToInt read_line(const unsigned char *buf, const unsigned int offset) {
    // Read until a null or newline char
    std::string to_return;
    unsigned int read = 0;
    char c = '\0';
    while (true) {
        c = buf[read + offset];
        to_return += c;
        read++;
        if (c == '\0' || c == '\n')
            break;
    }

    return std::make_tuple(to_return, read);
}

Graph *parse(const unsigned char *mmapd_log_file, const size_t length) {
    unsigned int i = 0;
    unsigned int total_read = 0;
    Graph *king = new Graph();

    while (total_read < length) {
        StringToInt line = read_line(mmapd_log_file, total_read);
        total_read += std::get<1>(line);

        std::string *line_str = &std::get<0>(line);
        size_t known_as = line_str->find(" is now known as ");
        size_t joined = line_str->find(" has joined ");

        if (joined != std::string::npos) {
            std::string nick = line_str->substr(JOINED_OFFSET);
            std::string to_graph;

            for (auto it = nick.begin(); it != nick.end(); it++) {
                to_graph += *it;
                if (*it == ' ')
                    break;
            }

            //printf("Joined: %s\n", to_graph.c_str());
            Node new_person(to_graph);
            king->addNode(new_person);
        } else if (known_as != std::string::npos) {
            std::string nick = line_str->substr(KNOWN_AS_OFFSET);
            std::string from_nick, to_nick;

            for (auto it = nick.begin(); it != nick.end(); it++) {
                if (*it == ' ')
                    break;
                from_nick += *it;
            }
            Node from_person(from_nick);

            const size_t from_offset = KNOWN_AS_OFFSET + std::strlen(" is now known as ") + from_nick.length();
            std::string to_nick_begin = line_str->substr(from_offset);
            for (auto it = to_nick_begin.begin(); it != to_nick_begin.end(); it++) {
                to_nick += *it;
            }
            Node to_person(to_nick);

            // This will add the nodes to the graph implicitly.
            // STAAAAAAAAAAAAAAAAAAAAATTTTEEEE!
            king->addEdge(from_person, to_person);

            //printf("%s turned into %s", from_nick.c_str(), to_nick.c_str());
        }
    }

    return king;
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
    Graph *king = parse((const unsigned char *)mmapd_log_file, sb.st_size);
    printf("Parsed. Have %zu nodes and %zu edges.\n", king->getNodeCount(), king->getEdgeCount());
    //king->printNodes();

    munmap(mmapd_log_file, sb.st_size);
    close(log_file);
    delete king;

    return 0;
}
