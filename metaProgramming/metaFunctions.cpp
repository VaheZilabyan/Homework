#include <iostream>

// is_same
template<typename T, typename U>
struct is_same {
	static constexpr bool value = false;
};
template<typename T>
struct is_same<T, T> {
	static constexpr bool value = true;
};
template<typename T, typename U>
constexpr bool is_same_v = is_same<T, U>::value;

// remove_reference
template<typename T>
struct remove_reference {
	using type = T;
};
template<typename T>
struct remove_reference<T&> {
	using type = T;
};
template<typename T>
struct remove_reference<T&&> {
	using type = T;
};
template<typename T>
using remove_reference_t = typename remove_reference<T>::type;

// enable_if
template<bool b, typename T = void>
struct enable_if {};

template<typename T>
struct enable_if<true, T> {
	using type = T;
};

template<typename T, typename U, class = typename enable_if<is_same_v<T, U>>::type>
void test(T) {
	std::cout << 1 << std::endl;
}
template<typename... T>
void test(...) {
	std::cout << 2 << std::endl;
}

// move
template<typename T>
remove_reference_t<T>&& move(T&& value) {
	return static_cast<remove_reference_t<T>&&>(value);
}

template<typename T>
T&& forward(T&& value) {
	return static_cast<T&&>(value);
}

void f(int&) {
	std::cout << "int&" << std::endl;
}
void f(int&&) {
	std::cout << "int&&" << std::endl;
}

template<typename T>
void foo(T&& x) {
	f(forward(x));
}

int main() {
	// test enable_if
	test<int, int>(1);
	test<int, char>(1);
	
	// test move
	int a = 0;
	f(a);
	f(move(a));
	
	// test forward
	foo(a);
	foo(move(a));
}