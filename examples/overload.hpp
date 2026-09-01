#pragma once

template<typename A, typename B>
struct overload_set : A , B {
    using A::operator();
    using B::operator();
};

template<class... Ts>
struct overload : Ts... {
    using Ts::operator()...;
};

template<class... Ts>
overload(Ts...) -> overload<Ts...>;