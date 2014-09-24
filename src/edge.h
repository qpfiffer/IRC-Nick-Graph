#pragma once
#include "common.h"

// this looks so fucked up with the namespacing because C++.
namespace FuckNamespaces {
    class Node;

    class Edge {
        public:
            Edge(): val(NULL), from(NULL), to(NULL) {};
            Edge(const std::string &val, const Node *from, const Node *to):
                val(NULL), from(from), to(to) {
                this->val = new std::string(val);
            };
            ~Edge() {
                delete this->val;
            }

            std::string getVal() const {
                return *this->val;
            }

            const Node *getFrom() const {
                return this->from;
            }

            const Node *getTo() const {
                return this->to;
            }

            bool operator==(const Edge &other) const;
        private:
            std::string *val;
            const Node *from;
            const Node *to;
    };

    std::ostream& operator<<(std::ostream& os, const Edge &edge);
    std::ostream& operator<<(std::ostream& os, const Edge *edge);
}
