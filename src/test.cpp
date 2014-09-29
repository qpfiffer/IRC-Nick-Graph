#include <cassert>

#include "tst_set.h"
// Simple tests.

int test_can_use_tst_tree() {
    TST::map<int> integer_map;

    assert(integer_map.empty());
    assert(integer_map.insert("test", 1));
    return 0;
}

int main(int argc, char *argv[]) {
    int ret = 0;
    ret &= test_can_use_tst_tree();
    assert(ret == 0);

    return ret;
}
