#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include <cstddef>
#include <type_traits>

namespace myVectorAllocator {

template<typename T>
class allocator
{
public:
    using value_type = T;
    using pointer  = T*;
    using const_pointer  = const T*;
    using reference  = T&;
    using const_reference  = const T&;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using propagate_on_container_move_assignment = std::true_type;
    using is_always_equal = std::true_type;

    template<typename U>
    struct rebind {
        using other = allocator<U>;
    };

    allocator() noexcept = default;
    allocator(const allocator&) noexcept = default;
    template<typename U>
    allocator(const allocator<U>&) noexcept {}


    static pointer allocate(size_t n) {
        return static_cast<T*>(::operator new(n * sizeof(T)));
        //return static_cast<T*>(malloc(n * sizeof(T)));
    }
    static pointer allocate(size_t newSize, T* ptr) {
        return static_cast<T*>(realloc(static_cast<void*>(ptr), newSize * sizeof(T)));
    }

    static void deallocate(T *ptr, size_t) noexcept {
        ::operator delete(ptr);
    }
    template<typename... Args>
    static void construct(T *ptr, const Args&... args) {
        new (ptr) T(args...);
    }
    static void destroy(T *ptr) noexcept {
        ptr->~T();
    }
};

}


#endif // ALLOCATOR_H
