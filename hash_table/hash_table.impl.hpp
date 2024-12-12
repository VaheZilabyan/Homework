#include "hash_table.hpp"

#include <iostream>
#include <vector>
#include <list>

namespace DS {

template<typename Key, typename T, typename Hash, typename EqualTo>
hash_table<Key, T, Hash, EqualTo>::hash_table(){
    table.resize(m_bucket_size);
}

template<typename Key, typename T, typename Hash, typename EqualTo>
bool hash_table<Key, T, Hash, EqualTo>::find(const Key& key) {
    size_t index = hash(key);
    for (auto& kv : table[index]) {
        if (kv.key == key) {
            return true;
        }
    }
    return false;
}

template<typename Key, typename T, typename Hash, typename EqualTo>
bool hash_table<Key, T, Hash, EqualTo>::insert(const Key& key, const T& value) {
    size_t index = hash(key);
    for (auto& kv : table[index]) {
        if (kv.key == key) {
            return false;
        }
    }
    if (load_factor() >= max_load_factor) {
        rehash(2 * m_bucket_size);
        index = hash(key);
    }
    table[index].emplace_back(key, value);
    table[index].back().hash = std::hash<Key>{}(key);
    ++m_total_elements;
    return true;
}


template<typename Key, typename T, typename Hash, typename EqualTo>
T& hash_table<Key, T, Hash, EqualTo>::operator[](Key key) {
    size_t index = hash(key);
    for (auto& kv : table[index]) {
        if (kv.key == key) {
            return kv.value;
        }
    }
    if (load_factor() >= max_load_factor) {
        rehash(2 * m_bucket_size);
        index = hash(key);
    }
    table[index].emplace_back(key);
    table[index].back().hash = std::hash<Key>{}(key);
    ++m_total_elements;
    return table[index].back().value;
}

template<typename Key, typename T, typename Hash, typename EqualTo>
bool hash_table<Key, T, Hash, EqualTo>::erase(const Key& key) {
    size_t index = hash(key);
    auto listIter = table[index].begin();
    while (listIter != table[index].end()) {
        if (listIter->key == key) {
            table[index].erase(listIter);
            --m_total_elements;
            return true;
        }
        ++listIter;
    }

    return false;
}

template<typename Key, typename T, typename Hash, typename EqualTo>
void hash_table<Key, T, Hash, EqualTo>::rehash(size_t count) {
    std::vector<std::list<Node>> new_table(count);

    for (auto it = table.begin(); it != table.end(); ++it) {
        auto listIter = it->begin();
        while (listIter != it->end()) {
            size_t index = listIter->hash % count;
            new_table[index].emplace_back(listIter->key, listIter->value);
            new_table[index].back().hash = listIter->hash;
            ++listIter;
        }
    }

    m_bucket_size = count;
    table = std::move(new_table);
}


template<typename Key, typename T, typename Hash, typename EqualTo>
std::size_t hash_table<Key, T, Hash, EqualTo>::bucket_count() const {
    return m_bucket_size;
}

template<typename Key, typename T, typename Hash, typename EqualTo>
float hash_table<Key, T, Hash, EqualTo>::load_factor() const {
    return m_total_elements / m_bucket_size;
}

template<typename Key, typename T, typename Hash, typename EqualTo>
int hash_table<Key, T, Hash, EqualTo>::hash(Key key) {
    std::size_t hashed_key = std::hash<Key>{}(key);
    return hashed_key % m_bucket_size;
}

template<typename Key, typename T, typename Hash, typename EqualTo>
bool hash_table<Key, T, Hash, EqualTo>::empty() const {
    return m_total_elements == 0;
}

template<typename Key, typename T, typename Hash, typename EqualTo>
size_t hash_table<Key, T, Hash, EqualTo>::size() const {
    return m_total_elements;
}

}
