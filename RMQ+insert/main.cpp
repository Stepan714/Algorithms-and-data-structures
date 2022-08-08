#include <iostream>

struct Node {
  int key_;
  int priority_;
  Node* left_;
  Node* right_;
  int result_;
  int size_;
};

void DeleteTree(Node* p) {
  if (p == nullptr) {
    return;
  }
  DeleteTree(p->left_);
  DeleteTree(p->right_);
  delete p;
}

int Result(Node* node) {
  if (node != nullptr) {
    return node->result_;
  }
  return 999999999;
}

class Dtree {
 public:
  Node* root_;
  Dtree() : root_(nullptr) {
  }
  ~Dtree() {
    DeleteTree(root_);
  }
};

int Size(Node* t) {
  if (t != nullptr) {
    return t->size_;
  }
  return 0;
}

void FixNode(Node* node) {
  if (node != nullptr) {
    node->size_ = 1 + Size(node->left_) + Size(node->right_);
    node->result_ = std::min(std::min(Result(node->right_), node->key_), Result(node->left_));
  }
}

Node* Merge(Node* t1, Node* t2) {
  if (t1 == nullptr) {
    return t2;
  }
  if (t2 == nullptr) {
    return t1;
  }
  if (t1->priority_ < t2->priority_) {
    t1->right_ = Merge(t1->right_, t2);
    FixNode(t1);
    return t1;
  }
  t2->left_ = Merge(t1, t2->left_);
  FixNode(t2);
  return t2;
}

std::pair<Node*, Node*> Split(Node* t, int size) {
  if (t == nullptr) {
    return {nullptr, nullptr};
  }
  if (Size(t->left_) < size) {
    std::pair<Node*, Node*> pair = Split(t->right_, size - Size(t->left_) - 1);
    t->right_ = pair.first;
    FixNode(t);
    return std::make_pair(t, pair.second);
  }
  std::pair<Node*, Node*> pair2 = Split(t->left_, size);
  t->left_ = pair2.second;
  FixNode(t);
  return std::make_pair(pair2.first, t);
}

Node* Insert(Node*& t, int idx, int value) {
  std::pair<Node*, Node*> pair = Split(t, idx);
  return Merge(Merge(pair.first, new Node{value, rand() % 6165116, nullptr, nullptr, value, 1}), pair.second);
}

int Query(Dtree& t, int left, int right) {
  auto pair1 = Split(t.root_, left);
  auto pair2 = Split(pair1.second, right - left);
  int result = Result(pair2.first);
  t.root_ = Merge(Merge(pair1.first, pair2.first), pair2.second);
  return result;
}

int main() {
  Dtree tree;
  tree.root_ = nullptr;
  int n;
  std::cin >> n;
  for (int i = 0; i < n; ++i) {
    std::string s;
    std::cin >> s;
    if (s == "+") {
      int value, idx;
      std::cin >> idx >> value;
      tree.root_ = Insert(tree.root_, idx, value);
    }
    if (s == "?") {
      int left, right;
      std::cin >> left >> right;
      std::cout << Query(tree, left - 1, right) << "\n";
    }
  }
  return 0;
}
