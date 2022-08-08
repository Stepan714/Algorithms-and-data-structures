#include <iostream>
#include <vector>
#include <algorithm>

struct Node {
  int key_;
  int priority_;
  Node* left_;
  Node* right_;
  Node* parent_;
  int index_;
};

void DeleteTree(Node* p) {
  if (p == nullptr) {
    return;
  }
  DeleteTree(p->left_);
  DeleteTree(p->right_);
  delete p;
}

struct Dtree {
  Node* root_;
  ~Dtree() {
    DeleteTree(root_);
  }
};

Node* Build(std::vector<std::pair<int, int>>& a) {
  Node* root = nullptr;
  Node* last_inserted = nullptr;
  int k = 1;
  for (auto& pair : a) {
    Node* cur = last_inserted;
    auto node = new Node{pair.first, pair.second, nullptr, nullptr, nullptr, k};
    while (cur && pair.second < cur->priority_) {
      cur = cur->parent_;
    }
    if (!cur) {
      node->left_ = root;
      if (root) {
        root->parent_ = node;
      }
      root = node;
    } else {
      node->left_ = cur->right_;
      if (cur->right_) {
        cur->right_->parent_ = node;
      }
      cur->right_ = node;
      node->parent_ = cur;
    }
    last_inserted = node;
    k++;
  }
  return root;
}

void InorderWalk(Node* boof) {
  if (boof != nullptr) {
    InorderWalk(boof->left_);
    std::cout << ((boof->parent_ != nullptr) ? boof->parent_->index_ : 0) << " "
              << ((boof->left_ != nullptr) ? boof->left_->index_ : 0) << " "
              << ((boof->right_ != nullptr) ? boof->right_->index_ : 0) << "\n";
    InorderWalk(boof->right_);
  }
}

int main() {
  int n;
  std::cin >> n;
  std::vector<std::pair<int, int>> vector(n, {0, 0});
  for (int i = 0; i < n; ++i) {
    std::pair<int, int> pair;
    int x, y;
    std::cin >> x >> y;
    pair.first = x;
    pair.second = y;
    vector[i] = pair;
  }
  Dtree tree;
  tree.root_ = Build(vector);
  std::cout << "YES\n";
  InorderWalk(tree.root_);
  return 0;
}
