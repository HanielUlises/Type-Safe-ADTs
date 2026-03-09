#include <functional>
#include <memory>
#include <vector>
#include <string>
#include <numeric>
#include <cstdio>

template<typename A>
struct Stream;

template<typename A>
using StreamPtr = std::shared_ptr<Stream<A>>;


// Lazy value  (equivalent to OCaml Lazy.t)
template<typename A>
struct Lazy {
    mutable StreamPtr<A> cache = nullptr;
    std::function<StreamPtr<A>()> thunk;

    StreamPtr<A> force() const {
        if (!cache)
            cache = thunk();
        return cache;
    }
};


// Algebraic constructor: Cons
template<typename A>
struct Stream {
    A head;
    Lazy<A> tail;
};

// constructor helper (Cons)
template<typename A>
StreamPtr<A> cons(A head, std::function<StreamPtr<A>()> tail) {
    auto s = std::make_shared<Stream<A>>();
    s->head = head;
    s->tail.thunk = tail;
    return s;
}

int nex_value(int x) {
    return x > 0 ? -x : 1 - x;
}


// Stream generator
StreamPtr<int> helper(int n) {
    return cons<int>(n, [n]() {
        return helper(nex_value(n));
    });
}


StreamPtr<int> ints_from(int start) {
    return helper(start);
}


std::vector<int> take(int n, StreamPtr<int> s) {
    if (n <= 0) return {};

    auto rest = take(n - 1, s->tail.force());

    std::vector<int> r;
    r.reserve(rest.size() + 1);
    r.push_back(s->head);
    r.insert(r.end(), rest.begin(), rest.end());

    return r;
}


std::string join(const std::vector<int>& v, const std::string& sep) {
    if (v.empty()) return "";

    return std::accumulate(
        std::next(v.begin()), v.end(),
        std::to_string(v.front()),
        [&sep](const std::string& acc, int x) {
            return acc + sep + std::to_string(x);
        });
}


int main() {

    auto ints = ints_from(0);

    auto r1 = take(200, ints);
    auto r2 = take(400, ints);

    std::printf(
        "Taking 200 numbers [%s]\n\nFirst 400 numbers [%s]\n",
        join(r1, ",").c_str(),
        join(r2, ",").c_str());

}