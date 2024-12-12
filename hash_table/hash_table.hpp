#ifndef HASH_TABLE_HPP
#define HASH_TABLE_HPP

#include <iostream>
#include <vector>
#include <list>

namespace DS {

template<typename Key, typename T, typename Hash = std::hash<Key>, typename EqualTo = std::equal_to<Key>>
class hash_table {
private:
    struct Node {
        Key key;
        T value;
        uint64_t hash;
        Node(const Key& k) : key(k), value(0) {}
        Node(const Key& k, const T& v) : key(k), value(v) {}
    };
private:
    std::vector<std::list<Node>> table;
    std::size_t m_bucket_size = 3;
    std::size_t m_total_elements = 0;
    static constexpr float max_load_factor = 1.0;

public:
    hash_table();
    bool find(const Key& key);
    bool insert(const Key& key, const T& value);
    bool erase(const Key& key);
    T& operator[](Key key);
    bool empty() const;
    size_t size() const;

    float load_factor() const;
    std::size_t bucket_count() const;

    int hash(Key key);
    void rehash(size_t count);
};

} //namespace DS

#endif
