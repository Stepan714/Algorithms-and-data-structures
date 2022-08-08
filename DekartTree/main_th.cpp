#include <iostream>

struct Node {
  int size_;
  int priority_;
  Node* left_;
  Node* right_;
  int value_;
  explicit Node(int value) {
    left_ = right_ = nullptr;
    value_ = value;
    size_ = 1;
    priority_ = rand() % 4343453;
  }
};

void DeleteTree(Node* p) {
  if (p == nullptr) {
    return;
  }
  DeleteTree(p->left_);
  DeleteTree(p->right_);
  delete p;
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

void InorderWalk(Node* boof) {
  if (boof != nullptr) {
    InorderWalk(boof->left_);
    std::cout << boof->value_ << " ";
    InorderWalk(boof->right_);
  }
}

Node* Insert(Node* t, Node* new_node, int k) {
  if (!t) {
    return new_node;
  }
  if (!new_node) {
    return t;
  }
  if (t->priority_ >= new_node->priority_) {
    if (new_node->value_ >= Size(t->left_)) {
      t->right_ = Insert(t->right_, new_node, k - Size(t->left_) - 1);
    } else {
      t->left_ = Insert(t->left_, new_node, k);
    }
    FixNode(t);
    return t;
  }
  std::pair<Node*, Node*> pair = Split(t, k);
  new_node->left_ = pair.first;
  new_node->right_ = pair.second;
  FixNode(new_node);
  return new_node;
}

Node* Rotate(Node* t, int left, int right) {
  auto pair1 = Split(t, right);
  auto pair2 = Split(pair1.first, left - 1);
  return Merge(pair2.second, Merge(pair2.first, pair1.second));
}

int main() {
  Dtree tree;
  tree.root_ = nullptr;
  int n, m;
  std::cin >> n >> m;
  int value = 1;
  while (value != n + 1) {
    tree.root_ = Insert(tree.root_, new Node(value), value);
    value++;
  }
  int left, right;
  while (m != 0) {
    std::cin >> left >> right;
    tree.root_ = Rotate(tree.root_, left, right);
    m--;
  }
  InorderWalk(tree.root_);
  return 0;
}
