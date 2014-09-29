#include <cassert>

#include "tst_set.h"
// Simple tests.

int test_can_use_tst_tree() {
    TST::set<int> integer_set;

    assert(integer_set.empty());
    assert(integer_set.insert("test", 1));
    assert(!integer_set.empty());
    return 0;
}

int main(int argc, char *argv[]) {
    int ret = 0;
    ret &= test_can_use_tst_tree();
    assert(ret == 0);

    return ret;
}
