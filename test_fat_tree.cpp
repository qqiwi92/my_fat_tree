#define BOOST_TEST_MODULE BTreeTests
#define BOOST_TEST_DYN_LINK
#include "fat_tree.hpp"
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(test_minimum_logic)
{
    BTree<int, 3> root;
    BTree<int, 3> left_child;

    for (int i = 0; i < 4; ++i)
        root.children[i] = nullptr;
    for (int i = 0; i < 4; ++i)
        left_child.children[i] = nullptr;

    left_child.val[0] = 5;
    left_child.parent = &root;
    root.children[0] = &left_child;
    root.val[0] = 10;

    auto it = minimum(&root);

    BOOST_CHECK_EQUAL(it.current, &left_child);
    BOOST_CHECK_EQUAL(it.s, 0);
}

BOOST_AUTO_TEST_CASE(test_maximum_logic)
{
    BTree<int, 3> root = {};
    BTree<int, 3> right_child = {};

    root.numKeys = 1;
    root.val[0] = 10;
    root.children[3] = &right_child;

    right_child.parent = &root;
    right_child.numKeys = 3;
    right_child.val[2] = 99;

    auto it = maximum(&root);

    BOOST_CHECK_EQUAL(it.current, &right_child);
    BOOST_CHECK_EQUAL(it.s, 2);
}

BOOST_AUTO_TEST_CASE(test_null_root)
{
    auto it = minimum<int, 3>(nullptr);
    BOOST_CHECK(it.current == nullptr);
}

BOOST_AUTO_TEST_CASE(test_get_getValue)
{
    BTree<int, 3> node = {};
    node.val[1] = 555;
    node.numKeys = 2;

    BTreeIt<int, 3> it(1, &node);

    BOOST_CHECK_EQUAL(value(it), 555);
}


BOOST_AUTO_TEST_CASE(test_next_within_node)
{
    BTree<int, 3> node = {};
    node.numKeys = 2;
    node.val[0] = 10;
    node.val[1] = 20;
    for(int i=0; i<4; ++i) node.children[i] = nullptr;

    BTreeIt<int, 3> it(0, &node);
    auto next_it = next(it);

    BOOST_CHECK_EQUAL(next_it.current, &node);
    BOOST_CHECK_EQUAL(next_it.s, 1);
}

BOOST_AUTO_TEST_CASE(test_next_descend_to_child)
{
    BTree<int, 3> root = {};
    BTree<int, 3> right_child = {};

    root.numKeys = 1;
    root.val[0] = 10;
    root.children[1] = &right_child;

    right_child.parent = &root;
    right_child.numKeys = 1;
    right_child.val[0] = 15;
    for(int i=0; i<4; ++i) right_child.children[i] = nullptr;

    BTreeIt<int, 3> it(0, &root);
    auto next_it = next(it);

    BOOST_CHECK_EQUAL(next_it.current, &right_child);
    BOOST_CHECK_EQUAL(next_it.s, 0);
    BOOST_CHECK_EQUAL(value(next_it), 15);
}

BOOST_AUTO_TEST_CASE(test_next_ascend_to_parent)
{
    BTree<int, 3> root = {};
    BTree<int, 3> left_child = {};

    root.numKeys = 1;
    root.val[0] = 100;
    root.children[0] = &left_child;

    left_child.parent = &root;
    left_child.numKeys = 1;
    left_child.val[0] = 50;
    for(int i=0; i<4; ++i) left_child.children[i] = nullptr;

    BTreeIt<int, 3> it(0, &left_child);
    auto next_it = next(it);

    BOOST_CHECK_EQUAL(next_it.current, &root);
    BOOST_CHECK_EQUAL(next_it.s, 0);
    BOOST_CHECK_EQUAL(value(next_it), 100);
}