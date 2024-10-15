#include <cstring>
#include <iostream>

int main() {
    char src[] = "Hello, World!";
    char dest[20];
    std::memcpy(dest, src, sizeof(src));
    std::cout << "Copied string: " << dest << std::endl;
    return 0;
}
