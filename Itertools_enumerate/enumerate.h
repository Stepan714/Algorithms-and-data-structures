#include <iostream>
#define TEMPORARY_ENUMERATE_IMPLEMENTED
#pragma once

template <class T>
class EnumerateObjLvalue {
  using TIterator = std::conditional_t<std::is_const_v<T>, typename T::const_iterator, typename T::iterator>;
  TIterator begin_;
  TIterator end_;
  size_t size_;

 public:
  explicit EnumerateObjLvalue(T& v) : begin_(std::begin(v)), end_(std::end(v)), size_(0) {
    auto t = begin_;
    while (t != end_) {
      size_++;
      t++;
    }
  }
  class ConstIterator {
    friend class EnumerateObjLvalue;
    using TIterator = std::conditional_t<std::is_const_v<T>, typename T::const_iterator, typename T::iterator>;
    using Reference = std::conditional_t<std::is_const_v<T>, typename T::const_reference, typename T::reference>;
    TIterator it_;
    size_t idx_;

   public:
    ConstIterator(TIterator t, size_t idx) : it_(t), idx_(idx) {
    }
    ConstIterator& operator++() {
      it_ = std::next(it_);
      idx_++;
      return *this;
    }
    ConstIterator operator++(int) {
      ConstIterator old = *this;
      it_ = std::next(it_);
      idx_++;
      return old;
    }
    bool operator==(const ConstIterator& iter) const {
      return (it_ == iter.it_);
    }
    bool operator!=(const ConstIterator& iter) const {
      return (it_ != iter.it_);
    }
    std::pair<size_t, Reference> operator*() const {
      return std::pair<size_t, Reference>(idx_, *it_);
    }
  };
  ConstIterator begin() {  // NOLINT
    return ConstIterator(begin_, 0);
  }
  ConstIterator end() {  // NOLINT
    return ConstIterator(end_, size_);
  }
  ConstIterator begin() const {  // NOLINT
    return ConstIterator(begin_, 0);
  }
  ConstIterator end() const {  // NOLINT
    return ConstIterator(end_, size_);
  }
};

template <class T>
class EnumerateObjRvalue {
  using TIterator = std::conditional_t<std::is_const_v<T>, typename T::const_iterator, typename T::iterator>;
  T container_;
  size_t size_;

 public:
  explicit EnumerateObjRvalue(T&& v) : container_(v), size_(0) {
    auto t = std::begin(container_);
    auto end = std::end(container_);
    while (t != end) {
      size_++;
      t++;
    }
  }
  class ConstIterator {
    friend class EnumerateObjRvalue;
    using TIterator = std::conditional_t<std::is_const_v<T>, typename T::const_iterator, typename T::iterator>;
    using Reference = std::conditional_t<std::is_const_v<T>, typename T::const_reference, typename T::reference>;
    using const_iterator = typename T::const_iterator;
    TIterator it_;
    size_t idx_;

   public:
    ConstIterator(TIterator t, size_t idx) : it_(t), idx_(idx) {
    }
    ConstIterator& operator++() {
      it_ = std::next(it_);
      idx_++;
      return *this;
    }
    ConstIterator operator++(int) {
      ConstIterator old = *this;
      it_ = std::next(it_);
      idx_++;
      return old;
    }
    bool operator==(const ConstIterator& iter) const {
      return (it_ == iter.it_);
    }
    bool operator!=(const ConstIterator& iter) const {
      return (it_ != iter.it_);
    }
    std::pair<size_t, Reference> operator*() const {
      return std::pair<size_t, Reference>(idx_, *it_);
    }
  };
  ConstIterator begin() {  // NOLINT
    return ConstIterator(std::begin(container_), 0);
  }
  ConstIterator end() {  // NOLINT
    return ConstIterator(std::end(container_), size_);
  }
  ConstIterator begin() const {  // NOLINT
    return ConstIterator(std::begin(container_), 0);
  }
  ConstIterator end() const {  // NOLINT
    return ConstIterator(std::end(container_), size_);
  }
};

template <class Container, class Result = typename std::conditional_t<std::is_rvalue_reference_v<Container&&>, EnumerateObjRvalue<std::remove_reference_t<Container>>, EnumerateObjLvalue<std::remove_reference_t<Container>>>>
auto Enumerate(Container&& container) {
  return Result(std::forward<Container>(container));
}
