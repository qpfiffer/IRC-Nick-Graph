#include <cassert>

#include "tst_map.h"
// Simple tests.

int test_can_use_tst_tree() {
    TST::map<int> integer_map;

    int val = 1;
    assert(integer_map.empty());
    assert(integer_map.insert("test", val));
    assert(!integer_map.empty());

    int *returned = integer_map.get("test");
    assert(*returned == val);

    assert(integer_map.get("test2") == nullptr);
    assert(integer_map.get("alkjsd") == nullptr);
    assert(integer_map.get("t") == nullptr);

    int new_val = 129380830;
    assert(integer_map.insert("abcdefg", new_val));

    int new_val_again = 1928392;
    assert(integer_map.insert("test2", new_val_again));

    returned = integer_map.get("test2");
    assert(*returned == new_val_again);

    return 0;
}

int main(int argc, char *argv[]) {
    int ret = 0;
    ret &= test_can_use_tst_tree();
    assert(ret == 0);

    return ret;
}
