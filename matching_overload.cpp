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

void example0(std::variant<int, float> &v) {
    std::cout << "`v` contains: ";
    struct visitor {
        void operator()(int) {std::cout << "int";}
        void operator()(float) {std::cout << "float";}
    };

    std::visit(visitor{}, v);
    std::cout << '\n';
}

void example1(std::variant<int,float> &v) {
    std::cout << "`v` contains: ";

    match([](int) {std::cout << "int";},
          [](float) {std::cout << "float";})(v);

    std::cout << '\n';
}

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
