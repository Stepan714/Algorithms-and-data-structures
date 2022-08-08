#include <stdexcept>
#pragma once
class StringViewOutOfRange : public std::out_of_range {
 public:
  StringViewOutOfRange() : std::out_of_range("StringViewOutOfRange") {
  }
};
class StringView {
  const char* ptr_;
  size_t size_;

 public:
  StringView() : ptr_(nullptr), size_(0) {
  }
  StringView(const char* str) : ptr_(str), size_(0) {  // NOLINT
    size_t i = 0;
    while (ptr_[i] != '\0') {
      i++;
    }
    size_ = i;
  }
  StringView(const char* str, size_t len) : ptr_(str), size_(len) {
  }
  char operator[](size_t idx) {
    return ptr_[idx];
  }
  char operator[](size_t idx) const {
    return ptr_[idx];
  }
  char At(size_t idx) {
    if (idx >= size_) {
      throw StringViewOutOfRange{};
    }
    return ptr_[idx];
  }
  char At(size_t idx) const {
    if (idx >= size_) {
      throw StringViewOutOfRange{};
    }
    return ptr_[idx];
  }
  char Front() {
    return ptr_[0];
  }
  char Front() const {
    return ptr_[0];
  }
  char Back() {
    return ptr_[size_ - 1];
  }
  char Back() const {
    return ptr_[size_ - 1];
  }
  size_t Size() const {
    return size_;
  }
  size_t Length() const {
    return size_;
  }
  const char* Data() const {
    return ptr_;
  }
  bool Empty() const {
    bool flag = false;
    if (size_ == 0) {
      flag = true;
    }
    return flag;
  }
  void Swap(StringView& other) {
    auto tmp = other.ptr_;
    auto buf = other.size_;
    other.ptr_ = ptr_;
    other.size_ = size_;
    ptr_ = tmp;
    size_ = buf;
  }
  const char* RemovePrefix(size_t prefix_size) {
    ptr_ = ptr_ + prefix_size;
    size_ -= prefix_size;
    return ptr_;
  }
  const char* RemoveSuffix(size_t suffix_size) {
    size_ -= suffix_size;
    return ptr_;
  }
  StringView Substr(size_t pos, size_t count = -1) {
    size_t min_size = count < Size() - pos ? count : Size() - pos;
    if (pos >= size_) {
      throw StringViewOutOfRange{};
    }
    StringView str;
    str.ptr_ = ptr_ + pos;
    str.size_ = min_size;
    return str;
  }
};
