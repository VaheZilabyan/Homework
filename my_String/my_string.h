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

    void clear();
    void reserve(size_t);
    void push_back(char ch);
    void pop_back();
    String& insert(size_t index, const char *str);
    //String& insert(size_t index, size_t count, char ch);

private:
    struct string_structure_
    {
        //size_t sz{0};
        size_t capacity;
        char *data;
    };

    size_t size_;
    union {
        char sso_buffer_[SSO_BUFFER_SIZE + 1];
        string_structure_ long_string_;
    };
    bool is_long_{false};
};

} // namespace my_string

#endif // STRING_H
