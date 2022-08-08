#include <iostream>
#include <exception>
#include <vector>
#include <memory>
#include <string>
#pragma once

template <typename T>
class Vector {
 public:
  using SizeType = size_t;
  using ConstIterator = const T*;
  using Iterator = T*;
  using ValueType = T;
  using Pointer = T*;
  using ConstPointer = const T*;
  using Reference = T&;
  using ConstReference = const T&;
  using ReverseIterator = std::reverse_iterator<Iterator>;
  using ConstReverseIterator = std::reverse_iterator<ConstIterator>;

 private:
  Pointer ptr_;
  SizeType size_;
  SizeType capacity_;

 public:
  Vector() noexcept : ptr_(nullptr), size_(0), capacity_(0) {
  }

  explicit Vector(SizeType size) noexcept(false) {
    try {
      ptr_ = new ValueType[size];
    } catch (...) {
      ptr_ = nullptr;
      size_ = 0;
      capacity_ = 0;
      throw;
    }
    size_ = size;
    capacity_ = size;
  }
  Vector(int size, int value) {
    if (size > 0) {
      ptr_ = new ValueType[size];
      for (SizeType i = 0; i < static_cast<size_t>(size); ++i) {
        ptr_[i] = value;
      }
      size_ = size;
      capacity_ = size_;
    } else {
      ptr_ = nullptr;
      size_ = 0;
      capacity_ = 0;
    }
  }
  template <class U>
  Vector(size_t size, U&& value) {
    if (size > 0) {
      Pointer ptr;
      ptr = new ValueType[size];
      try {
        for (SizeType i = 0; i < static_cast<size_t>(size); ++i) {
          ptr[i] = value;
      	}
      } catch (...) {
        delete[] ptr;
        throw;
      }
      ptr_ = ptr;
      size_ = size;
      capacity_ = size_;
    } else {
      ptr_ = nullptr;
      size_ = 0;
      capacity_ = 0;
    }
  }
  template <char*>
  Vector(size_t size, char* value) {
    if (size > 0) {
      Pointer ptr;
      ptr = new ValueType[size];
      try {
        for (SizeType i = 0; i < static_cast<size_t>(size); ++i) {
          ptr[i] = value;
      	}
      } catch (...) {
        delete[] ptr;
        throw;
      }
      ptr_ = ptr;
      size_ = size;
      capacity_ = size_;
    } else {
      ptr_ = nullptr;
      size_ = 0;
      capacity_ = 0;
    }
  }
  Vector(std::initializer_list<T> list) {
    Pointer ptr;
    auto it = list.begin();
    ptr = new ValueType[list.size()];
    try {
      for (SizeType i = 0; i < list.size(); ++i) {
        ptr[i] = *it;
        it++;
      }
    } catch (...) {
      delete[] ptr;
      ptr_ = nullptr;
      size_ = 0;
      capacity_ = 0;
      throw;
    }
    ptr_ = ptr;
    size_ = list.size();
    capacity_ = list.size();
  }
  template <class InputIt>
  Vector(InputIt first, InputIt last) noexcept(false) {
    auto ffirst = first;
    auto ffffirst = first;
    SizeType cnt = 0;
    while (ffirst != last) {
      cnt++;
      ffirst++;
    }
    if (cnt != 0) {
      Pointer ptr;
      ptr = new ValueType[cnt];
      try {
        SizeType i = 0;
        while (i != cnt) {
          ptr[i++] = *ffffirst;
          ffffirst++;
        }
      } catch (...) {
        delete[] ptr;
        ptr_ = nullptr;
        size_ = 0;
        capacity_ = 0;
        throw;
      }
      ptr_ = ptr;
      ptr = nullptr;
      size_ = cnt;
      capacity_ = cnt;
    } else {
      ptr_ = nullptr;
      size_ = 0;
      capacity_ = 0;
    }
  }
  ~Vector() noexcept {
    delete[] ptr_;
    capacity_ = 0;
    size_ = 0;
  }
  Vector(const Vector& vector) noexcept(false) {
    if (vector.ptr_ != nullptr) {
      Pointer ptr;
      ptr = new ValueType[vector.capacity_];
      try {
        for (SizeType i = 0; i < vector.size_; ++i) {
          ptr[i] = vector.ptr_[i];
        }
      } catch (...) {
        delete[] ptr;
        ptr_ = nullptr;
        size_ = 0;
        capacity_ = 0;
        throw;
      }
      ptr_ = ptr;
      size_ = vector.size_;
      capacity_ = vector.capacity_;
    } else {
      ptr_ = nullptr;
      size_ = 0;
      capacity_ = 0;
    }
  }
  Vector& operator=(const Vector& vector) noexcept(false) {
    if (vector.ptr_ != ptr_) {
      Pointer ptr;
      ptr = new ValueType[vector.capacity_];
      try {
        for (SizeType i = 0; i < vector.size_; ++i) {
          ptr[i] = vector.ptr_[i];
        }
      } catch (...) {
      	delete[] ptr;
        throw;
      }
      delete[] ptr_;
      ptr_ = ptr;
      size_ = vector.size_;
      capacity_ = vector.capacity_;
    }
    return *this;
  }
  Vector(Vector&& vector) noexcept {
    if (vector.ptr_) {
      ptr_ = vector.ptr_;
      vector.ptr_ = nullptr;
      size_ = vector.size_;
      capacity_ = vector.capacity_;
      vector.size_ = 0;
      vector.capacity_ = 0;
    } else {
      ptr_ = nullptr;
      size_ = 0;
      capacity_ = 0;
    }
  }
  Vector& operator=(Vector&& vector) noexcept {
    if (vector.ptr_) {
      delete[] ptr_;
      ptr_ = vector.ptr_;
      vector.ptr_ = nullptr;
      size_ = vector.size_;
      capacity_ = vector.capacity_;
      vector.size_ = 0;
      vector.capacity_ = 0;
    } else {
      delete[] ptr_;
      ptr_ = nullptr;
      size_ = 0;
      capacity_ = 0;
    }
    return *this;
  }
  SizeType Size() const noexcept(false) {
    return size_;
  }
  SizeType Capacity() const noexcept(false) {
    return capacity_;
  }
  bool Empty() const noexcept(false) {
    return size_ == 0;
  }
  Reference operator[](SizeType idx) {
    return ptr_[idx];
  }
  ConstReference operator[](SizeType idx) const {
    return ptr_[idx];
  }
  ConstReference At(SizeType idx) const noexcept(false) {
    if (idx > size_ - 1) {
      throw std::out_of_range{""};
    }
    return ptr_[idx];
  }
  Reference At(SizeType idx) noexcept(false) {
    if (idx > size_ - 1) {
      throw std::out_of_range{""};
    }
    return ptr_[idx];
  }
  Reference Front() noexcept {
    return ptr_[0];
  }
  ConstReference Front() const noexcept {
    return ptr_[0];
  }
  Reference Back() noexcept {
    return ptr_[size_ - 1];
  }
  ConstReference Back() const noexcept {
    return ptr_[size_ - 1];
  }
  void Clear() noexcept {
    size_ = 0;
  }
  Pointer Data() noexcept {
    return ptr_;
  }
  ConstPointer Data() const noexcept {
    return ptr_;
  }
  void Swap(Vector& other) noexcept {
    auto ptr = other.ptr_;
    other.ptr_ = ptr_;
    ptr_ = ptr;
    auto size = other.size_;
    other.size_ = size_;
    size_ = size;
    auto capacity = other.capacity_;
    other.capacity_ = capacity_;
    capacity_ = capacity;
  }
  void Resize(SizeType new_size) noexcept(false) {
    if (new_size <= capacity_) {
      size_ = new_size;
    } else {
      Pointer ptr;
      try {
        ptr = new ValueType[new_size * 2];
        for (SizeType i = 0; i < size_; ++i) {
          ptr[i] = std::forward<ValueType>(ptr_[i]);
        }
      } catch (...) {
        throw;
      }
      delete[] ptr_;
      ptr_ = ptr;
      capacity_ = 2 * new_size;
      size_ = new_size;
    }
  }
  void Resize(SizeType new_size, ValueType value) noexcept(false) {
    auto size = size_;
    if (new_size <= size_) {
      size_ = new_size;
    } else {
      try {
        this->Resize(new_size);
        for (SizeType i = size; i < new_size; ++i) {
          ptr_[i] = std::forward<ValueType>(value);
        }
      } catch (...) {
        throw;
      }
    }
  }
  void Reserve(SizeType new_cap) noexcept(false) {
    auto max_cap = capacity_ > new_cap ? capacity_ : new_cap;
    if (max_cap != capacity_) {
      Pointer ptr;
      try {
        ptr = new ValueType[max_cap];
        for (SizeType i = 0; i < size_; ++i) {
          ptr[i] = std::forward<T>(ptr_[i]);
        }
      } catch (...) {
        throw;
      }
      delete[] ptr_;
      ptr_ = ptr;
      capacity_ = max_cap;
    }
  }
  void ShrinkToFit() noexcept(false) {
    if (size_ != 0) {
      Pointer ptr;
      try {
        ptr = new ValueType[size_];
        for (SizeType i = 0; i < size_; ++i) {
          ptr[i] = std::forward<T>(ptr_[i]);
        }
      } catch (...) {
        throw;
      }
      delete[] ptr_;
      ptr_ = ptr;
      capacity_ = size_;
    } else {
      delete[] ptr_;
      ptr_ = nullptr;
      capacity_ = 0;
    }
  }
  void PushBack(ConstReference value) {
    if (size_ < capacity_) {
      try {
        ptr_[size_] = value;
      } catch (...) {
        size_--;
        throw;
      }
      size_++;
    } else {
      Pointer ptr = nullptr;
      try {
        ptr = new ValueType[(size_ + 1) * 2];
        for (SizeType i = 0; i < size_; ++i) {
          ptr[i] = std::forward<T>(ptr_[i]);
        }
        ptr[size_] = value;
      } catch (...) {
        throw;
      }
      delete[] ptr_;
      ptr_ = ptr;
      ++size_;
      capacity_ = 2 * size_;
    }
  }
  void PushBack(T&& value) {
    if (size_ < capacity_) {
      try {
        size_++;
        ptr_[size_ - 1] = std::move(value);
      } catch (...) {
        size_--;
        throw;
      }
    } else {
      Pointer ptr = nullptr;
      try {
        ptr = new ValueType[(size_ + 1) * 2];
        for (SizeType i = 0; i < size_; ++i) {
          ptr[i] = std::move(ptr_[i]);
        }
        ptr[size_] = std::move(value);
      } catch (...) {
        throw;
      }
      delete[] ptr_;
      ptr_ = ptr;
      ++size_;
      capacity_ = 2 * size_;
    }
  }
  void PopBack() {
    if (size_ != 0) {
      size_--;
    }
  }
  ConstPointer begin() const {  // NOLINT
    return ptr_;
  }
  Pointer begin() {  // NOLINT
    return ptr_;
  }
  ConstPointer end() const {  // NOLINT
    return ptr_ + size_;
  }
  Pointer end() {  // NOLINT
    return ptr_ + size_;
  }
  ConstPointer cbegin() const {  // NOLINT
    return ptr_;
  }
  ConstPointer cend() const {  // NOLINT
    return ptr_ + size_;
  }
  ReverseIterator rbegin() {  // NOLINT
    return static_cast<ReverseIterator>(ptr_ + size_);
  }
  ConstReverseIterator rbegin() const {  // NOLINT
    return static_cast<ReverseIterator>(ptr_ + size_);
  }
  ReverseIterator rend() {  // NOLINT
    return static_cast<ReverseIterator>(ptr_);
  }
  ConstReverseIterator rend() const {  // NOLINT
    return static_cast<ReverseIterator>(ptr_);
  }
  ConstReverseIterator crbegin() {  // NOLINT
    return static_cast<ReverseIterator>(ptr_ + size_);
  }
  ConstReverseIterator crbegin() const {  // NOLINT
    return static_cast<ReverseIterator>(ptr_ + size_);
  }
  ConstReverseIterator crend() {  // NOLINT
    return static_cast<ReverseIterator>(ptr_);
  }
  ConstReverseIterator crend() const {  // NOLINT
    return static_cast<ReverseIterator>(ptr_);
  }
  friend bool operator<(const Vector& v1, const Vector& v2) noexcept {
    bool flag = false;
    auto minn = v1.size_ > v2.size_ ? v2.size_ : v1.size_;
    size_t cnt = 0;
    if (v1.ptr_ != nullptr && v2.ptr_ != nullptr) {
      for (SizeType i = 0; i < minn; ++i) {
        if (v1[i] < v2[i]) {
          flag = true;
          break;
        }
        if (v1[i] == v2[i]) {
          cnt++;
        } else {
          break;
        }
      }
      if (cnt == minn) {
        flag = v1.size_ < v2.size_;
      }
    } else {
      if (!(v1.ptr_ == nullptr && v2.ptr_ != nullptr)) {
        flag = false;
      }
      if (v1.ptr_ == nullptr && v2.ptr_ != nullptr) {
        flag = true;
      }
    }
    return flag;
  }
  friend bool operator>(const Vector& v1, const Vector& v2) noexcept {
    return v2 < v1;
  }
  friend bool operator==(const Vector& v1, const Vector& v2) noexcept {
    return !((v1 > v2) || (v1 < v2));
  }
  friend bool operator!=(const Vector& v1, const Vector& v2) noexcept {
    return !(v1 == v2);
  }
  friend bool operator>=(const Vector& v1, const Vector& v2) noexcept {
    return !(v1 < v2);
  }
  friend bool operator<=(const Vector& v1, const Vector& v2) noexcept {
    return !(v1 > v2);
  }
};
