#include <iostream>
#include <vector>
#include <list>
#pragma once

template <typename KeyT>
class UnorderedSet {
  std::vector<std::list<KeyT>> v_;
  size_t count_bucket_;
  size_t count_value_;
  std::hash<KeyT> hash_;

 public:
  UnorderedSet() : v_(), count_bucket_(0), count_value_(0) {
  }
  explicit UnorderedSet(size_t count_bucket) : v_(count_bucket), count_bucket_(count_bucket), count_value_(0) {
  }
  template <class ForwardIt>
  UnorderedSet(ForwardIt first, ForwardIt last) : v_(0) {
    auto first1 = first;
    size_t cnt = 0;
    while (first1 != last) {
      cnt++;
      first1++;
    }
    for (size_t i = 0; i < cnt; ++i) {
      v_.push_back(std::list<KeyT>(0));
    }
    hash_ = std::hash<KeyT>{};
    count_bucket_ = cnt;
    count_value_ = cnt;
    while (first != last) {
      size_t hash = hash_(*first) % count_bucket_;
      auto it1 = v_[hash].begin();
      auto it2 = v_[hash].end();
      bool flag = false;
      while (it1 != it2) {
        if (*it1 == *first) {
          flag = true;
          break;
        }
        ++it1;
      }
      if (!flag) {
        v_[hash].push_back(*first);
      }
      first++;
    }
  }
  UnorderedSet(const UnorderedSet& uset) {
    v_ = uset.v_;
    count_bucket_ = uset.count_bucket_;
    count_value_ = uset.count_value_;
    hash_ = uset.hash_;
  }
  UnorderedSet(UnorderedSet&& uset) {
    v_ = std::move(uset.v_);
    count_bucket_ = uset.count_bucket_;
    count_value_ = uset.count_value_;
    hash_ = uset.hash_;
    uset.count_bucket_ = 0;
    uset.count_value_ = 0;
  }
  UnorderedSet& operator=(const UnorderedSet& uset) {
    v_ = uset.v_;
    count_bucket_ = uset.count_bucket_;
    count_value_ = uset.count_value_;
    hash_ = uset.hash_;
    return *this;
  }
  UnorderedSet& operator=(UnorderedSet&& uset) {
    v_ = std::move(uset.v_);
    count_bucket_ = uset.count_bucket_;
    count_value_ = uset.count_value_;
    hash_ = std::move(uset.hash_);
    uset.count_bucket_ = 0;
    uset.count_value_ = 0;
    return *this;
  }
  size_t Size() const {
    return count_value_;
  }
  size_t Empty() const {
    return count_value_ == 0;
  }
  void Clear() {
    v_.clear();
    count_bucket_ = count_value_ = 0;
  }
  void Rehash(size_t new_bucket_count) {
    if (new_bucket_count > count_bucket_ || new_bucket_count >= count_value_) {
      std::vector<std::list<KeyT>> buf = std::move(v_);
      for (size_t i = 0; i < new_bucket_count; ++i) {
        v_.push_back(std::list<KeyT>(0));
      }
      count_bucket_ = new_bucket_count;
      hash_ = std::move(std::hash<KeyT>{});
      for (size_t i = 0; i < buf.size(); i++) {
        auto it_first = buf[i].begin();
        auto it_last = buf[i].end();
        while (it_first != it_last) {
          size_t hash = hash_(*it_first) % new_bucket_count;
          auto it1 = v_[hash].begin();
          auto it2 = v_[hash].end();
          bool flag = false;
          while (it1 != it2) {
            if (*it1 == *it_first) {
              flag = true;
              break;
            }
            ++it1;
          }
          if (!flag) {
            v_[hash].push_back(*it_first);
          }
          it_first++;
        }
      }
    }
  }
  bool Find(const KeyT& value) const {
    bool flag = false;
    if (!v_.empty()) {
      auto idx = hash_(value) % count_bucket_;
      auto it1 = v_[idx].begin();
      auto it2 = v_[idx].end();
      while (it1 != it2) {
        if (*it1 == value) {
          flag = true;
          break;
        }
        it1++;
      }
    }
    return flag;
  }
  size_t BucketCount() const {
    return count_bucket_;
  }
  size_t BucketSize(size_t id) const {
    size_t res = 0;
    if (!v_.empty() && id < v_.size()) {
      res = v_[id].size();
    }
    return res;
  }
  size_t Bucket(const KeyT& key) const {
    size_t res = 0;
    if (count_bucket_ != 0) {
      res = hash_(key) % count_bucket_;
    }
    return res;
  }
  double LoadFactor() const {
    double res = 0;
    if (count_bucket_ != 0) {
      res = (count_value_ * 1.0) / (count_bucket_ * 1.0);
    }
    return res;
  }
  void Insert(const KeyT& key) {
    if (count_bucket_ <= count_value_) {
      if (count_bucket_ != 0) {
        Rehash(2 * count_bucket_);
      } else {
        Rehash(1);
      }
    }
    auto id = hash_(key) % count_bucket_;
    if (!Find(key)) {
      v_[id].push_back(key);
    }
    count_value_++;
  }
  void Insert(KeyT&& key) {
    if (count_bucket_ <= count_value_) {
      if (count_bucket_ != 0) {
        Rehash(2 * count_bucket_);
      } else {
        Rehash(1);
      }
    }
    auto id = hash_(key) % count_bucket_;
    if (!Find(key)) {
      v_[id].push_back(std::move(key));
    }
    count_value_++;
  }
  void Erase(const KeyT& key) {
    if (count_value_ != 0) {
      auto id = hash_(key) % count_bucket_;
      auto it_first = v_[id].begin();
      auto it_last = v_[id].end();
      while (it_first != it_last) {
        if (*it_first == key) {
          break;
        }
        ++it_first;
      }
      if (it_first != it_last) {
        v_[id].erase(it_first);
        count_value_--;
      }
    }
  }
  void Reserve(size_t new_bucket_count) {
    if (new_bucket_count > count_bucket_) {
      Rehash(new_bucket_count);
    }
  }
};
