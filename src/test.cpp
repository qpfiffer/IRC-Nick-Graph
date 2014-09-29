#include <cassert>

#include "tst_set.h"
// Simple tests.

int test_can_use_tst_tree() {
    TST::set<int> integer_set;

    int val = 1;
    assert(integer_set.empty());
    assert(integer_set.insert("test", val));
    assert(!integer_set.empty());
    int *returned = integer_set.get("test");
    assert(*returned == val);
    return 0;
}

int main(int argc, char *argv[]) {
    int ret = 0;
    ret &= test_can_use_tst_tree();
    assert(ret == 0);

    return ret;
}
