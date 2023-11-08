#include <deque>
#include <iostream>

std::deque<int> begin;
std::deque<int> end;

void RegularGoblin(int number) {
  end.push_back(number);
  if (end.size() > begin.size()) {
    begin.push_back(end.front());
    end.pop_front();
  }
}

void PrintLast() {
  std::cout << begin.front() << '\n';
  begin.pop_front();
  if (end.size() > begin.size()) {
    begin.push_back(end.front());
    end.pop_front();
  }
}

void PreferenceGoblin(int number) {
  if (begin.size() == end.size()) {
    begin.push_back(number);
  } else {
    end.push_front(number);
  }
}

int main() {
  int quantity;
  std::cin >> quantity;
  char help;
  int number;
  for (int i = 0; i < quantity; ++i) {
    std::cin >> help;
    if (help == '-') {
      PrintLast();
    } else if (help == '+') {
      std::cin >> number;
      RegularGoblin(number);
    } else {
      std::cin >> number;
      PreferenceGoblin(number);
    }
  }
}