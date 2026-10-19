#include "cache_engine.hpp"
void CacheEngine::set(const std::string& key , const std::string &value){
    store[key]=value;
}
bool CacheEngine::get(const std::string& key , std::string &value){
    auto it = store.find(key);
    if(it == store.end()){
        return false;
    }
    value = it->second;
        return true;
}
bool CacheEngine::delete_key(const std::string &key){
    return store.erase(key) > 0;
}
bool CacheEngine::exist(const std::string &key){
    return store.find(key) !=store.end();
}

