#include <iostream>
#include "my_string.h"

int main()
{
    using std::cout;
    using std::endl;
    using namespace my_string;

    String s("Hello World!!!!!sdf");

    cout << s.c_str() << endl;
    cout << s.size() << endl;
    cout << s.capacity() << endl;

    return 0;
}
