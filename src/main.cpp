#include "common.h"
#include "edge.h"
#include "node.h"
#include "graph.h"
using namespace FuckNamespaces;

// The line read and the number of characters read.
typedef std::tuple<std::string, size_t> StringToSizeT;

// Used for parsing:
#define JOINED_OFFSET 24
#define KNOWN_AS_OFFSET 23

class AliasGraph: public Graph {
    public:
        void printAliases() const {
            for (auto it = nodes.begin(); it != nodes.end(); it++) {
                FuckNamespaces::Node *node = *it;
                if (node->getEdgeCount() > 0) {
                    std::cout   << node->getName() << " has the following "
                                << node->getEdgeCount() << " aliases:\n";
                    node->printAliases();
                }
            }
        }
};

StringToSizeT read_line(const char *buf, const size_t offset) {
    // Read until a null or newline char
    size_t read = 0;
    char c = '\0';

    // Get a pointer to the start position in the array:
    const char *start_buf = buf + offset;

    while (true) {
        c = buf[read + offset];
        read++;
        if (c == '\0' || c == '\n')
            break;
    }
    std::string to_return(start_buf, read);

    return std::make_tuple(to_return, read);
}

AliasGraph *parse(const char *mmapd_log_file, const size_t length) {
    size_t total_read = 0;
    AliasGraph *king = new AliasGraph();

    while (total_read < length) {
        StringToSizeT line = read_line(mmapd_log_file, total_read);
        total_read += std::get<1>(line);

        std::string *line_str = &std::get<0>(line);
        size_t known_as = line_str->find(" is now known as ");
        size_t joined = line_str->find(" has joined ");

        if (joined != std::string::npos) {
            std::string nick = line_str->substr(JOINED_OFFSET);
            std::string to_graph, room_str;

            for (auto it = nick.begin(); it != nick.end(); it++) {
                if (*it == ' ')
                    break;
                to_graph += *it;
            }
            Node new_person(to_graph);

            const size_t room_offset = joined + std::strlen(" has joined ");
            std::string room_offset_begin = line_str->substr(room_offset);
            for (auto it = room_offset_begin.begin(); it != line_str->end(); it++) {
                if (*it != '\n' && *it != ' ')
                    room_str += *it;
                else
                    break;
            }
            Node room(room_str);

            king->addEdge(&new_person, &room, "joined");

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
                if (*it != '\n' && *it != ' ')
                    to_nick += *it;
                else
                    break;
            }
            Node to_person(to_nick);

            if (from_nick.size() <= 0 || to_nick.size() <= 0)
                continue;

            // This will add the nodes to the graph implicitly.
            // STAAAAAAAAAAAAAAAAAAAAATTTTEEEE!
            king->addEdge(&from_person, &to_person, "became");
        }
    }

    return king;
}

void usage(const char *program_name) {
    std::cout   << program_name << " <output_type> <logfile>\n\n"
                << "Where <output_type> is one of the following:\n\n"
                << "\tgephi       - Outputs /tmp/nodes.csv and /tmp/edges.csv for use with the Gephi graph program.\n"
                << "\tsigmajs     - Outputs a JSON encoded graph for use with the sigma.js graphing library.\n"
                << "\taliases     - Simply prints aliases and joins to STDOUT. Filters out non-aliased users.\n"
                << "\tnodes       - Prints all nodes to stdout.\n"
                << "\tedges       - Prints all edges to stdout.\n";
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        usage(argv[0]);
        return 1;
    }

    const std::string option = argv[1];
    const char *logfile = argv[2];

    int log_file = open(logfile, O_RDONLY);
    if (log_file < 0) {
        std::cout << "Could not open log file.\n";
        return 1;
    }

    struct stat sb = {0};
    if (fstat(log_file, &sb) == -1) {
        std::cout << "Could not get filesize.";
        return -1;
    }

    void *mmapd_log_file = mmap(NULL, sb.st_size, PROT_READ, MAP_SHARED, log_file, 0);

    // Parse the log file
    madvise(mmapd_log_file, sb.st_size, MADV_SEQUENTIAL | MADV_WILLNEED);
    AliasGraph *king = parse((const char *)mmapd_log_file, sb.st_size);

    // We're done now
    munmap(mmapd_log_file, sb.st_size);
    close(log_file);

    std::cerr   << "Parsed. Have " << king->getNodeCount() << " nodes and "
                << king->getEdgeCount() << " edges.\n";

    if ("gephi" == option) {
        king->printCSV();
    } else if ("sigmajs" == option) {
        king->printSigmaGraphJS();
    } else if ("aliases" == option) {
        king->printAliases();
    } else if ("nodes" == option) {
        king->printNodes();
    } else if ("edges" == option) {
        king->printEdges();
    }

    delete king;

    return 0;
}
