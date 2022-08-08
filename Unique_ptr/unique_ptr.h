#pragma once
#include <iostream>
template <class T>
class UniquePtr {
 private:
  T* ptr_;

 public:
  UniquePtr() : ptr_(nullptr) {
  }
  explicit UniquePtr(T* ptr) : ptr_(ptr) {
  }
  UniquePtr(const UniquePtr&) = delete;
  UniquePtr<T>& operator=(const UniquePtr&) = delete;
  UniquePtr(UniquePtr<T>&& other) noexcept : ptr_(other.ptr_) {
    other.ptr_ = nullptr;
  }
  UniquePtr<T>& operator=(UniquePtr<T>&& other) noexcept {
    if (this != &other) {
      delete ptr_;
      ptr_ = other.ptr_;
      other.ptr_ = nullptr;
    }
    return *this;
  }
  ~UniquePtr() {
    delete ptr_;
  }
  T* Release() {
    T* ptr = ptr_;
    ptr_ = nullptr;
    return ptr;
  }
  void Reset(T* ptr = nullptr) {
    T* other = ptr_;
    ptr_ = ptr;
    delete other;
  }
  void Swap(UniquePtr<T>& x) noexcept {
    auto tmp = std::move(x);
    x = std::move(*this);
    *this = std::move(tmp);
  }
  T* Get() const {
    return ptr_;
  }
  T* Get() {
    return ptr_;
  }
  T& operator*() const {
    return *ptr_;
  }
  T* operator->() const {
    return ptr_;
  }
  explicit operator bool() const noexcept {
    bool flag = true;
    if (ptr_ == nullptr) {
      flag = false;
    }
    return flag;
  }
};
