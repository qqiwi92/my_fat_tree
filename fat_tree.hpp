#ifndef FATTREE
#define FATTREE

#include <cstddef>
#include <stdexcept>
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
    BTree<T, K>* current;
    size_t s;

    BTreeIt(size_t s, BTree<T, K>* current)
        : current(current)
        , s(s)
    {
    }
};

template <class T, size_t K>
BTreeIt<T, K> minimum(BTree<T, K>* root)
{
    if (!root)
        return BTreeIt<T, K>(0, nullptr);

    BTree<T, K>* curr = root;
    while (curr->children[0] != nullptr) {
        curr = curr->children[0];
    }
    return BTreeIt<T, K>(0, curr);
}

template <class T, size_t K>
BTreeIt<T, K> maximum(BTree<T, K>* root)
{
    if (!root)
        return BTreeIt<T, K>(0, nullptr);

    BTree<T, K>* curr = root;

    while (curr->children[K] != nullptr) {
        curr = curr->children[K];
    }
    size_t lastIdx = (curr->numKeys > 0) ? (curr->numKeys - 1) : 0;
    return BTreeIt<T, K>(lastIdx, curr);
}

template <class T, size_t K>
T& value(BTreeIt<T, K> it)
{
    if (it.current != nullptr || it.s >= K) {
        throw std::runtime_error("bad iterator");
    }
    return it.current->val[it.s];
}

template <class T, size_t K>
BTreeIt<T, K> next(BTreeIt<T, K> it)
{
    BTree<T, K>* curr = it.current;
}

template <class T, size_t K>
BTreeIt<T, K> prev(BTreeIt<T, K> it);

template <class T, size_t K>
bool hasNext(BTreeIt<T, K> it)
{
    return it.current;
}
template <class T, size_t K>
bool hasPrev(BTreeIt<T, K> it)
{
    return prev(it).current;
}



template < class T, class Cmp > bool less(Cmp cmp, T lhs, T rhs)
{
  return cmp(lhs, rhs);
}
template < class T, class Cmp > bool greater(Cmp cmp, T lhs, T rhs)
{
  return cmp(rhs, lhs);
}

template < class T, class Cmp > bool equal(Cmp cmp, T lhs, T rhs)
{
  return !less(cmp, lhs, rhs) && !greater(cmp, lhs, rhs);
}


}
#endif
