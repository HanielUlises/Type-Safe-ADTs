#include <variant>
#include <iostream>
#include <unordered_map>
#include <vector>

template <typename K, typename V>
struct key_value {
    virtual void put(K k, V v) = 0;
    virtual V get(K k) = 0;
};

// Implementation 1: stores values in a hash map
template <typename K, typename V>
class hash_key_value : public key_value<K, V> {
    std::unordered_map<K, V> data;

public:
    void put(K k, V v) override {
        data[k] = v;
    }

    V get(K k) override {
        return data.at(k);
    }
};

// Implementation 2: stores key-value pairs in a vector
template <typename K, typename V>
class vector_key_value : public key_value<K, V> {
    std::vector<std::pair<K, V>> data;

public:
    void put(K k, V v) override {
        for (auto& [key, value] : data) {
            if (key == k) {
                value = v;
                return;
            }
        }
        data.push_back({k, v});
    }

    V get(K k) override {
        for (auto& [key, value] : data) {
            if (key == k)
                return value;
        }
        throw std::runtime_error("Key not found");
    }
};


int main() {
    std::variant<int, float, char> v0 {2.0f};

    std::visit([] (auto x) {
        if constexpr(std::is_same_v<decltype(x), int>) {
            std::cout << x << "i\n";
        } else if constexpr(std::is_same_v<decltype(x), float>) {
            std::cout << x << "f\n";
        } else if constexpr(std::is_same_v<decltype(x), char>) {
            std::cout << x << "c\n";
        }
    }, v0);
}