#include "cache_engine.hpp"

bool CacheEngine::is_expired(const CacheEntry& entry) const{
    if(!entry.has_expiry)return false;
    return std::chrono::steady_clock::now() >=entry.expiry_time;
}

void CacheEngine::set(const std::string& key , const std::string &value ){
    store[key]=CacheEntry{value , false , {}};
}

bool CacheEngine::get(const std::string &key , std::string &value){
    auto it = store.find(key);
    if(it == store.end()){
        return false;
    }
    if(is_expired(it->second)){
          store.erase(key);
          return false;
    }
    value = it->second.value;
        return true;
}

bool CacheEngine::delete_key(const std::string &key){
    return store.erase(key) > 0;
}
bool CacheEngine::exist(const std::string &key){
    return store.find(key) !=store.end();
}



// TTL Eviction Methods 

void CacheEngine::set_with_ttl(const std::string& key , const std::string &value , int ttl_seconds){
    if(ttl_seconds<=0){
        store.erase(key);
        return;
    }
    auto expire = std::chrono::steady_clock::now() + std::chrono::seconds(ttl_seconds);

     store[key]=CacheEntry{value , true , expire};
}

bool CacheEngine::expire(const std::string &key , int ttl_seconds){
    auto it=store.find(key);

    if(it==store.end())return false;
    if(is_expired(it->second)){
        store.erase(it);
        return false;
    }


    if (ttl_seconds <= 0) {
        store.erase(it);
        return true;
    }

    it->second.has_expiry=true;
    it->second.expiry_time= std::chrono::steady_clock::now()+ std::chrono::seconds(ttl_seconds);
    return true;


}

long long CacheEngine::ttl(const std::string& key) {
    auto it = store.find(key);

    if (it == store.end()) {
        return -2;
    }

    if (is_expired(it->second)) {
        store.erase(it);
        return -2;
    }

    if (!it->second.has_expiry) {
        return -1;
    }

    auto remaining =
        it->second.expiry_time - std::chrono::steady_clock::now();

    return std::chrono::duration_cast<std::chrono::seconds>(
        remaining
    ).count();
}

