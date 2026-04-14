#define BOOST_TEST_MODULE BTreeTests
#define BOOST_TEST_DYN_LINK
#include "fat_tree.hpp"
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(test_minimum_logic)
{
    stuff::BTree<int, 3> root;
    stuff::BTree<int, 3> left_child;

    for (int i = 0; i < 4; ++i)
        root.children[i] = nullptr;
    for (int i = 0; i < 4; ++i)
        left_child.children[i] = nullptr;

    left_child.val[0] = 5;
    left_child.parent = &root;
    root.children[0] = &left_child;
    root.val[0] = 10;

    auto it = stuff::minimum(&root);

    BOOST_CHECK_EQUAL(it.current, &left_child);
    BOOST_CHECK_EQUAL(it.s, 0);
}

BOOST_AUTO_TEST_CASE(test_maximum_logic)
{
    stuff::BTree<int, 3> root = {};
    stuff::BTree<int, 3> right_child = {};

    root.numKeys = 1;
    root.val[0] = 10;
    root.children[3] = &right_child;

    right_child.parent = &root;
    right_child.numKeys = 3;
    right_child.val[2] = 99;

    auto it = stuff::maximum(&root);

    BOOST_CHECK_EQUAL(it.current, &right_child);
    BOOST_CHECK_EQUAL(it.s, 2);
}

BOOST_AUTO_TEST_CASE(test_null_root)
{
    auto it = stuff::minimum<int, 3>(nullptr);
    BOOST_CHECK(it.current == nullptr);
}

BOOST_AUTO_TEST_CASE(test_get_value)
{
    stuff::BTree<int, 3> node = {};
    node.val[1] = 555;
    node.numKeys = 2;

    stuff::BTreeIt<int, 3> it(1, &node);

    BOOST_CHECK_EQUAL(stuff::getValue(it), 555);
}
