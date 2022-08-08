#include <iostream>
#include <vector>

class FenwickTree {
  std::vector<std::vector<std::vector<int>>> ft_;
  int n_;
  int GetPrefixSum(int x, int y, int z) const {
    int result = 0;
    for (int i = x; i >= 0; i = (i & (i + 1)) - 1) {
      for (int j = y; j >= 0; j = (j & (j + 1)) - 1) {
        for (int k = z; k >= 0; k = (k & (k + 1)) - 1) {
          result += ft_[i][j][k];
        }
      }
    }
    return result;
  }

 public:
  explicit FenwickTree(int n) {
    n_ = n;
    std::vector<int> a(n, 0);
    std::vector<std::vector<int>> b(n, a);
    ft_ = std::move(std::vector<std::vector<std::vector<int>>>(n, b));
  }
  void Print() const {
    for (auto& i : ft_) {
      for (auto& j : i) {
        for (auto& k : j) {
          std::cout << k << " ";
        }
      }
    }
  }
  int Query(int x1, int y1, int z1, int x2, int y2, int z2) const {
    int value1 = GetPrefixSum(x2, y2, z2) - GetPrefixSum(x1 - 1, y2, z2) - GetPrefixSum(x2, y1 - 1, z2) +
                 GetPrefixSum(x1 - 1, y1 - 1, z2);
    value1 -= (GetPrefixSum(x2, y2, z1 - 1) - GetPrefixSum(x1 - 1, y2, z1 - 1) - GetPrefixSum(x2, y1 - 1, z1 - 1) +
               GetPrefixSum(x1 - 1, y1 - 1, z1 - 1));
    return value1;
  }
  void Update(int x, int y, int z, int delta) {
    for (int i = x; i < n_; i = (i | (i + 1))) {
      for (int j = y; j < n_; j = (j | (j + 1))) {
        for (int d = z; d < n_; d = (d | (d + 1))) {
          ft_[i][j][d] += delta;
        }
      }
    }
  }
};

int main() {
  int n;
  std::cin >> n;
  FenwickTree tree(n);
  int value_comand;
  std::cin >> value_comand;
  while (value_comand != 3) {
    if (value_comand == 1) {
      int i, j, k;
      int a;
      std::cin >> i >> j >> k >> a;
      tree.Update(i, j, k, a);
    }
    if (value_comand == 2) {
      int x1, y1, z1, x2, y2, z2;
      std::cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2;
      std::cout << tree.Query(x1, y1, z1, x2, y2, z2) << "\n";
    }
    std::cin >> value_comand;
  }
  return 0;
}
