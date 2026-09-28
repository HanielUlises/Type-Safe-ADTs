#include <optional>

template <typename T> template 
<typename U = T> 
std::optional<T> optional(U value);