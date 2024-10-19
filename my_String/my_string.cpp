#include "my_string.h"

#include <string.h>
#include <iostream>

namespace my_string {

String::String() noexcept
    : size_(0),
    is_long_(false)
{
    sso_buffer_[0] = '\0';
}

String::String(const char* str)
    : size_(strlen(str))
    , is_long_(size_ > SSO_BUFFER_SIZE)
{
    if (is_long_) {
        long_string_.data = new char[size_ + 1];
        memcpy(long_string_.data, str, size_ + 1);
        long_string_.capacity = size_;
    } else {
        // Copy to SSO buffer
        memcpy(sso_buffer_, str, size_ + 1);
    }
}

String::String(const String& other)
    : size_(other.size_), is_long_(other.is_long_) {
    if (is_long_) {
        // Copy in heap buffer
        long_string_.data = new char[size_ + 1];
        memcpy(long_string_.data, other.long_string_.data, size_ + 1);
        long_string_.capacity = other.long_string_.capacity;
    } else {
        // Copy to SSO buffer
        memcpy(sso_buffer_, other.sso_buffer_, size_ + 1);
    }
}

String::~String() {
    if (is_long_) {
        delete[] long_string_.data;
    }
}

const char* String::c_str() const noexcept {
    return is_long_? long_string_.data : sso_buffer_;
}

size_t String::size() const noexcept {
    return size_;
}

size_t String::capacity() const noexcept {
    return is_long_ ? long_string_.capacity : SSO_BUFFER_SIZE;
}

bool String::empty() const noexcept {
    return size_ == 0;
}

char& String::operator[](size_t index) {
    return is_long_ ? long_string_.data[index] : sso_buffer_[index];
}

const char& String::operator[](size_t index) const {
    return is_long_ ? long_string_.data[index] : sso_buffer_[index];
}

void String::clear() {
    size_ = 0;
}

void String::reserve(size_t new_capacity) {
    if (is_long_) {
        char *new_buffer = new char[new_capacity + 1];
        memcpy(new_buffer, long_string_.data, size_ + 1); //or new_capacity , without +1
        delete[] long_string_.data;
        long_string_.data = new_buffer;
        long_string_.capacity = new_capacity;
    } else {
        if (new_capacity > SSO_BUFFER_SIZE) {
            char* new_buffer = new char[new_capacity + 1];
            memcpy(new_buffer, sso_buffer_, size_ + 1);
            // Switch to long string mode
            long_string_.data = new_buffer;
            long_string_.capacity = new_capacity;
            is_long_ = true;
        }
    }
}

void String::push_back(char ch) {

    if (is_long_) {
        if (size_ + 1 > long_string_.capacity) {
            reserve(long_string_.capacity * 2);
        }
        long_string_.data[size_++] = ch;
        long_string_.data[size_] = '\0';
    } else {
        if (size_ < SSO_BUFFER_SIZE) {
            sso_buffer_[size_++] = ch;
            sso_buffer_[size_] = '\0';
        } else { // (size_ == SSO_BUFFER_SIZE)
            size_t new_capacity = SSO_BUFFER_SIZE * 2;
            char* new_data = new char[new_capacity + 1];
            memcpy(new_data, sso_buffer_, size_ + 1);
            new_data[size_] = ch;
            ++size_;
            new_data[size_] = '\0';
            long_string_.data = new_data;
            long_string_.capacity = new_capacity;
            is_long_ = true;
        }
    }
}

void String::pop_back() {
    if (is_long_) {
        long_string_.data[size_ - 1] = '\0';
    } else {
        sso_buffer_[size_ - 1] = '\0';
    }
    --size_;
}

String& String::insert(size_t index, const char *str) {
    size_t len = strlen(str);
    if (size_ + len <= SSO_BUFFER_SIZE) {
        for (size_t i = size_ + len; i >= index + len; --i) {
            sso_buffer_[i] = sso_buffer_[i - len];
        }
        int j = 0;
        for (size_t i = index; i < index + len; ++i) {
            sso_buffer_[i] = str[j++];
        }
        size_ += len;
    } else {    // copy from sso_buffer_ to heap data
        size_t new_capacity = size_ + len;
        char* new_data = new char[new_capacity + 1];    //+1 for '\0'

        size_t k = 0;
        size_t i = 0;
        for ( ; i < index; ++i) {
            new_data[i] = sso_buffer_[k++];
        }
        int j = 0;
        for ( ; i < index + len; ++i) {
            new_data[i] = str[j++];
        }
        for ( ; i < new_capacity; ++i) {
            new_data[i] = sso_buffer_[k++];
        }
        new_data[new_capacity] = '\0';

        long_string_.data = new_data;
        size_ = new_capacity;
        long_string_.capacity = new_capacity;
        is_long_ = true;
    }
}

}
