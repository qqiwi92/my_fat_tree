#ifndef FATTREE
#define FATTREE

#include <cstddef>
#include <stdexcept>

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
    if (it.current == nullptr || it.s >= K) {
        throw std::runtime_error("bad iterator");
    }
    return it.current->val[it.s];
}

template <class T, size_t K>
size_t getRelativePosition(BTree<T, K>* root)
{
    if (root == nullptr || root->parent == nullptr) {
        throw std::out_of_range("bad input");
    }
    BTree<T, K>* parent = root->parent;
    for (size_t i = 0; i < parent->numKeys + 1; ++i) {
        if (parent->children[i] == root) {
            return i;
        }
    }
    throw std::out_of_range("not a child of a parent");
}

template <class T, size_t K>
BTreeIt<T, K> next(BTreeIt<T, K> it)
{
    if (!it.current)
        return BTreeIt<T, K>(0, nullptr);

    BTree<T, K>* node = it.current;

    if (node->children[it.s + 1] != nullptr) {
        return minimum(node->children[it.s + 1]);
    }
    if (it.s + 1 < node->numKeys) {
        return BTreeIt<T, K>(it.s + 1, node);
    }

    BTree<T, K>* parent = node->parent;
    BTree<T, K>* child = node;

    while (parent) {
        size_t relativePosition = getRelativePosition(node);

        if (relativePosition < parent->numKeys) {
            return BTreeIt<T, K>(relativePosition, parent);
        }
        child = parent;
        parent = parent->parent;
    }

    return { 0, nullptr };
}

template <class T, size_t K>
BTreeIt<T, K> prev(BTreeIt<T, K> it)
{
    if (!it.current)
        return BTreeIt<T, K>(0, nullptr);

    BTree<T, K>* node = it.current;

    if (node->children[it.s] != nullptr) {
        return maximum(node->children[it.s]);
    }

    if (it.s > 0) {
        return BTreeIt<T, K>(it.s - 1, node);
    }

    BTree<T, K>* child = node;
    BTree<T, K>* p = node->parent;

    while (p) {
        size_t idx = getRelativePosition(child);

        if (idx > 0) {
            return BTreeIt<T, K>(idx - 1, p);
        }

        child = p;
        p = p->parent;
    }

    return BTreeIt<T, K>(0, nullptr);
}

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

template <class T, class Cmp>
bool less(Cmp cmp, T lhs, T rhs)
{
    return cmp(lhs, rhs);
}
template <class T, class Cmp>
bool greater(Cmp cmp, T lhs, T rhs)
{
    return cmp(rhs, lhs);
}

template <class T, class Cmp>
bool equal(Cmp cmp, T lhs, T rhs)
{
    return !less(cmp, lhs, rhs) && !greater(cmp, lhs, rhs);
}

template <class T, size_t K, class Cmp>
bool isEqualUnsafe(BTree<T, K>* lhs, BTree<T, K>* rhs, Cmp cmp)
{
    BTree<T, K>* blhs = siftLeft(lhs);
    BTree<T, K>* brhs = siftLeft(rhs);
    while (hasNext(blhs) && hasNext(brhs)) {
        if (!equal(cmp, blhs->val, brhs->val))
            return false;
        blhs = next(blhs);
        brhs = next(brhs);
    }
    return !hasNext(blhs) && !hasNext(brhs);
}

template <class T, class Cmp, size_t K>
bool isEqual(BTree<T, K>* lhs, BTree<T, K>* rhs, Cmp cmp)
{
    if (!rhs && !lhs)
        return true;
    if (!rhs || !lhs)
        return false;
    assert(rhs && lhs);
    return isEqualUnsafe(lhs, rhs, cmp);
}

#endif
