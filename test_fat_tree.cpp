#define BOOST_TEST_MODULE BTreeTests
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include "fat_tree.hpp" 

BOOST_AUTO_TEST_CASE(test_btree_initialization) {
    stuff::BTree<int, 3> tree ;
    
    BOOST_TEST(sizeof(tree.val) / sizeof(int) == 3);
    }

BOOST_AUTO_TEST_CASE(test_iterator_logic) {
    stuff::BTreeIt<int, 5> it;
    it.s = 0;
    BOOST_CHECK(it.s == 0);
}
