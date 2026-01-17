#include <iostream>
#include <variant>

int main() {
    std::variant<int, float, char> v0 {2.0f};

    std::visit([] (auto x) {
        if constexpr(std::is_same_v<decltype(x), int>)
            std::cout << x << "i\n";
        else if constexpr(std::is_same_v<decltype(x), float>)
            std::cout << x << "f\n";
        else if constexpr(std::is_same_v<decltype(x), char>)
            std::cout << x << "c\n";
    }, v0);
}