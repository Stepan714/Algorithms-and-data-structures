#include <iostream>
#include <vector>
#include <cmath>

size_t Left(size_t i) {
  return 2 * i + 1;
}
size_t Right(size_t i) {
  return 2 * i + 2;
}

class SegmentTree {
  std::vector<std::pair<int, int>> tree_;
  size_t size_;

 public:
  explicit SegmentTree(std::vector<int>& v) {
    size_t size = v.size();
    size_t res = 0;
    while (size != 0) {
      res += size;
      size /= 2;
    }
    tree_.resize(res, {-1, 0});
    size_ = res;
    for (size_t i = 0; i < v.size(); ++i) {
      tree_[i + v.size() - 1] = std::pair(v[i], 0);
    }
    for (int i = v.size() - 2; i >= 0; --i) {
      tree_[i].first = std::max(tree_[Left(i)].first, tree_[Right(i)].first);
      tree_[i].second = 0;
    }
  }
  void Push(int node) {
    tree_[node].first += tree_[node].second;
    tree_[Left(node)].second += tree_[node].second;
    tree_[Right(node)].second += tree_[node].second;
    tree_[node].second = 0;
  }
  int Query(int left, int right, int node = 0, int a = 0, int b = 0) {
    if (left <= a && b <= right) {
      return tree_[node].first + tree_[node].second;
    }
    if (a > right || b < left) {
      return 0;
    }
    Push(node);
    auto left_res = Query(left, right, Left(node), a, (a + b) / 2);
    auto right_res = Query(left, right, Right(node), (a + b) / 2 + 1, b);
    return std::max(left_res, right_res);
  }
  void Update(int left, int right, int node = 0, int a = 0, int b = 0, int delta = 0) {
    if (left <= a && b <= right) {
      tree_[node].second += delta;
      return;
    }
    if (a > right || b < left) {
      return;
    }
    Push(node);
    Update(left, right, Left(node), a, (a + b) / 2, delta);
    Update(left, right, Right(node), (a + b) / 2 + 1, b, delta);
    tree_[node].first = std::max(tree_[Left(node)].first + tree_[Left(node)].second,
                                 tree_[Right(node)].first + tree_[Right(node)].second);
  }
};

int main() {
  int n;
  std::cin >> n;
  std::vector<int> v(n, 0);
  for (int i = 0; i < n; ++i) {
    int value;
    std::cin >> value;
    v[i] = value;
  }
  int k = static_cast<int>(std::log2(v.size() - 1)) + 1;
  auto size = static_cast<size_t>((1 << k));
  size_t a = v.size();
  for (size_t i = a; i < size; ++i) {
    v.emplace_back(-1);
  }
  SegmentTree tree(v);
  int w;
  std::cin >> w;
  while (w != 0) {
    char a;
    std::cin >> a;
    if (a == 'm') {
      int x, y;
      std::cin >> x >> y;
      auto t = tree.Query(x - 1, y - 1, 0, 0, v.size() - 1);
      std::cout << t << " ";
    }
    if (a == 'a') {
      int x, y, delta;
      std::cin >> x >> y >> delta;
      tree.Update(x - 1, y - 1, 0, 0, v.size() - 1, delta);
    }
    w--;
  }
  return 0;
}
