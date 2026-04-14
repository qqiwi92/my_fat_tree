#ifndef FATTREE
#define FATTREE

#include <cstddef>

namespace stuff {

template <class T, size_t K>
struct BTree {
    T val[K];
    BTree<T, K>* children[K + 1];
    BTree<T, K>* parent;
};

template <class T, size_t K>
struct BTreeIt {
    BTreeIt(size_t s, BTree<T, K>* current)
        : s(s)
        , current(current)
    {
    }
    BTree<T, K>* current;
    size_t s;
};

template <class T, size_t K>
BTreeIt<T, K>* minimum(BTree<T, K> it)
{
    if (!it) {
        return { nullptr, 0 };
    }
    while (it.children[0]) {
        it = it.children[0];
    }
    return { it, 0 };
}

template <class T, size_t K>
T value(BTreeIt<T, K> it);
template <class T, size_t K>
BTreeIt<T, K>* next(BTree<T, K> it);
template <class T, size_t K>
BTreeIt<T, K>* prev(BTree<T, K> it);
template <class T, size_t K>
bool hasNext(BTree<T, K> it);
template <class T, size_t K>
bool hasPrev(BTree<T, K> it);

}
#endif
