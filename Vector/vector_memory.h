#include <iostream>
#include <exception>
#include <vector>
#include <memory>
#include <string>
#define VECTOR_MEMORY_IMPLEMENTED
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
    Pointer ptr = size > 0 ? static_cast<T*>(operator new[](sizeof(T) * size)) : nullptr;
    size_t i = 0;
    try {
      for (; i < size; ++i) {
        new (ptr + i) T;
      }
    } catch (...) {
      --i;
      while (i != 0) {
        std::destroy_at(ptr + i);
        i--;
      }
      std::destroy_at(ptr);
      operator delete[](ptr);
      size_ = 0;
      capacity_ = 0;
      throw;
    }
    ptr_ = ptr;
    size_ = size;
    capacity_ = size;
  }
  Vector(int size, int value) {
    if (size > 0) {
      auto ptr = static_cast<T*>(operator new[](sizeof(T) * size));
      for (int i = 0; i < size; i++) {
        new (ptr + i) T(value);
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
  template <class U>
  Vector(size_t size, U&& value) {
    if (size > 0) {
      auto ptr = static_cast<T*>(operator new[](sizeof(T) * size));
      SizeType i = 0;
      try {
        for (; i < static_cast<size_t>(size); ++i) {
          new (ptr + i) T(value);
        }
      } catch (...) {
        i--;
        while (i != 0) {
          std::destroy_at(ptr + i);
          i--;
        }
        std::destroy_at(ptr);
        operator delete[](ptr);
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
      auto ptr = static_cast<T*>(operator new[](sizeof(T) * size));
      SizeType i = 0;
      try {
        for (; i < static_cast<size_t>(size); ++i) {
          new (ptr + i) T(value);
        }
      } catch (...) {
        i--;
        while (i != 0) {
          std::destroy_at(ptr + i);
          i--;
        }
        std::destroy_at(ptr);
        operator delete[](ptr);
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
    auto it = list.begin();
    auto ptr = static_cast<T*>(operator new[](sizeof(T) * list.size()));
    SizeType i = 0;
    try {
      for (; i < list.size(); ++i) {
        new (ptr + i) T(*it);
        it++;
      }
    } catch (...) {
      i--;
      while (i != 0) {
        std::destroy_at(ptr + i);
        i--;
      }
      std::destroy_at(ptr);
      operator delete[](ptr);
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
      auto ptr = static_cast<T*>(operator new[](sizeof(T) * cnt));
      SizeType i = 0;
      try {
        while (i != cnt) {
          new (ptr + (i++)) T(*ffffirst);
          ffffirst++;
        }
      } catch (...) {
        i--;
        while (i != 0) {
          std::destroy_at(ptr + i);
          i--;
        }
        std::destroy_at(ptr);
        operator delete[](ptr);
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
    for (size_t i = 0; i < size_; i++) {
      std::destroy_at(ptr_ + i);
    }
    size_ = capacity_ = 0;
    operator delete[](ptr_);
  }
  Vector(const Vector& vector) noexcept(false) {
    if (vector.ptr_ != nullptr) {
      auto ptr = static_cast<T*>(operator new[](sizeof(T) * vector.size_));
      SizeType i = 0;
      try {
        for (; i < vector.size_; ++i) {
          new (ptr + i) T(vector.ptr_[i]);
        }
      } catch (...) {
        i--;
        while (i != 0) {
          std::destroy_at(ptr + i);
          i--;
        }
        std::destroy_at(ptr);
        operator delete[](ptr);
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
      auto ptr = static_cast<T*>(operator new[](sizeof(T) * vector.size_));
      SizeType i = 0;
      try {
        for (; i < vector.size_; ++i) {
          new (ptr + i) T(vector.ptr_[i]);
        }
      } catch (...) {
        i--;
        while (i != 0) {
          std::destroy_at(ptr + i);
          i--;
        }
        std::destroy_at(ptr);
        operator delete[](ptr);
        if (size_ != 0) {
          size_t j = size_ - 1;
          while (j != 0) {
            std::destroy_at(ptr_ + j);
            j--;
          }
          std::destroy_at(ptr_);
        }
        operator delete[](ptr_);
        ptr_ = nullptr;
        size_ = 0;
        capacity_ = 0;
        throw;
      }
      if (size_ != 0) {
        size_t j = size_ - 1;
        while (j != 0) {
          std::destroy_at(ptr_ + j);
          j--;
        }
        std::destroy_at(ptr_);
      }
      operator delete[](ptr_);
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
    size_t j = 0;
    while (j != size_) {
      std::destroy_at(ptr_ + size_ - j - 1);
      j++;
    }
    operator delete[](ptr_);
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
    size_t i = 0;
    while (i != size_) {
      std::destroy_at(ptr_ + size_ - 1 - i);
      i++;
    }
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
  void Resize(SizeType new_size) {
    if (new_size <= capacity_) {
      if (new_size <= size_) {
        for (size_t i = new_size; i < size_; i++) {
          std::destroy_at(ptr_ + i);
        }
        size_ = new_size;
        return;
      }
      for (size_t i = size_; i < new_size; i++) {
        new (ptr_ + i) T;
      }
      size_ = new_size;
      return;
    }
    auto ptr = static_cast<T*>(operator new[](sizeof(T) * new_size));
    size_t k = 0;
    try {
      for (size_t i = 0; i < size_; i++) {
        k++;
        new (ptr + i) T(std::move(ptr_[i]));
      }
      for (size_t i = size_; i < new_size; i++) {
        k++;
        new (ptr + i) T;
      }
    } catch (...) {
      for (size_t i = 0; i < k; i++) {
        std::destroy_at(ptr + i);
      }
      operator delete[](ptr);
      throw;
    }
    for (size_t i = 0; i < size_; i++) {
      std::destroy_at(ptr_ + i);
    }
    operator delete[](ptr_);
    ptr_ = ptr;
    size_ = new_size;
    capacity_ = new_size;
  }
  void Resize(SizeType new_size, ValueType value) {
    if (new_size <= capacity_) {
      if (new_size <= size_) {
        for (size_t i = new_size; i < size_; i++) {
          std::destroy_at(ptr_ + i);
        }
        size_ = new_size;
        return;
      }
      for (size_t i = size_; i < new_size; i++) {
        ptr_[i] = value;
      }
      size_ = new_size;
      return;
    }
    auto ptr = static_cast<T*>(operator new[](sizeof(T) * new_size));
    size_t k = 0;
    try {
      for (size_t i = 0; i < size_; i++) {
        k++;
        new (ptr + i) T(ptr_[i]);
      }
      for (size_t i = size_; i < new_size; i++) {
        k++;
        new (ptr + i) T(value);
      }
    } catch (...) {
      for (size_t i = 0; i < k; i++) {
        std::destroy_at(ptr + i);
      }
      operator delete[](ptr);
      throw;
    }
    for (size_t i = 0; i < size_; i++) {
      std::destroy_at(ptr_ + i);
    }
    operator delete[](ptr_);
    ptr_ = ptr;
    size_ = new_size;
    capacity_ = new_size;
  }
  void Reserve(SizeType new_cap) noexcept(false) {
    auto max_cap = capacity_ > new_cap ? capacity_ : new_cap;
    if (max_cap != capacity_) {
      auto ptr = static_cast<T*>(operator new[](sizeof(T) * max_cap));
      SizeType i = 0;
      try {
        for (; i < size_; ++i) {
          new (ptr + i) T(std::forward<T>(ptr_[i]));
        }
      } catch (...) {
        i--;
        while (i != 0) {
          std::destroy_at(ptr + i);
          i--;
        }
        std::destroy_at(ptr);
        operator delete[](ptr);
        throw;
      }
      if (size_ != 0) {
        size_t j = size_ - 1;
        while (j != 0) {
          std::destroy_at(ptr_ + j);
          j--;
        }
        std::destroy_at(ptr_);
      }
      operator delete[](ptr_);
      ptr_ = ptr;
      capacity_ = max_cap;
    }
  }
  void ShrinkToFit() noexcept(false) {
    if (size_ != 0) {
      auto ptr = static_cast<T*>(operator new[](sizeof(T) * size_));
      SizeType i = 0;
      try {
        for (; i < size_; ++i) {
          new (ptr + i) T(std::forward<T>(ptr_[i]));
        }
      } catch (...) {
        i--;
        while (i != 0) {
          std::destroy_at(ptr + i);
          i--;
        }
        operator delete[](ptr);
        throw;
      }
      size_t j = 0;
      while (j != size_) {
        std::destroy_at(ptr_ + size_ - 1 - j);
        j++;
      }
      operator delete[](ptr_);
      ptr_ = ptr;
      capacity_ = size_;
    } else {
      operator delete[](ptr_);
      ptr_ = nullptr;
      capacity_ = 0;
    }
  }
  void PushBack(ConstReference value) {
    if (size_ < capacity_) {
      try {
        new (ptr_ + size_) T(value);
      } catch (...) {
        throw;
      }
      size_++;
    } else {
      auto ptr = static_cast<T*>(operator new[](sizeof(T) * (size_ + 1) * 2));
      SizeType i = 0;
      try {
        for (; i < size_; ++i) {
          new (ptr + i) T(std::forward<T>(ptr_[i]));
        }
        new (ptr + i) T(value);
      } catch (...) {
        i--;
        while (i != 0) {
          std::destroy_at(ptr + i);
          i--;
        }
        std::destroy_at(ptr);
        operator delete[](ptr);
        throw;
      }
      if (size_ != 0) {
        size_t j = size_ - 1;
        while (j != 0) {
          std::destroy_at(ptr_ + j);
          j--;
        }
        std::destroy_at(ptr_);
      }
      operator delete[](ptr_);
      ptr_ = ptr;
      ++size_;
      capacity_ = 2 * size_;
    }
  }
  void PushBack(T&& value) {
    if (size_ < capacity_) {
      try {
        new (ptr_ + size_) T(std::move(value));
      } catch (...) {
        throw;
      }
      size_++;
    } else {
      auto ptr = static_cast<T*>(operator new[](sizeof(T) * (size_ + 1) * 2));
      SizeType i = 0;
      try {
        for (; i < size_; ++i) {
          new (ptr + i) T(std::move(ptr_[i]));
        }
        new (ptr + i) T(std::move(value));
      } catch (...) {
        i--;
        while (i != 0) {
          std::destroy_at(ptr + i);
          i--;
        }
        std::destroy_at(ptr);
        operator delete[](ptr);
        throw;
      }
      if (size_ != 0) {
        size_t j = size_ - 1;
        while (j != 0) {
          std::destroy_at(ptr_ + j);
          j--;
        }
        std::destroy_at(ptr_);
      }
      operator delete[](ptr_);
      ptr_ = ptr;
      ++size_;
      capacity_ = 2 * size_;
    }
  }
  void PopBack() {
    if (size_ != 0) {
      std::destroy_at(ptr_ + size_ - 1);
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
  template <class... Types>
  void EmplaceBack(Types&&... args) {
    if (size_ < capacity_) {
      try {
        new (ptr_ + size_) T(args...);
      } catch (...) {
        throw;
      }
      size_++;
    } else {
      auto ptr = static_cast<T*>(operator new[](sizeof(T) * (size_ + 1) * 2));
      SizeType i = 0;
      try {
        for (; i < size_; ++i) {
          new (ptr + i) T(std::forward<T>(ptr_[i]));
        }
        new (ptr + i) T(args...);
      } catch (...) {
        i--;
        while (i != 0) {
          std::destroy_at(ptr + i);
          i--;
        }
        std::destroy_at(ptr);
        operator delete[](ptr);
        throw;
      }
      if (size_ != 0) {
        size_t j = size_ - 1;
        while (j != 0) {
          std::destroy_at(ptr_ + j);
          j--;
        }
        std::destroy_at(ptr_);
      }
      operator delete[](ptr_);
      ptr_ = ptr;
      ++size_;
      capacity_ = 2 * size_;
    }
  }
};
