#include "hash_table.impl.hpp"

#include <iostream>
#include <string>

using namespace std;

int main() {
    using namespace DS;

    hash_table<std::string, int> m;
    m["1rd"] = 10;
    std::cout << m["1rd"] << std::endl;

    m.insert("2rd", 20);
    std::cout << m["2rd"] << std::endl;

    m.insert("3rd", 30);
    std::cout << m["3rd"] << std::endl;

    m["4rd"] = 40;
    std::cout << m["4rd"] << std::endl;

    std::cout << "size = " << m.size() << std::endl;

    if (m.find("1rd")) cout << "find\n";

    std::cout << "\nend main!!\n";
    return 0;
}

//831379
//4400016250
//0278257
