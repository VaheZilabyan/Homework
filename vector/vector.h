#ifndef VECTOR_H
#define VECTOR_H

#include <cstddef>
#include <iterator>
#include <initializer_list>

namespace myStl {

template<typename T, typename Allocator = std::allocator<T>>
class vector
{
public:
    using value_type = T;
    using pointer = value_type*;
    using reference = value_type&;
    using const_reference = const value_type&;
    using size_type = size_t;
    using difference_type = std::ptrdiff_t;
    using allocator_type = Allocator;
    class iterator;

    vector(const Allocator& alloc = Allocator());
    vector(size_t n, const T& value = T(), const Allocator& alloc = Allocator());
    vector(const std::initializer_list<T>& il, const Allocator& alloc = Allocator());
    void reserve(size_t n);
    void push_back(const T& value);
    void resize(size_t n, const_reference value = T());
    iterator insert(iterator pos, const T& value);
    iterator erase(iterator pos);
    void pop_back();
    void clear();
    void shrink_to_fit();
    reference at(size_t i);
    const_reference at(size_t i) const;
    const_reference front() const {
        return *begin();
    }
    const_reference back() const {
        return *(end() - 1);
    }
    size_t size() const {
        return size_;
    }
    size_t capacity() const {
        return capacity_;
    }
    bool empty() {
        return size_ == 0;
    }
    T& operator[](size_t index);
    const T& operator[](size_t index) const;
    iterator begin() {
        return iterator(arr_);
    }
    iterator end() {
        return iterator(arr_ + size_);
    }
    vector& operator=(const vector& other);
    ~vector();
public:
    class iterator {
    public:
        using value_type = T;
        using pointer = T*;
        using reference = T&;
        using difference_type = std::ptrdiff_t;
        using iterator_category = std::random_access_iterator_tag;

        iterator() : ptr_{nullptr} {}
        iterator(T *ptr) : ptr_{ptr} {}
        iterator(const iterator& other) : ptr_{other.ptr_} {}
        T& operator*() {
            return *ptr_;
        }
        T* operator->() {
            return ptr_;
        }
        iterator& operator++() {
            ++ptr_;
            return *this;
        }
        iterator operator++(int) {
            iterator copy(*this);
            ++(*this);
            return copy;
        }
        iterator& operator--() {
            --ptr_;
            return *this;
        }
        iterator operator--(int) {
            iterator copy(*this);
            --(*this);
            return copy;
        }
        iterator& operator+=(int n) {
            ptr_ += n;
            return *this;
        }
        iterator& operator-=(int n) {
            ptr_ -= n;
            return *this;
        }
        iterator operator+(int n) {
            auto copy = *this;
            copy += n;
            return copy;
        }
        iterator operator-(int n) {
            auto copy = *this;
            copy -= n;
            return copy;
        }
        difference_type operator-(iterator beg) {
            difference_type ret = 0;
            for(; beg.ptr_ != ptr_; ++beg) ++ret;
            return ret;
        }
        bool operator==(iterator p) {
            return p.ptr_ == ptr_;
        }
        bool operator!=(iterator p) {
            return !(p.ptr_ == ptr_);
        }
        bool operator<=(const iterator& other) const {
            return ptr_ <= other.ptr_;
        }
        bool operator>=(const iterator& other) const {
            return ptr_ >= other.ptr_;
        }
        T* get() {
            return ptr_;
        }
    private:
        T *ptr_;
    };
private:
    Allocator alloc_;
    size_t size_;
    size_t capacity_;
    T* arr_;
};

}

#include "vector.impl.h"

#endif // VECTOR_H
