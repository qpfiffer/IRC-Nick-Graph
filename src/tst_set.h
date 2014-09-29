#pragma once
#include <string>

namespace TST {
    template<typename T>
    class set {
        public:
            set<t>(): root(nullptr), node_count(0) {}
            // Inserts a new value into the tree with key *key*.
            // Returns whether or not the value was actually inserted.
            bool insert(const std::string &key, T new_value) {
                bool inserted = false;
                char iterable_str[key.size()] = key.c_str();

                if(!root) {
                    root = new tst_node(iterable_str[0]);
                }

                for(unsigned int i = 0; i < key.size(); i++) {
                }

                return inserted;
            }

            bool find(const std::string key) const {
                return false;
            }

            bool empty() const {
                return (node_count > 0);
            }
        private:
            struct tst_node {
                tst_node(char c):
                    lokid(nullptr), eqkid(nullptr), hikid(nullptr),
                    node_char(c), is_value(false) {}

                tst_node(char c, T value):
                    lokid(nullptr), eqkid(nullptr), hikid(nullptr),
                    node_char(c), is_value(true), value(value) {}

                tst_node(tst_node &other):
                    lokid(other.lokid), eqkid(other.eqkid), hikid(other.hikid),
                    node_char(other.node_char), is_value(other.is_value) {}

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
