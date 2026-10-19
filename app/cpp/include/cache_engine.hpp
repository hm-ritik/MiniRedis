
#pragma once

#include <string>
#include <unordered_map>
#include <chrono>

class CacheEngine {
private:
    struct CacheEntry{
        std::string value;
        bool has_expiry= false;
        std::chrono::steady_clock::time_point expiry_time;
    };

    std::unordered_map<std::string, CacheEntry> store;

    bool is_expired(const CacheEntry& entry) const;



public:
    void set(const std::string& key, const std::string& value);
    bool get(const std::string& key, std::string& value);
    bool delete_key(const std::string& key);
    bool exist(const std::string& key);

    // time to leave eviction methods 
    void set_with_ttl(const std::string&key , const std::string &value , int ttl_seconds);
    bool expire(const std::string &key , int ttl_seconds);
    long long ttl(const std::string &key);

};
