#include <optional>

// The targtet optional will be in the same state as the source optional
// if the source optional contained a value, it will be copied/moved
std::optional<int> s0;
std::optional<int> s1{42};

auto d0 = s0; // unset `optional<int>`
auto d1 = s1; // set `optional<int>`, value `42`
