#include "nick_normalize.h"
using namespace FuckNamespaces;

//bool Edge::operator==(const Edge &other) {
//    return this->val == other.getVal();
//}

StringToInt read_line(const char *buf, const unsigned int offset) {
    // Read until a null or newline char
    std::string to_return;
    int read = 0;
    while (true) {
        char c = '\0';
        c = buf[read + offset];
        to_return.append(&c);
        read++;
        if (c == '\0' || c == '\n')
            break;
    }

    return std::make_tuple(to_return, read);
}

Graph *parse(const char *mmapd_log_file, const size_t length) {
    unsigned int i = 0;
    unsigned int total_read = 0;
    Graph *king = new Graph();

    while (total_read < length) {
        StringToInt line = read_line(mmapd_log_file, total_read);
        total_read += std::get<1>(line);

        std::string *line_str = &std::get<0>(line);
        if (line_str->find(" has joined ") != std::string::npos ||
            line_str->find(" is now known as ") != std::string::npos) {
            printf("Got a hit with: %s", line_str->c_str());
        }
    }

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
    Graph *king = parse((const char *)mmapd_log_file, sb.st_size);

    munmap(mmapd_log_file, sb.st_size);
    close(log_file);
    delete king;

    return 0;
}
