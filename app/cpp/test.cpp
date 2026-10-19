
#include <iostream>
#include <string>

#include "cache_engine.hpp"

int main() {
    CacheEngine cache;

    cache.set("name", "Malkit");

    std::string value;

    if (cache.get("name", value)) {
        std::cout << "GET name: " << value << '\n';
    } else {
        std::cout << "Key not found\n";
    }

    std::cout << "EXISTS name: "
              << std::boolalpha
              << cache.exist("name") << '\n';

    std::cout << "DELETE name: "
              << cache.delete_key("name") << '\n';

    std::cout << "EXISTS name after deletion: "
              << cache.exist("name") << '\n';

    return 0;
}
