#pragma once

#define TEST1

#include <concepts>
#include <set>

template <typename T, typename Op>
concept Associativity = requires(T a, T b, T c, Op op) {
    op(a, op(b, c));
    op(op(a, b), c);
};

template<class T>
void unit(T) {}

template<class T>
struct mempty;

template<class T>
T mappend(T, T) = delete;
template<class M>
concept Monoid = requires (M m) {
    { mempty<M>::value() } -> std::same_as<M>;
    { mappend(m, m) } -> std::same_as<M>;
};

template<typename T, typename Op>
struct Magma {
    std::set<T> S;
    Op op;

    T combine(T &a, T &b) {
        return op(a, b);
    }
};

template<typename T, typename BinOp>
requires Associativity<BinOp, T>
struct Semigroup {
    std::set<T> S;
    BinOp op;

    T combine(T &a, T &b) {
        return op(a, b);
    }
};



#if defined(TEST1)
struct Add {
    int operator()(int a, int b) const {
        return a + b;
    }
};

Semigroup<int, Add> G{
    {1, 2, 3},
    Add{}
};
#endif 