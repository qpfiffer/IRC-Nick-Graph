#pragma once
#include <cassert>
#include <cstring>
#include <string>

namespace TST {
    template<typename T>
    class set {
        public:
            set(): root(nullptr), node_count(0) {}
            // Inserts a new value into the tree with key *key*.
            // Returns whether or not the value was actually inserted.
            bool insert(const std::string &key, T new_value) {
                const char *iterable_str = key.c_str();

                if(!root) {
                    root = new tst_node(iterable_str[0]);
                }

                // Wish we had proper recursion...
                tst_node *current_node = root;
                for(unsigned int i = 0; i < key.size(); i++) {
                    char current_char = iterable_str[i];
                    if (current_char < current_node->node_char) {
                        if (current_node->lokid == nullptr) {
                            tst_node *new_node = new tst_node(iterable_str[0]);
                            current_node->lokid = new_node;
                        }
                        current_node = current_node->lokid;
                    } else if (current_char == current_node->node_char) {
                        if (current_node->eqkid == nullptr) {
                            tst_node *new_node = new tst_node(iterable_str[0]);
                            current_node->eqkid = new_node;
                        }

                        // Is this the last area?
                        bool is_last = i == key.size() - 1;
                        if (!is_last) {
                            current_node = current_node->eqkid;
                        } else {
                            if(current_node->is_value)
                                return false;

                            current_node->is_value = true;
                            current_node->value = new_value;

                            this->node_count++;
                            return true;
                        }
                    } else { // current_char > current_node->node_char
                        if (current_node->hikid == nullptr) {
                            tst_node *new_node = new tst_node(iterable_str[0]);
                            current_node->hikid = new_node;
                        }
                        current_node = current_node->hikid;
                    }
                }

                // Shouldn't be able to get here.
                return false;
            }

            T* get(const std::string key) const {
                if (!root)
                    return nullptr;

                tst_node *node = this->root;
                const char *key_str = key.c_str();
                for (unsigned int i = 0; i < key.size(); i++) {
                    if (!node)
                        break;
                    if (key_str[i] < node->node_char) {
                        node = node->lokid;
                    } else if (key_str[i] == node->node_char) {
                        bool is_last = i == key.size() - 1;
                        if (is_last) {
                            if (node->is_value)
                                return &(node->value);
                            return nullptr;
                        } else {
                            node = node->eqkid;
                        }
                    } else {
                        node = node->hikid;
                    }
                }
                return nullptr;
            }

            bool empty() const {
                return node_count == 0;
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
