#include "shared_ptr.h"

namespace my_shared_ptr {

template <typename T>
shared_ptr<T>::shared_ptr() 
	: ptr_{ new controlBlock_{nullptr, 0} } {
	
}

template <typename T>
shared_ptr<T>::shared_ptr(T* ptr) 
	: ptr_{ new controlBlock_{ptr, 1} } {

}

template<typename T>
shared_ptr<T>::shared_ptr(const shared_ptr& copied) 
	: ptr_{ copied.ptr_ } {
	++ptr_->count;
}

template<typename T>
shared_ptr<T>::shared_ptr(shared_ptr&& moved)
	: ptr_{ moved.ptr_ } {
	moved.ptr_ = nullptr;
}

template<typename T>
shared_ptr<T>& shared_ptr<T>::operator=(const shared_ptr& copied)
{
	if (this != &copied) {
		this->~shared_ptr(); // --ptr_->count; if count==0 delete object
		ptr_ = copied.ptr_;
		++ptr_->count;
	}
	return *this;
}

template<typename T>
shared_ptr<T>& shared_ptr<T>::operator=(shared_ptr&& moved) noexcept {
	if (this != &moved) {
		this->~shared_ptr(); // --ptr_->count; if count==0 delete object
		ptr_ = moved.ptr_;
		--moved.ptr_->count;
		moved.ptr_ = nullptr;
		++ptr_->count;
	}
	return *this;
}

template <typename T>
shared_ptr<T>::~shared_ptr() {
	--ptr_->count;
	if (ptr_->count == 0) {
		delete ptr_->data;
		delete ptr_;
	}
}

template<typename T>
T& shared_ptr<T>::operator*() const {
	return *ptr_->data;
}
template<typename T>
T* shared_ptr<T>::operator->() const {
	return ptr_ ? ptr_->data : nullptr;
}

template<typename T>
size_t shared_ptr<T>::use_count() const {
	return ptr_ ? ptr_->count.load() : static_cast<unsigned __int64>(0);
}

template<typename T>
T* shared_ptr<T>::get() const
{
	return ptr_ ? ptr_->data : nullptr;
}

}