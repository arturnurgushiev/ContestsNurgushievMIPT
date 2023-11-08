#include <iostream>
#include <stack>
#include <string>

const int kInf = 2147483647;
std::stack<int> first;
std::stack<int> first_min;
std::stack<int> second;
std::stack<int> second_min;
int size = 0;

void FirstToSecond() {
  while (!first.empty()) {
    first_min.pop();
    second.push(first.top());
    second_min.push(std::min(second_min.top(), first.top()));
    first.pop();
  }
}

void Push(int number) {
  ++size;
  first.push(number);
  first_min.push(std::min(first_min.top(), number));
  std::cout << "ok" << '\n';
}

void Pop() {
  if (size == 0) {
    std::cout << "error" << '\n';
    return;
  }
  --size;
  if (second.empty()) {
    FirstToSecond();
  }
  std::cout << second.top() << '\n';
  second.pop();
  second_min.pop();
}

void Front() {
  if (size == 0) {
    std::cout << "error" << '\n';
    return;
  }
  if (second.empty()) {
    FirstToSecond();
  }
  std::cout << second.top() << '\n';
}

void Size() { std::cout << size << '\n'; }

void Clear() {
  size = 0;
  while (!first.empty()) {
    first.pop();
    first_min.pop();
  }
  while (!second.empty()) {
    second.pop();
    second_min.pop();
  }
  std::cout << "ok" << '\n';
}

void Min() {
  if (size == 0) {
    std::cout << "error" << '\n';
    return;
  }
  std::cout << std::min(first_min.top(), second_min.top()) << '\n';
}

void NotPush(const std::string& command) {
  if (command == "dequeue") {
    Pop();
  }
  if (command == "front") {
    Front();
  }
  if (command == "size") {
    Size();
  }
  if (command == "clear") {
    Clear();
  }
  if (command == "min") {
    Min();
  }
}

int main() {
  first_min.push(kInf);
  second_min.push(kInf);
  int quantity;
  int number;
  std::cin >> quantity;
  std::string command;
  for (int i = 0; i < quantity; ++i) {
    std::cin >> command;
    if (command == "enqueue") {
      std::cin >> number;
      Push(number);
    } else {
      NotPush(command);
    }
  }
}