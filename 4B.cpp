#include <bits/stdc++.h>

const int kModule = 1e9;

struct Node {
  int value = -1;
  int height = 0;
  Node* left = nullptr;
  Node* right = nullptr;
  void LLPivot() {
    std::swap(value, left->value);
    Node* help_right = right;
    Node* help_left = left;
    Node* left_copy = new Node;
    *left_copy = *left;
    right = left_copy;
    right->left = right->right;
    right->right = help_right;
    left = left->left;
    delete help_left;
  }
  void RRPivot() {
    std::swap(value, right->value);
    Node* help_left = left;
    Node* help_right = right;
    Node* right_copy = new Node;
    *right_copy = *right;
    left = right_copy;
    left->right = left->left;
    left->left = help_left;
    right = right->right;
    delete help_right;
  }
  void LRPivot() {
    left->RRPivot();
    LLPivot();
  }
  void RLPivot() {
    right->LLPivot();
    RRPivot();
  }
  int Delta() const {
    int right_height = -1;
    int left_height = -1;
    if (right != nullptr) {
      right_height = right->height;
    }
    if (left != nullptr) {
      left_height = left->height;
    }
    return right_height - left_height;
  }
};

void Delete(Node* ptr) {
  if (ptr == nullptr) {
    return;
  }
  if (ptr->left != nullptr) {
    Delete(ptr->left);
  }
  if (ptr->right != nullptr) {
    Delete(ptr->right);
  }
  delete ptr;
}

class AVLTree {
 private:
  Node root_;
  int FindMin(Node* node, int find_val) {
    if (node->value < find_val) {
      if (node->right == nullptr) {
        return -1;
      }
      return FindMin(node->right, find_val);
    }
    if (node->left == nullptr) {
      return node->value;
    }
    int try_to_left = FindMin(node->left, find_val);
    if (try_to_left == -1) {
      try_to_left = node->value;
    }
    return try_to_left;
  }
  void Add(Node* node, int insert_number) {
    if (root_.value == -1) {
      root_.value = insert_number;
      return;
    }
    if (node->value == insert_number) {
      return;
    }
    if (insert_number < node->value) {
      if (node->left == nullptr) {
        node->height = std::max(1, node->height);
        node->left = new Node;
        node->left->value = insert_number;
        return;
      }
      Add(node->left, insert_number);
      if (node->Delta() == -2) {
        if (node->left->Delta() <= 0) {
          node->LLPivot();
        } else {
          node->LRPivot();
        }
      }
      if (node->right != nullptr) {
        node->height = std::max(node->left->height + 1, node->right->height);
      } else {
        node->height = node->left->height + 1;
      }
      return;
    }
    if (node->right == nullptr) {
      node->height = std::max(1, node->height);
      node->right = new Node;
      node->right->value = insert_number;
      return;
    }
    Add(node->right, insert_number);
    if (node->Delta() == 2) {
      if (node->right->Delta() >= 0) {
        node->RRPivot();
      } else {
        node->RLPivot();
      }
    }
    if (node->left != nullptr) {
      node->height = std::max(node->right->height + 1, node->left->height);
    } else {
      node->height = node->right->height + 1;
    }
  }

 public:
  int FindMin(int find_val) { return FindMin(&root_, find_val); }
  void Add(int insert_number) { return Add(&root_, insert_number); }
  ~AVLTree() {
    Node* left = root_.left;
    Node* right = root_.right;
    Delete(left);
    Delete(right);
  }
};

int main() {
  AVLTree avl_tree;
  int number_of_request;
  std::cin >> number_of_request;
  int prev = kModule;
  char command;
  for (int i = 0; i < number_of_request; ++i) {
    std::cin >> command;
    if (command == '?') {
      int find_val;
      std::cin >> find_val;
      prev = avl_tree.FindMin(find_val);
      std::cout << prev << '\n';
    } else {
      int insert_number;
      std::cin >> insert_number;
      insert_number = (insert_number + prev) % kModule;
      avl_tree.Add(insert_number);
      prev = kModule;
    }
  }
}