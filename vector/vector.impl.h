#include "vector.h"

namespace myStl {

template <typename T, typename Allocator>
vector<T, Allocator>::vector(const Allocator& alloc)
    : alloc_{alloc}
    , size_{0}
    , capacity_{0}
    , arr_{nullptr}
{}

template<typename T, typename Allocator>
vector<T, Allocator>::vector(size_t n, const T& value, const Allocator &alloc)
    : alloc_{alloc}
    , size_{n}
    , capacity_{n}
    , arr_{alloc_.allocate(size_)}
{
    for (int i = 0; i < size_; ++i) {
        //new (arr_ + i) T(value);
        alloc_.construct(arr_ + i, value);
    }
}

template <typename T, typename Allocator>
vector<T, Allocator>::vector(const std::initializer_list<T>& il, const Allocator& alloc)
    : alloc_{alloc}
    , size_{il.size()}
    , capacity_{il.size()}
    , arr_{alloc_.allocate(size_)}
{
    int i = 0;
    for (auto iter = il.begin(); iter != il.end(); ++iter) {
        alloc_.construct(arr_ + i++, *iter);
    }
}

template <typename T, typename Allocator>
void vector<T, Allocator>::reserve(size_t n) {
    if (n <= capacity_) return;
    //T *newarr = alloc_.allocate(n);

    T *newarr = alloc_.allocate(n, arr_);
    /* std::cout << "old address: " << arr_ << "\n";
    std::cout << "new address: " << newarr << "\n";*/

    for (size_t i = 0; i < size_; ++i) 	{
        alloc_.construct(newarr + i, arr_[i]);
        alloc_.destroy(arr_ + i);
    }

    alloc_.deallocate(arr_, size_);
    arr_ = newarr;
    capacity_ = n;
}

template <typename T, typename Allocator>
typename vector<T, Allocator>::iterator vector<T, Allocator>::insert(iterator pos, const T& value) {
    size_t dif = pos - begin();
    if (dif > size_) throw std::out_of_range("munmap_chunk(): invalid pointer");
    if (size_ == capacity_) {
        reserve(2 * size_);
    }

    auto it = end();
    for(size_t i = size_; it != pos; --i, --it) {
        T val = arr_[i - 1];
        alloc_.construct(arr_ + i, val);
    }
    alloc_.construct(pos.get(), value);
    ++size_;
    return pos;
}

template <typename T, typename Allocator>
typename vector<T, Allocator>::iterator vector<T, Allocator>::erase(iterator pos) {
    size_t dif = pos - begin();
    if (dif >= size_) throw std::out_of_range("position >= vector size");
    if (dif == size_ - 1) {
        pop_back();
        return pos;
    }
    for (size_t i = dif; i < size_; ++i) {
        T val = arr_[i + 1];
        alloc_.construct(arr_ + i, val);
    }
    --size_;
    return pos + 1;
}

template <typename T, typename Allocator>
void vector<T, Allocator>::push_back(const T& value) {
    if (size_ >= capacity_) {
        size_t newCapacity = (capacity_ == 0) ? 1 : (size_ * 2);
        reserve(newCapacity);
    }
    alloc_.construct(arr_ + size_, value);
    ++size_;
}

template <typename T, typename Allocator>
void vector<T, Allocator>::pop_back() {
    alloc_.destroy(arr_ + size_);
    --size_;
}

template <typename T, typename Allocator>
const T &vector<T, Allocator>::operator [](size_t index) const {
    return arr_[index];
}

template <typename T, typename Allocator>
T& vector<T, Allocator>::operator[](size_t index) {
    return arr_[index];
}

template<typename T, typename Allocator>
void vector<T, Allocator>::clear() {
    for(size_t i = 0; i < size_; ++i) {
        //(arr_ + i)->~T();
        alloc_.destroy(arr_ + i);
    }
    alloc_.deallocate(arr_, size_);
    size_ = 0;
}

template <typename T, typename Allocator>
void vector<T, Allocator>::resize(size_t n, const T& value) {
    if (n <= size_) {
        size_ = n;
    } else {
        if (n > capacity_) {
            reserve(n);
            size_ = n;
        }
        else {
            for (size_t i = size_; i < n; ++i) {
                alloc_.construct(arr_ + i, value);
            }
            size_ = n;
        }
    }
}

template<typename T, typename Allocator>
void vector<T, Allocator>::shrink_to_fit() {
    capacity_ = size_;
}

template <typename T, typename Allocator>
T& vector<T, Allocator>::at(size_t i) {
    if (i >= size_) throw std::out_of_range("index >= size");
    return arr_[i];
}

template <typename T, typename Allocator>
const T& vector<T, Allocator>::at(size_t i) const {
    if (i >= size_) throw std::out_of_range("index >= size");
    return arr_[i];
}

template<typename T, typename Allocator>
vector<T, Allocator>& vector<T, Allocator>::operator=(const vector& other) {
    if (this != &other) {
        T *newarr = alloc_.allocate(other.capacity_);

        for (size_t i = 0; i < other.size_; ++i) {
            alloc_.construct(newarr + i, other[i]);
        }
        for (size_t i = 0; i < size_; ++i) {
            alloc_.destroy(arr_ + i);
        }
        alloc_.deallocate(arr_, capacity_);
        arr_ = newarr;
        size_ = other.size_;
        capacity_ = other.capacity_;
    }
    return *this;
}

template<typename T, typename Allocator>
vector<T, Allocator>::~vector() {
    if (empty()) {
        clear();
    }
}

}
