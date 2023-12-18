#include <iostream>
#include <string>
#include <vector>

class HeapMinMax {
 private:
  std::vector<std::pair<int, int>> min_heap_;
  std::vector<std::pair<int, int>> max_heap_;
  std::vector<int> help_to_decrease_key_;
  std::vector<int> help_to_increase_key_;
  int size_heap_ = 0;

  static void SiftUp(std::vector<std::pair<int, int>>& heap,
                     std::vector<int>& help, int index, bool is_min_heap) {
    while (index != 0) {
      int parent = (index - 1) / 2;
      if ((is_min_heap && heap[parent].first <= heap[index].first) ||
          (!is_min_heap && heap[parent].first >= heap[index].first)) {
        break;
      }
      std::swap(help[heap[parent].second], help[heap[index].second]);
      std::swap(heap[parent], heap[index]);
      index = parent;
    }
  }

  void SiftDown(std::vector<std::pair<int, int>>& heap, std::vector<int>& help,
                int index, bool is_min_heap) const {
    while (2 * index + 1 < size_heap_) {
      int first_son = 2 * index + 1;
      int change_son = first_son;
      int second_son = 2 * index + 2;
      if (second_son < size_heap_) {
        if ((is_min_heap && heap[second_son].first < heap[first_son].first) ||
            (!is_min_heap && heap[second_son].first > heap[first_son].first)) {
          change_son = second_son;
        }
      }
      if ((is_min_heap && heap[change_son] >= heap[index]) ||
          (!is_min_heap && heap[change_son] <= heap[index])) {
        break;
      }
      std::swap(help[heap[change_son].second], help[heap[index].second]);
      std::swap(heap[change_son], heap[index]);
      index = change_son;
    }
  }

  void SiftUpMinHeap(int index) {
    SiftUp(min_heap_, help_to_decrease_key_, index, true);
  }

  void SiftDownMinHeap(int index) {
    SiftDown(min_heap_, help_to_decrease_key_, index, true);
  }

  void SiftUpMaxHeap(int index) {
    SiftUp(max_heap_, help_to_increase_key_, index, false);
  }

  void SiftDownMaxHeap(int index) {
    SiftDown(max_heap_, help_to_increase_key_, index, false);
  }

  void ExtractHelp(std::vector<std::pair<int, int>>& heap,
                   std::vector<int>& help, bool is_min_heap) {
    std::swap(help[heap[size_heap_ - 1].second], help[heap[0].second]);
    std::swap(heap[--size_heap_], heap[0]);
    heap.pop_back();
    if (is_min_heap) {
      SiftDownMinHeap(0);
    } else {
      SiftDownMaxHeap(0);
    }
    ++size_heap_;
  }

  void InsertHelp(std::vector<std::pair<int, int>>& heap,
                  std::vector<int>& help, int insert_number,
                  int index_of_request, bool is_min_heap) {
    heap.push_back({insert_number, index_of_request});
    help.resize(1 + index_of_request, size_heap_);
    if (is_min_heap) {
      SiftUpMinHeap(size_heap_);
    } else {
      SiftUpMaxHeap(size_heap_);
    }
  }

  void ChangeKeyHelp(std::vector<std::pair<int, int>>& heap,
                     std::vector<int>& help, int index_of_insert_request,
                     int delta, bool is_min_heap) {
    if (is_min_heap) {
      delta = -delta;
    }
    heap[help[index_of_insert_request]].first += delta;
    if (is_min_heap) {
      SiftUpMinHeap(help[index_of_insert_request]);
    } else {
      SiftUpMaxHeap(help[index_of_insert_request]);
    }
  }
  void InsertMinHeap(int insert_number, int index_of_request) {
    InsertHelp(min_heap_, help_to_decrease_key_, insert_number,
               index_of_request, true);
  }

  void ExtractMinHeap() { ExtractHelp(min_heap_, help_to_decrease_key_, true); }

  void DecreaseKey(int index_of_insert_request, int delta) {
    ChangeKeyHelp(min_heap_, help_to_decrease_key_, index_of_insert_request,
                  delta, true);
  }

  void InsertMaxHeap(int insert_number, int index_of_request) {
    InsertHelp(max_heap_, help_to_increase_key_, insert_number,
               index_of_request, false);
  }

  void ExtractMaxHeap() {
    ExtractHelp(max_heap_, help_to_increase_key_, false);
  }

  void IncreaseKey(int index_of_insert_request, int delta) {
    ChangeKeyHelp(max_heap_, help_to_increase_key_, index_of_insert_request,
                  delta, false);
  }

  int Extract(std::vector<std::pair<int, int>>& heap, bool is_min_heap) {
    int result = heap[0].first;
    const int kInf = 1e9;
    if (is_min_heap) {
      IncreaseKey(heap[0].second, kInf);
    } else {
      DecreaseKey(heap[0].second, kInf);
    }
    ExtractMinHeap();
    ExtractMaxHeap();
    --size_heap_;
    return result;
  }

 public:
  void Insert(int insert_number, int index_of_request) {
    InsertMaxHeap(insert_number, index_of_request + 1);
    InsertMinHeap(insert_number, index_of_request + 1);
    ++size_heap_;
  }

  int ExtractMin() { return Extract(min_heap_, true); }

  int ExtractMax() { return Extract(max_heap_, false); }

  void Clear() {
    size_heap_ = 0;
    min_heap_.resize(0);
    max_heap_.resize(0);
  }

  int GetMin() { return min_heap_[0].first; }

  int GetMax() { return max_heap_[0].first; }

  int Size() const { return size_heap_; }
};

void Solve(HeapMinMax& min_max_heap, const std::string& command, int index) {
  if (command != "clear" && command != "size" && command != "insert" &&
      min_max_heap.Size() == 0) {
    std::cout << "error\n";
    return;
  }
  if (command == "insert") {
    int insert_number;
    std::cin >> insert_number;
    min_max_heap.Insert(insert_number, index + 1);
    std::cout << "ok" << '\n';
  }
  if (command == "extract_min") {
    std::cout << min_max_heap.ExtractMin() << '\n';
  }
  if (command == "extract_max") {
    std::cout << min_max_heap.ExtractMax() << '\n';
  }
  if (command == "get_min") {
    std::cout << min_max_heap.GetMin() << '\n';
  }
  if (command == "get_max") {
    std::cout << min_max_heap.GetMax() << '\n';
  }
  if (command == "size") {
    std::cout << min_max_heap.Size() << '\n';
  }
  if (command == "clear") {
    min_max_heap.Clear();
    std::cout << "ok" << '\n';
  }
  std::cout << std::flush;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int number_of_request;
  std::cin >> number_of_request;
  std::string command;
  HeapMinMax min_max_heap;
  for (int i = 0; i < number_of_request; ++i) {
    std::cin >> command;
    Solve(min_max_heap, command, i);
  }
  return 0;
}
