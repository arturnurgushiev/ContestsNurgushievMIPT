#include <bits/stdc++.h>

#include <random>

std::mt19937 random_data(time(nullptr));

class Treap {
 public:
  struct Node;
  void Insert(int value);
  void Erase(int value);
  Node* Next(int value);
  Node* Prev(int value);
  Node* Kth(int index);
  bool Find(int key);
  Treap() = default;
  ~Treap() { Delete(root_); }

 private:
  Node* root_ = nullptr;
  std::pair<Node*, Node*> Split(Node* root, int value);
  Node* Merge(Node* root_small, Node* root_big);
  Node* Insert(Node* root, int value);
  Node* Erase(Node* root, int value);
  Node* Next(Node* root, int value);
  Node* Prev(Node* root, int value);
  Node* Kth(Node* root, int index, int now);
  static void Update(Node* root);
  static int GetSize(Node* root);
  bool Find(Node* root, int key);
  void Delete(Node* root);
};

struct Treap::Node {
  int key = 0;
  int priority = 0;
  int size = 1;
  Node* left = nullptr;
  Node* right = nullptr;
  Node(int key) : key(key), priority(random_data()) {}
  Node() = default;
};

void NodePrint(Treap::Node* node) {
  if (node == nullptr) {
    std::cout << "none" << '\n';
  } else {
    std::cout << node->key << '\n';
  }
}

int main() {
  Treap treap;
  std::string command;
  while (std::cin >> command) {
    if (command == "insert") {
      int value;
      std::cin >> value;
      treap.Insert(value);
    } else if (command == "delete") {
      int value;
      std::cin >> value;
      treap.Erase(value);
    } else if (command == "exists") {
      int value;
      std::cin >> value;
      if (treap.Find(value)) {
        std::cout << "true" << '\n';
      } else {
        std::cout << "false" << '\n';
      }
    } else if (command == "next") {
      int value;
      std::cin >> value;
      NodePrint(treap.Next(value));
    } else if (command == "prev") {
      int value;
      std::cin >> value;
      NodePrint(treap.Prev(value));
    } else {
      int index;
      std::cin >> index;
      NodePrint(treap.Kth(index));
    }
  }
  return 0;
}

std::pair<Treap::Node*, Treap::Node*> Treap::Split(Treap::Node* root,
                                                   int value) {
  if (root == nullptr) {
    return {nullptr, nullptr};
  }
  if (root->key < value) {
    auto [root_small, root_big] = Split(root->right, value);
    root->right = root_small;
    Update(root);
    return {root, root_big};
  }
  auto [root_small, root_big] = Split(root->left, value);
  root->left = root_big;
  Update(root);
  return {root_small, root};
}

Treap::Node* Treap::Merge(Treap::Node* root_small, Treap::Node* root_big) {
  if (root_small == nullptr) {
    return root_big;
  }
  if (root_big == nullptr) {
    return root_small;
  }
  if (root_small->priority < root_big->priority) {
    root_small->right = Merge(root_small->right, root_big);
    Update(root_small);
    return root_small;
  }
  root_big->left = Merge(root_small, root_big->left);
  Update(root_big);
  return root_big;
}

Treap::Node* Treap::Insert(Treap::Node* root, int value) {
  if (Find(root, value)) {
    return root;
  }
  auto [root_small, root_big] = Split(root, value);
  Node* new_node = new Node(value);
  return Merge(Merge(root_small, new_node), root_big);
}

Treap::Node* Treap::Erase(Treap::Node* root, int value) {
  if (!Find(root, value)) {
    return root;
  }
  auto [root_small, root_equal_big] = Split(root, value);
  auto [root_equal, root_big] = Split(root_equal_big, value + 1);
  delete root_equal;
  return Merge(root_small, root_big);
}

Treap::Node* Treap::Next(Treap::Node* root, int value) {
  if (root == nullptr) {
    return nullptr;
  }
  if (root->key < value) {
    return Next(root->right, value);
  }
  if (root->left == nullptr || root->left->key < value) {
    return root;
  }
  return Next(root->left, value);
}

Treap::Node* Treap::Prev(Treap::Node* root, int value) {
  if (root == nullptr) {
    return nullptr;
  }
  if (root->key > value) {
    return Prev(root->left, value);
  }
  if (root->right == nullptr || root->right->key > value) {
    return root;
  }
  return Prev(root->right, value);
}

Treap::Node* Treap::Kth(Treap::Node* root, int index, int now) {
  if (root == nullptr || GetSize(root->left) + now == index) {
    return root;
  }
  if (GetSize(root->left) + now > index) {
    return Kth(root->left, index, now);
  }
  now += 1 + GetSize(root->left);
  return Kth(root->right, index, now);
}

void Treap::Delete(Treap::Node* root) {
  if (root == nullptr) {
    return;
  }
  Delete(root->left);
  Delete(root->right);
  delete root;
}

void Treap::Update(Treap::Node* root) {
  /*if (root == nullptr) {
    return;
  }*/
  root->size = 1 + GetSize(root->left) + GetSize(root->right);
}

int Treap::GetSize(Treap::Node* root) {
  if (root == nullptr) {
    return 0;
  }
  return root->size;
}

bool Treap::Find(Node* root, int key) {
  if (root == nullptr) {
    return false;
  }
  if (root->key == key) {
    return true;
  }
  if (root->key > key) {
    return Find(root->left, key);
  }
  return Find(root->right, key);
}

void Treap::Insert(int value) { root_ = Insert(root_, value); }

void Treap::Erase(int value) { root_ = Erase(root_, value); }

Treap::Node* Treap::Next(int value) { return Next(root_, value); }

Treap::Node* Treap::Prev(int value) { return Prev(root_, value); }

Treap::Node* Treap::Kth(int index) { return Kth(root_, index, 0); }

bool Treap::Find(int key) { return Find(root_, key); }