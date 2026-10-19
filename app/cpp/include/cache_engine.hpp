#include <string>
#include <unordered_map>

class CacheEngine{
    private:
       std::unordered_map<std::string , std::string> store;
    public:   
    void set(const std::string &key , const std::string &value);
    bool get(const std::string &key , std::string &value);
    bool delete_key(const std::string &key);
    bool exist(const std::string &key);
};