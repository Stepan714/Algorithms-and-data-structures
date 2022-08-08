#include <iostream>
#pragma once

template <class T>
class Reversed {
  using TIterator =
      std::conditional_t<std::is_const_v<T>, typename T::const_reverse_iterator, typename T::reverse_iterator>;
  TIterator rbegin_;
  TIterator rend_;

 public:
  explicit Reversed(T& v) : rbegin_(std::rbegin(v)), rend_(std::rend(v)) {
  }
  explicit Reversed(T&& v) : rbegin_(std::rbegin(v)), rend_(std::rend(v)) {
  }
  class ReverseIterator {
    friend class Enumerate;
    using TIterator =
        std::conditional_t<std::is_const_v<T>, typename T::const_reverse_iterator, typename T::reverse_iterator>;
    using Reference = std::conditional_t<std::is_const_v<T>, typename T::const_reference, typename T::reference>;
    TIterator it_;

   public:
    explicit ReverseIterator(TIterator t) : it_(t) {
    }
    ReverseIterator& operator++() {
      it_ = std::next(it_);
      return *this;
    }
    ReverseIterator operator++(int) {
      ReverseIterator old = *this;
      it_ = std::next(it_);
      return old;
    }
    bool operator==(const ReverseIterator& iter) const {
      return (it_ == iter.it_);
    }
    bool operator!=(const ReverseIterator& iter) const {
      return (it_ != iter.it_);
    }
    Reference operator*() const {
      return *it_;
    }
  };
  ReverseIterator begin() {  // NOLINT
    return ReverseIterator(rbegin_);
  }
  ReverseIterator end() {  // NOLINT
    return ReverseIterator(rend_);
  }
  ReverseIterator begin() const {  // NOLINT
    return ReverseIterator(rbegin_);
  }
  ReverseIterator end() const {  // NOLINT
    return ReverseIterator(rend_);
  }
  ReverseIterator rbegin() {  // NOLINT
    return ReverseIterator(rbegin_);
  }
  ReverseIterator rend() {  // NOLINT
    return ReverseIterator(rend_);
  }
  ReverseIterator rbegin() const {  // NOLINT
    return ReverseIterator(rbegin_);
  }
  ReverseIterator rend() const {  // NOLINT
    return ReverseIterator(rend_);
  }
};
