#include "overload.hpp"

template <typename T>
struct foo_float {
    T operator()(float op) { return T{}; }
};

template <typename T>
struct foo_char {
    T operator()(char op) { return T{}; }
};
