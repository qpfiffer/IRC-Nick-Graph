#pragma once
#include <string>

namespace TST {
    template<typename T>
    class map {
        public:
            bool insert(const std::string key, T new_value) {
                this->node_count++;
                return false;
            }

            bool find(const std::string key) const {
                return false;
            }

            bool empty() const {
                return (node_count > 0);
            }
        private:
            struct tst_node {
                tst_node():
                    lokid(nullptr), eqkid(nullptr), hikid(nullptr),
                    node_char('\0'), is_value(false) {};
                tst_node(tst_node &other):
                    lokid(other.lokid), eqkid(other.eqkid), hikid(other.hikid),
                    node_char(other.node_char), is_value(other.is_value) {};

                tst_node *lokid;
                tst_node *eqkid;
                tst_node *hikid;
                char node_char;
                bool is_value;

                T value;
            };

            tst_node *root;
            unsigned int node_count;
    };
}
