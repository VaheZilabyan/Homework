#include <iostream>

#include "shared_ptr.h"

using namespace my_shared_ptr;

struct base {
	base() {
		std::cout << "ctor\n";
	}
	~base() {
		std::cout << "~ctor\n";
	}
	void foo() {
		std::cout << "foo\n";
	}
};

int main() {
	shared_ptr<base> sp1(new base);
	shared_ptr<base> sp2 = sp1;
	shared_ptr<base> sp3(new base);

	std::cout << sp3.get() << '\n';
	std::cout << sp3.use_count() << '\n';

	sp3 = std::move(sp1);

	std::cout << sp1.get() << " " << sp2.get() << " " << sp3.get() << '\n';
	std::cout << sp1.use_count() << " " << sp2.use_count() << " " << sp3.use_count() << '\n';

	std::cout << "end...\n";
	return 0;
}