#include <bits/stdc++.h>

#include <random>

std::mt19937 random_data(time(nullptr));

class Treap {
 public:
  struct Node;
  void Insert(std::string& key, std::string& value);
  Node* Find(std::string& key);
  Treap() = default;
  ~Treap() { Delete(root_); }

 private:
  Node* root_ = nullptr;
  std::pair<Node*, Node*> Split(Node* root, std::string& key);
  Node* Merge(Node* root_small, Node* root_big);
  Node* Insert(Node* root, std::string& key, std::string& value);
  Node* Find(Node* root, std::string& key);
  void Delete(Node* root);
};

struct Treap::Node {
  std::string key;
  int priority = 0;
  std::string value;
  Node* left = nullptr;
  Node* right = nullptr;
  Node(const std::string& key, const std::string& value)
      : key(key), priority(random_data()), value(value) {}
  Node() = default;
};

void NodePrint(Treap::Node* node) {
  if (node == nullptr) {
    return;
  }
  std::cout << node->value << '\n';
}

int main() {
  Treap treap_keys_is_cars;
  Treap treap_keys_is_racers;
  int number_of_racers;
  std::cin >> number_of_racers;
  for (int i = 0; i < number_of_racers; ++i) {
    std::string racer;
    std::string car;
    std::cin >> racer >> car;
    treap_keys_is_cars.Insert(car, racer);
    treap_keys_is_racers.Insert(racer, car);
  }
  int number_of_request;
  std::cin >> number_of_request;
  for (int i = 0; i < number_of_request; ++i) {
    std::string request;
    std::cin >> request;
    Treap::Node* request_is_car = treap_keys_is_cars.Find(request);
    Treap::Node* request_is_racer = treap_keys_is_racers.Find(request);
    NodePrint(request_is_car);
    NodePrint(request_is_racer);
  }
  return 0;
}

std::pair<Treap::Node*, Treap::Node*> Treap::Split(Treap::Node* root,
                                                   std::string& key) {
  if (root == nullptr) {
    return {nullptr, nullptr};
  }
  if (root->key < key) {
    auto [root_small, root_big] = Split(root->right, key);
    root->right = root_small;
    return {root, root_big};
  }
  auto [root_small, root_big] = Split(root->left, key);
  root->left = root_big;
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
    return root_small;
  }
  root_big->left = Merge(root_small, root_big->left);
  return root_big;
}

Treap::Node* Treap::Insert(Treap::Node* root, std::string& key,
                           std::string& value) {
  auto [root_small, root_big] = Split(root, key);
  Node* new_node = new Node(key, value);
  return Merge(Merge(root_small, new_node), root_big);
}

void Treap::Delete(Treap::Node* root) {
  if (root == nullptr) {
    return;
  }
  Delete(root->left);
  Delete(root->right);
  delete root;
}

Treap::Node* Treap::Find(Node* root, std::string& key) {
  if (root == nullptr) {
    return nullptr;
  }
  if (root->key == key) {
    return root;
  }
  if (root->key > key) {
    return Find(root->left, key);
  }
  return Find(root->right, key);
}

void Treap::Insert(std::string& key, std::string& value) {
  root_ = Insert(root_, key, value);
}

Treap::Node* Treap::Find(std::string& key) { return Find(root_, key); }