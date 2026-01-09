#include <variant>
#include <iostream>
#include <string>

template<class... Ts> struct overload : Ts... { using Ts::operator()...; };
template<class... Ts> overload(Ts...) -> overload<Ts...>;


struct Expr {
    using Variant = std::variant<
        int,                    
        struct Add { Expr left; Expr right; },   // Sum:     left + right
        struct Sub { Expr left; Expr right; },   // Subtraction:    left - right
        struct Mul { Expr left; Expr right; },   // Product:    left * right
        struct Neg { Expr expr; }                // Negation: -expr
    >;

    Variant data;

    explicit Expr(int i)             : data(i) {}
    Expr(Add a)                      : data(std::move(a)) {}
    Expr(Sub s)                      : data(std::move(s)) {}
    Expr(Mul m)                      : data(std::move(m)) {}
    Expr(Neg n)                      : data(std::move(n)) {}
};

int eval(const Expr& e) {
    return std::visit(overload{
        [](int i)                    { return i; },
        [](const Expr::Add& a)       { return eval(a.left) + eval(a.right); },
        [](const Expr::Sub& s)       { return eval(s.left) - eval(s.right); },
        [](const Expr::Mul& m)       { return eval(m.left) * eval(m.right); },
        [](const Expr::Neg& n)       { return -eval(n.expr); }
    }, e.data);
}

std::string to_string(const Expr& e) {
    return std::visit(overload{
        [](int i)                    { return std::to_string(i); },
        [](const Expr::Add& a)       { return "(" + to_string(a.left) + " + " + to_string(a.right) + ")"; },
        [](const Expr::Sub& s)       { return "(" + to_string(s.left) + " - " + to_string(s.right) + ")"; },
        [](const Expr::Mul& m)       { return "(" + to_string(m.left) + " * " + to_string(m.right) + ")"; },
        [](const Expr::Neg& n)       { return "-(" + to_string(n.expr) + ")"; }
    }, e.data);
}

int main() {
    Expr expr = Expr::Mul{
        Expr::Add{ Expr(2), Expr(3) },
        Expr::Neg{ Expr::Sub{ Expr(4), Expr(1) } }
    };

    std::cout << "Expression: " << to_string(expr) << "\n";
    std::cout << "Result: " << eval(expr) << "\n";

    return 0;
}