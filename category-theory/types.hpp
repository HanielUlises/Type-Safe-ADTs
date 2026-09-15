#include <concepts>

template<class T>
void unit(T) {}

template<class T>
struct mempty;

template<class T>
T mappend(T, T) = delete;
template<class M>
concept Monoid = requires (M m) {
    { mempty<M>::value() } -> std::same_as<M>;
    { mappend(m, m) } -> std::same_as<M>;
};