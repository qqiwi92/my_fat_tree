#ifndef FATTREE
#define FATTREE

#include <cstddef>

template <class T, size_t K>
struct BTree {
    T val[K];
    BTree<T, K> children[K + 1];
    BTree<T, K>* parent;
};

template <class T, size_t K>
struct BTreeIt {
    size_t s;
    BTree<T, K>* current;
};

template <class T, size_t K>
T value(BTreeIt<T, K> it);
template <class T, size_t K>
BTree<T, K> next(BTree<T, K> it);
template <class T, size_t K>
BTree<T, K> prev(BTree<T, K> it);
template <class T, size_t K>
bool hasNext(BTree<T, K> it);
template <class T, size_t K>
bool hasPrev(BTree<T, K> it);

#endif
