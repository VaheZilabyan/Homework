#include <iostream>
#include "my_string.h"

int main()
{
    using std::cout;
    using std::endl;
    using namespace my_string;

    String s("Hello!");

    cout << "str     : " << s.c_str() << endl;
    cout << "size    : " << s.size() << endl;
    cout << "capacity: " << s.capacity() << endl;

    s.insert(2, "123456789abcdqwerty");


    cout << "str     : " << s.c_str() << endl;
    cout << "size    : " << s.size() << endl;
    cout << "capacity: " << s.capacity() << endl;

    return 0;
}
