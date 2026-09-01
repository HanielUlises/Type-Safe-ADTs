#pragma once

#include <variant>

#define VARIADIC

#ifdef ADDITIVE

template<typename A, typename B>
struct overload_set : A, B {
    using A::operator();
    using B::operator();

    overload_set(A a, B b)
        : A(a), B(b) {}
};

#elifdef VARIADIC

template <typename... Fs>
struct overload_set : Fs... {
    template<typename... Xs>
    constexpr overload_set(Xs &&...xs) 
        : Fs{std::forward<Xs>(xs)}...
    {}

    using Fs::operator()...;
};

template<typename... Xs>
overload_set(Xs&&... xs) 
    -> overload_set<std::decay_t<Xs>...>;

template <typename... Fs>
auto match(Fs&&... Fs) {
    return[
        visitor = overload_set{std::forward<Fs>(fs)...};
    ](auto&&... vs) -> decltype(auto) {
        return std::visit(visitor,
            std::forward<decltype(vs)>(vs)...);
    };
}

#endif

template<class... Ts>
struct overload : Ts... {
    using Ts::operator()...;
};

template<class... Ts>
overload(Ts...) -> overload<Ts...>;
