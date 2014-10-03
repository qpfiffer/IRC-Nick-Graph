#pragma once
#include <cassert>
#include <cstring>

#include <iterator>
#include <string>

namespace TST {
    template<typename T>
    class map {
        public:
            map(): root(nullptr), node_count(0) {}
            // Inserts a new value into the tree with key *key*.
            // Returns whether or not the value was actually inserted.
            bool insert(const std::string &key, T new_value) {
                assert(new_value != nullptr);
                return _insert(this->root, key, new_value);
            }

            T* get(const std::string &key) const {
                return _get(this->root, key);
            }

            T *begin() {
                return &this->root;
            }

            const unsigned int count() const {
                return this->node_count;
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

            T* _get(tst_node *current_node, const std::string &key) const {
                const char current_char = key[0];

                if (current_node == nullptr)
                    return nullptr;

                if (current_char < current_node->node_char) {
                    return _get(current_node->lokid, key);
                } else if (current_char == current_node->node_char) {
                    if (key.size() > 1) {
                        return _get(current_node->eqkid, key.substr(1, key.size()));
                    } else {
                        if (!current_node->is_value)
                            return nullptr;
                        return &current_node->value;
                    }
                } else {
                    return _get(current_node->hikid, key);
                }
            }

            bool _insert(tst_node*& current_node,
                         const std::string &key, T val) {
                const char current_char = key[0];

                if (current_node == nullptr) {
                    current_node = new tst_node(current_char);
                }

                if (current_char < current_node->node_char) {
                    return _insert(current_node->lokid, key, val);
                } else if (current_char == current_node->node_char) {
                    if (key.size() > 1) {
                        return _insert(current_node->eqkid,
                                key.substr(1, key.size()), val);
                    } else {
                        if (current_node->is_value) // Duplicate?
                            return false;
                        current_node->is_value = true;
                        current_node->value = val;
                        this->node_count++;
                        return true;
                    }
                } else {
                    return _insert(current_node->hikid, key, val);
                }
            }

            tst_node *root;
            unsigned int node_count;
    };
}
