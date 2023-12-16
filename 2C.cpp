#include <deque>
#include <iostream>

class QueueWithPreference {
 private:
  std::deque<int> begin_;
  std::deque<int> end_;

 public:
  void RegularGoblin(int number) {
    end_.push_back(number);
    if (end_.size() > begin_.size()) {
      begin_.push_back(end_.front());
      end_.pop_front();
    }
  }

  int Last() {
    int result = begin_.front();
    begin_.pop_front();
    if (end_.size() > begin_.size()) {
      begin_.push_back(end_.front());
      end_.pop_front();
    }
    return result;
  }

  void PreferenceGoblin(int number) {
    if (begin_.size() == end_.size()) {
      begin_.push_back(number);
    } else {
      end_.push_front(number);
    }
  }
};

int main() {
  QueueWithPreference queue_with_preference;
  int quantity;
  std::cin >> quantity;
  char help;
  int number;
  for (int i = 0; i < quantity; ++i) {
    std::cin >> help;
    if (help == '-') {
      std::cout << queue_with_preference.Last() << '\n';
    } else if (help == '+') {
      std::cin >> number;
      queue_with_preference.RegularGoblin(number);
    } else {
      std::cin >> number;
      queue_with_preference.PreferenceGoblin(number);
    }
  }
}
