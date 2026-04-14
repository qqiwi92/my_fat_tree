#ifndef FATTREE
#define FATTREE

#include <cstddef>

namespace stuff {

template <class T, size_t K>
struct BTree {
    T val[K];
    BTree<T, K>* children[K + 1];
    BTree<T, K>* parent;
    size_t numKeys;
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
BTreeIt<T, K> minimum(BTree<T, K>* root)
{
    if (!root) return BTreeIt<T, K>(0, nullptr);

    BTree<T, K>* curr = root;
    while (curr->children[0] != nullptr) {
        curr = curr->children[0];
    }
    return BTreeIt<T, K>(0, curr);
}

template <class T, size_t K>
BTreeIt<T, K> maximum(BTree<T, K>* root)
{
    if (!root) return BTreeIt<T, K>(0, nullptr);

    BTree<T, K>* curr = root;
    
    while (curr->children[K] != nullptr) {
        curr = curr->children[K];
    }

    return BTreeIt<T, K>(curr->numKeys - 1, curr);
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
