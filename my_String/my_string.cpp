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
        // Copy in heap buffer
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

}
