#include <iostream>
#include <stack>
#include <string>

class QueueToSolveTheProblem {
 private:
  const int kInf = 2147483647;
  std::stack<int> first_;
  std::stack<int> first_min_;
  std::stack<int> second_;
  std::stack<int> second_min_;
  int size_ = 0;
  void FirstToSecond() {
    while (!first_.empty()) {
      first_min_.pop();
      second_.push(first_.top());
      second_min_.push(std::min(second_min_.top(), first_.top()));
      first_.pop();
    }
  }

 public:
  QueueToSolveTheProblem() {
    first_min_.push(kInf);
    second_min_.push(kInf);
  }

  void Push(int number) {
    ++size_;
    first_.push(number);
    first_min_.push(std::min(first_min_.top(), number));
  }

  int Pop() {
    --size_;
    if (second_.empty()) {
      FirstToSecond();
    }
    int result = second_.top();
    second_.pop();
    second_min_.pop();
    return result;
  }

  int Front() {
    if (second_.empty()) {
      FirstToSecond();
    }
    return second_.top();
  }

  int Size() const { return size_; }

  void Clear() {
    size_ = 0;
    while (!first_.empty()) {
      first_.pop();
      first_min_.pop();
    }
    while (!second_.empty()) {
      second_.pop();
      second_min_.pop();
    }
  }

  int Min() { return std::min(first_min_.top(), second_min_.top()); }
};

int main() {
  QueueToSolveTheProblem queue;
  int quantity;
  int number;
  std::cin >> quantity;
  std::string command;
  for (int i = 0; i < quantity; ++i) {
    std::cin >> command;
    if (command == "enqueue") {
      std::cin >> number;
      queue.Push(number);
      std::cout << "ok" << '\n';
    }
    if (command == "dequeue") {
      if (queue.Size() > 0) {
        std::cout << queue.Pop() << '\n';
      } else {
        std::cout << "error\n";
      }
    }
    if (command == "front") {
      if (queue.Size() > 0) {
        std::cout << queue.Front() << '\n';
      } else {
        std::cout << "error\n";
      }
    }
    if (command == "size") {
      std::cout << queue.Size() << '\n';
    }
    if (command == "clear") {
      queue.Clear();
      std::cout << "ok" << '\n';
    }
    if (command == "min") {
      if (queue.Size() > 0) {
        std::cout << queue.Min() << '\n';
      } else {
        std::cout << "error\n";
      }
    }
  }
}
