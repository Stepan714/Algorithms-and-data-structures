#include <iostream>
#pragma once
#define REVERSE_RANGE_IMPLEMENTED

class Range {
  int begin_value_;
  int end_value_;
  int stepr_;

 public:
  class Iterator {
   private:
    int value_;
    int stepi_;
    explicit Iterator(int value, int step = 1) : value_(value), stepi_(step) {
    }
    friend class Range;

   public:
    Iterator& operator++() {
      value_ += stepi_;
      return *this;
    }
    Iterator operator++(int) {
      Iterator old = *this;
      value_ += stepi_;
      return old;
    }
    bool operator==(const Iterator& it) const {
      return value_ == it.value_;
    }
    bool operator!=(const Iterator& it) const {
      return value_ != it.value_;
    }
    int operator*() {
      return value_;
    }
  };
  class RevrseIterator {
   private:
    int value_;
    int stepi_;
    explicit RevrseIterator(int value, int step = 1) : value_(value), stepi_(step) {
    }
    friend class Range;

   public:
    RevrseIterator& operator++() {
      value_ -= stepi_;
      return *this;
    }
    RevrseIterator operator++(int) {
      RevrseIterator old = *this;
      value_ -= stepi_;
      return old;
    }
    bool operator==(const RevrseIterator& it) const {
      return value_ == it.value_;
    }
    bool operator!=(const RevrseIterator& it) const {
      return value_ != it.value_;
    }
    int operator*() {
      return value_;
    }
  };
  explicit Range(int end_value) : begin_value_(0), end_value_(end_value), stepr_(1) {
    if (end_value <= 0) {
      end_value_ = 0;
    }
  }
  Range(int first, int last, int step = 1) : begin_value_(first), end_value_(last), stepr_(step) {
    if (step == 0) {
      stepr_ = begin_value_ = end_value_ = 0;
    } else {
      if ((last - first) % step != 0) {
        end_value_ = first + (last - first + step - 1) / step * step;
      }
      if (step > 0 && begin_value_ >= end_value_) {
        stepr_ = begin_value_ = end_value_ = 0;
      }
      if (step < 0 && begin_value_ <= end_value_) {
        stepr_ = begin_value_ = end_value_ = 0;
      }
    }
  }
  Iterator begin() const {  // NOLINT
    return Iterator{begin_value_, stepr_};
  }
  Iterator end() const {  // NOLINT
    return Iterator{end_value_};
  }
  RevrseIterator rbegin() const {  // NOLINT
    return RevrseIterator(end_value_ - stepr_, stepr_);
  }
  RevrseIterator rend() const {  // NOLINT
    return RevrseIterator(begin_value_ - stepr_, stepr_);
  }
};
