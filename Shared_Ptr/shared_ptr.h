#include <iostream>
#pragma once
template <class T>
class SharedPtr {
 private:
  T* ptr_;
  int* cnt_;

 public:
  SharedPtr() : ptr_(nullptr), cnt_(nullptr) {
  }
  SharedPtr(T* ptr) : ptr_(ptr), cnt_(new int) {  //  NOLINT
    *cnt_ = 1;
  }
  SharedPtr(const SharedPtr<T>& other) : ptr_(other.ptr_) {
    if (other.ptr_ == nullptr) {
      ptr_ = nullptr;
      cnt_ = nullptr;
    } else {
      ptr_ = other.ptr_;
      *other.cnt_ += 1;
      cnt_ = other.cnt_;
    }
  }
  SharedPtr<T>& operator=(const SharedPtr<T>& other) {
    if (other.ptr_ != ptr_) {
      if (other.ptr_ == nullptr) {
        if (ptr_ != nullptr) {
          if (*cnt_ == 1) {
            delete ptr_;
            delete cnt_;
            ptr_ = other.ptr_;
            cnt_ = other.cnt_;
          } else {
            *cnt_ -= 1;
            ptr_ = other.ptr_;
            cnt_ = new int;
            *cnt_ = 0;
          }
        } else {
          delete ptr_;
          ptr_ = other.ptr_;
          delete cnt_;
          cnt_ = other.cnt_;
        }
      } else {
        if (ptr_ != nullptr) {
          if (*cnt_ == 1) {
            delete ptr_;
            delete cnt_;
            ptr_ = other.ptr_;
            cnt_ = other.cnt_;
            *cnt_ += 1;
          } else {
            *cnt_ -= 1;
            ptr_ = other.ptr_;
            cnt_ = other.cnt_;
            *cnt_ += 1;
          }
        } else {
          ptr_ = other.ptr_;
          delete cnt_;
          cnt_ = other.cnt_;
          *cnt_ += 1;
        }
      }
    }
    return *this;
  }
  SharedPtr(SharedPtr<T>&& other) noexcept {
    ptr_ = other.ptr_;
    other.ptr_ = nullptr;
    cnt_ = other.cnt_;
    other.cnt_ = nullptr;
  }
  SharedPtr<T>& operator=(SharedPtr<T>&& other) noexcept {
    if (other.ptr_ == ptr_) {
      other.ptr_ = nullptr;
      if (cnt_ != nullptr) {
        *cnt_ -= 1;
      }
    } else {
      if (other.ptr_ == nullptr) {
        if (ptr_ != nullptr) {
          if (*cnt_ == 1) {
            delete ptr_;
            delete cnt_;
            ptr_ = nullptr;
            cnt_ = nullptr;
          }
          if (*cnt_ > 1) {
            ptr_ = nullptr;
            *cnt_ -= 1;
            cnt_ = nullptr;
          }
        }
      } else {
        if (ptr_ == nullptr) {
          ptr_ = other.ptr_;
          cnt_ = other.cnt_;
          other.ptr_ = nullptr;
          other.cnt_ = nullptr;
        } else {
          if (*cnt_ == 1) {
            delete ptr_;
            delete cnt_;
            ptr_ = other.ptr_;
            cnt_ = other.cnt_;
            other.ptr_ = nullptr;
            other.cnt_ = nullptr;
          }
          if (*cnt_ > 1) {
            *cnt_ -= 1;
            ptr_ = other.ptr_;
            cnt_ = other.cnt_;
            other.ptr_ = nullptr;
            other.cnt_ = nullptr;
          }
        }
      }
    }
    return *this;
  }
  ~SharedPtr() {
    if (cnt_ != nullptr) {
      *cnt_ -= 1;
      if (*cnt_ <= 0) {
        delete ptr_;
        delete cnt_;
      }
    } else {
      delete ptr_;
      delete cnt_;
    }
  }
  void Reset(T* ptr = nullptr) {
    T* other = ptr_;
    if (ptr == nullptr) {
      if (ptr_ != nullptr) {
        if (*cnt_ == 1) {
          delete other;
          delete cnt_;
        } else {
          *cnt_ -= 1;
        }
        ptr_ = ptr;
        cnt_ = nullptr;
      }
    } else {
      if (ptr_ != nullptr && *cnt_ == 1) {
        delete other;
        ptr_ = nullptr;
        delete cnt_;
        cnt_ = nullptr;
      } else if (ptr_ != nullptr) {
        *cnt_ -= 1;
        ptr_ = ptr;
        cnt_ = new int;
        *cnt_ = 1;
      } else {
        ptr_ = ptr;
        cnt_ = new int;
        *cnt_ = 1;
      }
    }
  }
  void Swap(SharedPtr<T>& other) {
    if (other.ptr_ != ptr_) {
      auto tmp = cnt_;
      cnt_ = other.cnt_;
      other.cnt_ = tmp;
      auto buf = ptr_;
      ptr_ = other.ptr_;
      other.ptr_ = buf;
    }
  }
  T* Get() {
    return ptr_;
  }
  T* Get() const {
    return ptr_;
  }
  int UseCount() const {
    int t = -1;
    if (cnt_ == nullptr) {
      t = 0;
    } else {
      t = *cnt_;
    }
    return t;
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
