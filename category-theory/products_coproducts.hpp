#pragma once

#include <utility>
#include <variant>

template <class A, class B>
A fst(std::pair<A, B> const& p) {
    return p.first;
}

template <class A, class B>
B snd(std::pair<A, B> const& p) {
    return p.second;
}

template <class A, class B>
using Product = std::pair<A, B>;


template <class A, class B>
using Coproduct = std::variant<A, B>;

template <class A, class B>
Coproduct<A, B> inl(A const& a) {
    return a;
}

template <class A, class B>
Coproduct<A, B> inr(B const& b) {
    return b;
}