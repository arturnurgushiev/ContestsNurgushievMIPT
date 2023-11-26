#include <iostream>
#include <string>
#include <vector>

class HeapMinMax {
 public:
  std::vector<std::pair<int, int>> min_heap;
  std::vector<std::pair<int, int>> max_heap;
  std::vector<int> help_to_decrease_key;
  std::vector<int> help_to_increase_key;
  int size_heap = 0;

  void SiftUpMinHeap(int index) {
    while (index != 0) {
      int parent = (index - 1) / 2;
      if (min_heap[parent].first <= min_heap[index].first) {
        break;
      }
      std::swap(help_to_decrease_key[min_heap[parent].second],
                help_to_decrease_key[min_heap[index].second]);
      std::swap(min_heap[parent], min_heap[index]);
      index = parent;
    }
  }

  void SiftDownMinHeap(int index) {
    while (2 * index + 1 < size_heap) {
      int first_son = 2 * index + 1;
      int min_son = first_son;
      int second_son = 2 * index + 2;
      if (second_son < size_heap &&
          min_heap[second_son].first < min_heap[first_son].first) {
        min_son = second_son;
      }
      if (min_heap[min_son] >= min_heap[index]) {
        break;
      }
      std::swap(help_to_decrease_key[min_heap[min_son].second],
                help_to_decrease_key[min_heap[index].second]);
      std::swap(min_heap[min_son], min_heap[index]);
      index = min_son;
    }
  }

  void InsertMinHeap(int insert_number, int index_of_request) {
    min_heap.push_back({insert_number, index_of_request});
    help_to_decrease_key[index_of_request] = size_heap;
    SiftUpMinHeap(size_heap);
  }

  void ExtractMin() {
    std::swap(help_to_decrease_key[min_heap[size_heap - 1].second],
              help_to_decrease_key[min_heap[0].second]);
    std::swap(min_heap[size_heap - 1], min_heap[0]);
    min_heap.pop_back();
    --size_heap;
    SiftDownMinHeap(0);
  }

  void DecreaseKey(int index_of_insert_request, int delta) {
    min_heap[help_to_decrease_key[index_of_insert_request]].first -= delta;
    SiftUpMinHeap(help_to_decrease_key[index_of_insert_request]);
  }

  void SiftUpMaxHeap(int index) {
    while (index != 0) {
      int parent = (index - 1) / 2;
      if (max_heap[parent].first >= max_heap[index].first) {
        break;
      }
      std::swap(help_to_increase_key[max_heap[parent].second],
                help_to_increase_key[max_heap[index].second]);
      std::swap(max_heap[parent], max_heap[index]);
      index = parent;
    }
  }

  void SiftDownMaxHeap(int index) {
    while (2 * index + 1 < size_heap) {
      int first_son = 2 * index + 1;
      int max_son = first_son;
      int second_son = 2 * index + 2;
      if (second_son < size_heap &&
          max_heap[second_son].first > max_heap[first_son].first) {
        max_son = second_son;
      }
      if (max_heap[max_son] <= max_heap[index]) {
        break;
      }
      std::swap(help_to_increase_key[max_heap[max_son].second],
                help_to_increase_key[max_heap[index].second]);
      std::swap(max_heap[max_son], max_heap[index]);
      index = max_son;
    }
  }

  void InsertMaxHeap(int insert_number, int index_of_request) {
    max_heap.push_back({insert_number, index_of_request});
    help_to_increase_key[index_of_request] = size_heap;
    SiftUpMaxHeap(size_heap);
  }

  void ExtractMax() {
    std::swap(help_to_increase_key[max_heap[size_heap - 1].second],
              help_to_increase_key[max_heap[0].second]);
    std::swap(max_heap[size_heap - 1], max_heap[0]);
    max_heap.pop_back();
    --size_heap;
    SiftDownMaxHeap(0);
  }

  void IncreaseKey(int index_of_insert_request, int delta) {
    max_heap[help_to_increase_key[index_of_insert_request]].first += delta;
    SiftUpMaxHeap(help_to_increase_key[index_of_insert_request]);
  }

  void ExtractMinInProgram() {
    if (size_heap == 0) {
      std::cout << "error" << '\n';
    } else {
      std::cout << min_heap[0].first << '\n';
      const int kInf = 1e9;
      IncreaseKey(min_heap[0].second, kInf);
      ExtractMax();
      ++size_heap;
      ExtractMin();
    }
  }

  void ExtractMaxInProgram() {
    if (size_heap == 0) {
      std::cout << "error" << '\n';
    } else {
      std::cout << max_heap[0].first << '\n';
      const int kInf = 1e9;
      DecreaseKey(max_heap[0].second, kInf);
      ExtractMin();
      ++size_heap;
      ExtractMax();
    }
  }

  void GetMin() {
    if (size_heap == 0) {
      std::cout << "error" << '\n';
    } else {
      std::cout << min_heap[0].first << '\n';
    }
  }

  void GetMax() {
    if (size_heap == 0) {
      std::cout << "error" << '\n';
    } else {
      std::cout << max_heap[0].first << '\n';
    }
  }
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int number_of_request;
  std::cin >> number_of_request;
  std::string command;
  HeapMinMax min_max_heap;
  min_max_heap.help_to_decrease_key.resize(number_of_request + 1, 0);
  min_max_heap.help_to_increase_key.resize(number_of_request + 1, 0);
  int insert_number;
  for (int i = 0; i < number_of_request; ++i) {
    std::cin >> command;
    if (command == "insert") {
      std::cin >> insert_number;
      min_max_heap.InsertMaxHeap(insert_number, i + 1);
      min_max_heap.InsertMinHeap(insert_number, i + 1);
      ++min_max_heap.size_heap;
      std::cout << "ok" << '\n';
    }
    if (command == "extract_min") {
      min_max_heap.ExtractMinInProgram();
    }
    if (command == "extract_max") {
      min_max_heap.ExtractMaxInProgram();
    }
    if (command == "get_min") {
      min_max_heap.GetMin();
    }
    if (command == "get_max") {
      min_max_heap.GetMax();
    }
    if (command == "size") {
      std::cout << min_max_heap.size_heap << '\n';
    }
    if (command == "clear") {
      min_max_heap.size_heap = 0;
      min_max_heap.min_heap.resize(0);
      min_max_heap.max_heap.resize(0);
      std::cout << "ok" << '\n';
    }
  }
  return 0;
}
