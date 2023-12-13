#include <iostream>
#include <stack>
#include <vector>

struct Node {
  int key = 0;
  int priority = 0;
  int number = 0;
  int left = 0;
  int right = 0;
  int parent = 0;
  Node(int key, int priority, int number)
      : key(key), priority(priority), number(number) {}
  Node() : Node(0, 0, 0) {}
};

int main() {
  int number_of_nodes;
  std::cin >> number_of_nodes;
  std::vector<Node> nodes(number_of_nodes + 1);
  for (int i = 1; i <= number_of_nodes; ++i) {
    int key;
    int priority;
    std::cin >> key >> priority;
    nodes[i] = {key, priority, i + 1};
  }
  std::cout << "YES\n";
  std::stack<int> right_way;
  right_way.push(1);
  for (int i = 2; i <= number_of_nodes; ++i) {
    if (nodes[right_way.top()].priority < nodes[i].priority) {
      nodes[right_way.top()].right = i;
      nodes[i].parent = nodes[right_way.top()].number - 1;
      right_way.push(i);
      continue;
    }
    int last_one;
    while (!right_way.empty() &&
           nodes[right_way.top()].priority > nodes[i].priority) {
      last_one = right_way.top();
      right_way.pop();
    }
    if (right_way.empty()) {
      nodes[i].left = last_one;
      nodes[last_one].parent = i;
    } else {
      nodes[i].parent = right_way.top();
      nodes[right_way.top()].right = i;
      nodes[i].left = last_one;
      nodes[last_one].parent = i;
    }
    right_way.push(i);
  }
  for (int i = 1; i <= number_of_nodes; ++i) {
    std::cout << nodes[i].parent << ' ' << nodes[i].left << ' '
              << nodes[i].right << '\n';
  }
}
