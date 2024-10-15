#ifndef STRING_H
#define STRING_H

#include <cstddef>

namespace my_string {

class String
{
public:
    static constexpr size_t SSO_BUFFER_SIZE = 15;
    String() noexcept;
    String(const char*);
    String(const String&);
    ~String();

    const char* c_str() const noexcept;
    size_t size() const noexcept;
    size_t capacity() const noexcept;
    bool empty() const noexcept;
    char& operator[](size_t);
    const char& operator[](size_t) const;

private:
    struct string_structure_
    {
        size_t capacity;
        char *data;
    };

    size_t size_;
    union {
        char sso_buffer_[SSO_BUFFER_SIZE + 1];
        string_structure_ long_string_;
    };
    bool is_long_;
};

} // namespace my_string

#endif // STRING_H
