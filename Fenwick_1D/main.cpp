#include <iostream>
#include <vector>
#include <string>

template <class FowardIterator>
std::vector<int64_t> inline CountPrefixSums(FowardIterator begin, FowardIterator end) {
  std::vector<int64_t> values(begin, end);
  std::vector<int64_t> result(values.size());
  if (result.empty()) {
    return result;
  }
  result[0] = values[0];
  for (size_t i = 1; i < values.size(); ++i) {
    result[i] = result[i - 1] + values[i];
  }
  return result;
}

class SumRange {
 public:
  template <class FowardIterator>
  SumRange(FowardIterator begin, FowardIterator end) : prefix_sums_(CountPrefixSums(begin, end)) {
  }
  int64_t GetSum(size_t left, size_t right) const noexcept {
    if (left == 0) {
      return prefix_sums_[right];
    }
    return prefix_sums_[right] - prefix_sums_[left - 1];
  }
  size_t Size() const {
    return prefix_sums_.size();
  }

 private:
  const std::vector<int64_t> prefix_sums_;
};

class FenwickTree {
  std::vector<int64_t> ft_;
  int64_t GetPrefixSum(int64_t right) const {
    if (right == 0) {
      return ft_[0];
    }
    int64_t result = 0;
    for (; right >= 0; right = (right & (right + 1)) - 1) {
      result += ft_[right];
    }
    return result;
  }

 public:
  template <class FowardIterator>
  FenwickTree(FowardIterator begin, FowardIterator end) {
    SumRange sr(begin, end);
    ft_ = std::vector<int64_t>(sr.Size());
    for (size_t i = 0; i < ft_.size(); ++i) {
      ft_[i] = sr.GetSum(i & (i + 1), i);
    }
  }
  void Print() const {
    for (auto& i : ft_) {
      std::cout << i << " ";
    }
  }
  int64_t Query(size_t left, size_t right) const {
    return GetPrefixSum(right) - GetPrefixSum(left - 1);
  }
  void Update(size_t k, int64_t delta) {
    for (size_t i = k; i < ft_.size(); i = (i | (i + 1))) {
      ft_[i] += delta;
    }
  }
};

int main() {
  std::vector<int64_t> v;
  size_t n;
  std::cin >> n;
  int64_t value;
  for (size_t i = 0; i < n; ++i) {
    std::cin >> value;
    v.push_back(value);
  }
  FenwickTree tree(v.begin(), v.end());
  size_t size;
  std::cin >> size;
  size_t left, right;
  int64_t new_value;
  for (size_t i = 0; i < size; ++i) {
    std::string a;
    std::cin >> a;
    if (a == "s") {
      std::cin >> left >> right;
      std::cout << tree.Query(left - 1, right - 1) << " ";
    } else if (a == "u") {
      std::cin >> left >> new_value;
      int64_t delta = new_value - v[left - 1];
      tree.Update(left - 1, delta);
      v[left - 1] = new_value;
    }
  }
  return 0;
}
