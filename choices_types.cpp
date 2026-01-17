#include <variant>
#include <functional>
#include <utility>
#include <type_traits>
#include <string>

// Sum type
template <class L, class R>
using Either = std::variant<L, R>;

// Product type
template <class A, class B>
struct Pair {
    A fst;
    B snd;
};

// Unit
struct Unit {};

// Functor over Either
template <class L, class R, class F>
auto fmap_right(const Either<L, R>& e, F f)
    -> Either<L, std::invoke_result_t<F, R>>
{
    using Out = Either<L, std::invoke_result_t<F, R>>;
    return std::visit(
        [&](auto&& x) -> Out {
            using X = std::decay_t<decltype(x)>;
            if constexpr (std::is_same_v<X, L>)
                return x;
            else
                return f(x);
        },
        e
    );
}

// Eliminator
template <class L, class R, class FL, class FR>
auto fold(const Either<L, R>& e, FL fl, FR fr)
    -> std::common_type_t<
        std::invoke_result_t<FL, L>,
        std::invoke_result_t<FR, R>>
{
    return std::visit(
        [&](auto&& x) {
            using X = std::decay_t<decltype(x)>;
            if constexpr (std::is_same_v<X, L>)
                return fl(x);
            else
                return fr(x);
        },
        e
    );
}

// Simple algebra
struct Nat {
    unsigned value;
};

struct Bool {
    bool value;
};

// Morphisms
inline Nat succ(Nat n) { return {n.value + 1}; }
inline Bool is_zero(Nat n) { return {n.value == 0}; }

// Example term
Either<Bool, Nat> term(Nat n) {
    if (n.value == 0) return Bool{true};
    return succ(n);
}

// Composition
int main() {
    Either<Bool, Nat> e = term({1});

    auto mapped = fmap_right(e, is_zero);

    auto result = fold(
        mapped,
        [](Bool b) { return b.value ? 1 : 0; },
        [](Bool b) { return b.value ? 2 : 3; }
    );

    return result;
}
