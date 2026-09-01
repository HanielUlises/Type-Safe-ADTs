#include <iostream>
#include "overload.hpp"

template <typename T>
struct foo_float {
    T operator()(float op) {
        return T{};
    }
};

template <typename T>
struct foo_char {
    T operator()(char op) {
        return T{};
    }
};

using foo = overload_set<foo_float<float>, foo_char<char>>;

int main() {
    foo f{
        foo_float<float>{},
        foo_char<char>{}
    };

    auto x0 = f(0.f);
    auto x1 = f('a');

    std::cout << x0 << '\n';
    std::cout << x1 << '\n';
}
