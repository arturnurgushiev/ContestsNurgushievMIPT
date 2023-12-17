#include <iostream>
#include <string>
#include <vector>

class Heap {
 private:
  std::vector<std::pair<long long, int>> heap_;
  std::vector<int> help_to_decrease_key_;
  int size_heap_ = 0;
  void SiftUp(int index) {
    while (index != 0) {
      int parent = (index - 1) / 2;
      if (heap_[parent].first > heap_[index].first) {
        std::swap(help_to_decrease_key_[heap_[parent].second],
                  help_to_decrease_key_[heap_[index].second]);
        std::swap(heap_[parent], heap_[index]);
      }
      index = parent;
    }
  }

  void SiftDown(int index) {
    while (2 * index + 1 < size_heap_) {
      int first_son = 2 * index + 1;
      int min_son = first_son;
      int second_son = 2 * index + 2;
      if (second_son < size_heap_ &&
          heap_[second_son].first < heap_[first_son].first) {
        min_son = second_son;
      }
      if (heap_[min_son] < heap_[index]) {
        std::swap(help_to_decrease_key_[heap_[min_son].second],
                  help_to_decrease_key_[heap_[index].second]);
        std::swap(heap_[min_son], heap_[index]);
      }
      index = min_son;
    }
  }

 public:
  void Insert(int insert_number, int index_of_request) {
    heap_.push_back({insert_number, index_of_request});
    help_to_decrease_key_.resize(index_of_request + 1, size_heap_);
    SiftUp(size_heap_++);
  }

  void ExtractMin() {
    std::swap(help_to_decrease_key_[heap_[size_heap_ - 1].second],
              help_to_decrease_key_[heap_[0].second]);
    std::swap(heap_[--size_heap_], heap_[0]);
    heap_.pop_back();
    SiftDown(0);
  }

  void DecreaseKey(int index_of_insert_request, int delta) {
    heap_[help_to_decrease_key_[index_of_insert_request]].first -= delta;
    SiftUp(help_to_decrease_key_[index_of_insert_request]);
  }

  long long Min() { return heap_[0].first; }
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int number_of_requests;
  std::cin >> number_of_requests;
  Heap heap;
  std::string command;
  int help_number;
  int index_of_insert_request;
  for (int i = 0; i < number_of_requests; ++i) {
    std::cin >> command;
    if (command == "insert") {
      std::cin >> help_number;
      heap.Insert(help_number, i + 1);
    }
    if (command == "getMin") {
      std::cout << heap.Min() << '\n';
    }
    if (command == "extractMin") {
      heap.ExtractMin();
    }
    if (command == "decreaseKey") {
      std::cin >> index_of_insert_request;
      std::cin >> help_number;
      heap.DecreaseKey(index_of_insert_request, help_number);
    }
  }
}
