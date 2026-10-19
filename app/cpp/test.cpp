
#include <iostream>
#include <string>
#include <chrono>

#include "cache_engine.hpp"

int main() {
    CacheEngine cache;
    std::string value;

    cache.set("city", "Ludhiana");
    cache.set_with_ttl("session", "active", 2);

    std::cout << std::boolalpha;

    std::cout << "City exists: "
              << cache.exist("city") << '\n';

    std::cout << "Session exists: "
              << cache.exist("session") << '\n';

    std::cout << "Wait 3 seconds, then press Enter...\n";
    std::cin.get();          

   // std::this_thread::sleep_for(std::chrono::seconds(3));

    std::cout << "Session exists after expiry: "
              << cache.exist("session") << '\n';


    cache.set("city", "Ludhiana");

std::cout << "City TTL: " << cache.ttl("city") << '\n';

cache.expire("city", 10);

std::cout << "City TTL after EXPIRE: "
          << cache.ttl("city") << '\n';          

    return 0;
}

