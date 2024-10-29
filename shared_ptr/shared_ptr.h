#pragma once

#include <atomic>

namespace my_shared_ptr {

template <typename T>
class shared_ptr
{
public:
	shared_ptr();
	explicit shared_ptr(T *ptr);
	shared_ptr(const shared_ptr&);
	shared_ptr(shared_ptr&&);
	~shared_ptr();

	shared_ptr& operator=(const shared_ptr&);
	shared_ptr& operator=(shared_ptr&&) noexcept;

	T& operator*() const;
	T* operator->() const;

	size_t use_count() const;
	T* get() const;
private:
	struct controlBlock_
	{
		T* data;
		std::atomic<size_t> count;
	};
	controlBlock_* ptr_;
};

}

#include "shared_ptr.impl.h"