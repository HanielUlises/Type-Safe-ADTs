#include <variant>
#include <iostream>
#include <string>

int main() {
    using Value = std::variant<int, double, std::string>;

    Value a = 42;
    Value b = 3.1415;
    Value c = std::string("hello");

    auto print = std::overload{
        [](int i)              { std::cout << "int:    " << i << '\n'; },
        [](double d)           { std::cout << "double: " << d << '\n'; },
        [](const std::string& s){ std::cout << "string: " << s << '\n'; }
    };

    std::visit(print, a);
    std::visit(print, b);
    std::visit(print, c);

    return 0;
}