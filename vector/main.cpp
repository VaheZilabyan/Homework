#include <iostream>

#include "allocator.h"
#include "vector.h"

#include <vector>

using std::cout;
using std::endl;
using namespace myStl;
using namespace myVectorAllocator;
using my_vector = vector<int, allocator<int>>;

struct base {
    base() {
        std::cout << "constructor\n";
    }
};

void merge(my_vector::iterator left, my_vector::iterator right) {
    auto mid = left + (right - left) / 2;
    auto start1 = left;
    auto start2 = mid + 1;
    while (start1 <= mid && start2 <= right) {
        if (*start1 <= *start2) {
            start1++;
        } else {
            int value = *start2;
            auto index = start2;

            while (index != start1) {
                *index = *(index - 1);
                --index;
            }
            *start1 = value;
            start1++;
            mid++;
            start2++;
        }
    }
}

void mergeSort(my_vector::iterator left, my_vector::iterator right) {
    if (left != right) {
        auto mid = left + (right - left) / 2;
        mergeSort(left, mid);
        mergeSort(mid + 1, right);
        merge(left, right);
    }
}

int main()
{
    my_vector vec;
    vec.push_back(15);
    vec.push_back(11);
    vec.push_back(13);

    //mergeSort(vec.begin(), vec.end() - 1);

    for (int i : vec) {
        cout << i << " ";
    } cout << endl;

    /*std::vector<int> v;
    v.push_back(5);
    cout << v.size() << " " << v.capacity() << endl;*/

    cout << "end..." << endl;
    return 0;
}
