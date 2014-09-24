#include "nick_normalize.h"
using namespace FuckNamespaces;

#define JOINED_OFFSET 24
#define KNOWN_AS_OFFSET 23

Graph::~Graph() {
    /*
    while (!nodes.empty()) {
        auto it = nodes.begin();
        FuckNamespaces::Node *node = *it;
        delete node;
    }

    while (!edges.empty()) {
        auto it = edges.begin();
        FuckNamespaces::Edge *edge = *it;
        delete edge;
    }
    */
}

void Node::printAliases() const {
    for (auto it = edges.begin(); it != edges.end(); it++) {
        const Edge *edge = *it;
        //if (*this == *edge->getFrom())
        //    std::cout << "* " << *(edge->getTo()) << "\n";
        std::cout << "* " << *edge;
    }
}

NodeInsertResult Graph::addNode(Node *node) {
    return this->nodes.insert(node);
}

void Graph::addEdge(Node *from, Node *to) {
    // Make sure we're inserting something:
    assert(to != NULL);
    assert(from != NULL);

    // Make sure both nodes are in the graph:
    NodeInsertResult from_instd_res = this->addNode(from);
    NodeInsertResult to_instd_res = this->addNode(to);

    // Get the actual nodes out of the unordered_set:
    // Fucking C++, look at this:
    Node *from_instd_nd = *(std::get<0>(from_instd_res));
    Node *to_instd_nd = *(std::get<0>(to_instd_res));

    // Create a new edge:
    Edge *newEdge = new Edge("became", from, to);
    EdgeInsertResult edge_instd_res = this->edges.insert(newEdge);

    // Get the actual edge from the unordered_set:
    Edge *edge_instd = *(std::get<0>(edge_instd_res));

    from_instd_nd->addEdge(edge_instd);
    to_instd_nd->addEdge(edge_instd);

    // If we didn't actually insert them, delete them:
    if (std::get<1>(edge_instd_res)) {
        //std::cout << "Duplicate edge.\n";
        //delete newEdge;
    }

    if (std::get<1>(from_instd_res)) {
        //delete from_instd_nd;
    }

    if (std::get<1>(to_instd_res)) {
        //delete to_instd_nd;
    }
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
        FuckNamespaces::Node *node = *it;
        std::cout << (*node) << "\n";
    }
}

void Graph::printAliases() {
    for (auto it = nodes.begin(); it != nodes.end(); it++) {
        FuckNamespaces::Node *node = *it;
        if (node->getEdgeCount() > 0) {
            printf("%s has the following %zu aliases:\n",
                    node->getName().c_str(),
                    node->getEdgeCount());
            node->printAliases();
        } else {
            //printf("%s has no aliases.\n", node->getName().c_str());
        }
    }
}

bool FuckNamespaces::EdgeEqualTo::operator()(const Edge *x, const Edge *y) const {
    std::stringstream lhs;
    lhs << *x;

    std::stringstream rhs;
    rhs << *y;

    const char *rhs_str, *lhs_str;
    lhs_str = lhs.str().c_str();
    rhs_str = rhs.str().c_str();

    return lhs.str() == rhs.str();
}

std::ostream& FuckNamespaces::operator<<(std::ostream& os, const Edge& edge) {
    const Node from = (*edge.getFrom());
    const Node to = (*edge.getTo());
    return os << from << " " << edge.getVal() << " " << to << "\n";
}

std::ostream& FuckNamespaces::operator<<(std::ostream& os, const Edge *edge) {
    return os << *edge;
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
                if (*it == ' ')
                    break;
                to_graph += *it;
            }

            //printf("Joined: %s\n", to_graph.c_str());
            Node *new_person = new Node(to_graph);
            king->addNode(new_person);
        } else if (known_as != std::string::npos) {
            std::string nick = line_str->substr(KNOWN_AS_OFFSET);
            std::string from_nick, to_nick;

            for (auto it = nick.begin(); it != nick.end(); it++) {
                if (*it == ' ')
                    break;
                from_nick += *it;
            }
            Node *from_person = new Node(from_nick);

            const size_t from_offset = KNOWN_AS_OFFSET + std::strlen(" is now known as ") + from_nick.length();
            std::string to_nick_begin = line_str->substr(from_offset);
            for (auto it = to_nick_begin.begin(); it != to_nick_begin.end(); it++) {
                if (*it != '\n' && *it != ' ')
                    to_nick += *it;
                else
                    break;
            }
            Node *to_person = new Node(to_nick);

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
    madvise(mmapd_log_file, sb.st_size, MADV_SEQUENTIAL | MADV_WILLNEED);
    Graph *king = parse((const unsigned char *)mmapd_log_file, sb.st_size);
    printf("Parsed. Have %zu nodes and %zu edges.\n", king->getNodeCount(), king->getEdgeCount());
    //king->printNodes();
    king->printAliases();

    munmap(mmapd_log_file, sb.st_size);
    close(log_file);
    delete king;

    return 0;
}
