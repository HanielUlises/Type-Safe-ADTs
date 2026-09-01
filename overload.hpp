#pragma once

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
    using Fs::operator()...;
};
#endif

template<class... Ts>
struct overload : Ts... {
    using Ts::operator()...;
};

template<class... Ts>
overload(Ts...) -> overload<Ts...>;
