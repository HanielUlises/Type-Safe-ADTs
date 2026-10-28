#include <utility>

template <class A, class B>
A fst(std::pair<A, B> const &p) {
    return p.first;
}

template <class A, class B>
A snd(std::pair<A, B> const &p) {
    return p.first;
}