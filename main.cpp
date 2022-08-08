#include <iostream>
#include <vector>
#include <cmath>

using Table = std::vector<std::vector<std::vector<std::vector<int>>>>;

class SparseTable2D {
  Table table_;

 public:
  explicit SparseTable2D(int n, int m, const std::vector<std::vector<int>>& matrix) {
    std::vector<int> a(m, (1 << 31));
    std::vector<std::vector<int>> b(1 + std::log2(m), a);
    std::vector<std::vector<std::vector<int>>> c(n, b);
    table_ = std::vector<std::vector<std::vector<std::vector<int>>>>(1 + std::log2(n), c);
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        table_[0][i][0][j] = matrix[i][j];
      }
      for (int k = 1; k <= std::log2(m); ++k) {
        for (int d = 0; d + (1 << (k - 1)) < m; ++d) {
          table_[0][i][k][d] = std::min(table_[0][i][k - 1][d], table_[0][i][k - 1][d + (1 << (k - 1))]);
        }
      }
    }
    for (int i = 1; i <= std::log2(n); ++i) {
      for (int j = 0; j < n - (1 << i) + 1; ++j) {
        for (int k = 0; k <= std::log2(m); ++k) {
          for (int l = 0; l < m - (1 << k) + 1; ++l) {
            table_[i][j][k][l] = std::min(table_[i - 1][j][k][l], table_[i - 1][j + (1 << (i - 1))][k][l]);
          }
        }
      }
    }
  }
  int Query(int x1, int y1, int x2, int y2) {
    int x = std::log2(x2 - x1 + 1);
    int y = std::log2(y2 - y1 + 1);
    int min_r1 = std::min(table_[x][x1][y][y1], table_[x][x1][y][y2 - (1 << y) + 1]);
    int min_r2 = std::min(table_[x][x2 - (1 << x) + 1][y][y1], table_[x][x2 - (1 << x) + 1][y][y2 - (1 << y) + 1]);
    return std::min(min_r1, min_r2);
  }
};

int main() {
  int n, m;
  std::cin >> m >> n;
  std::vector<int> a(n, 0);
  std::vector<std::vector<int>> matrix(m, a);
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) {
      std::cin >> matrix[i][j];
    }
  }
  SparseTable2D table(m, n, matrix);
  int count;
  std::cin >> count;
  for (int i = 0; i < count; ++i) {
    int x1, y1, x2, y2;
    std::cin >> x1 >> y1 >> x2 >> y2;
    std::cout << table.Query(x1 - 1, y1 - 1, x2 - 1, y2 - 1) << "\n";
  }
  return 0;
}
