#include <iostream>
#include <string>
#include <vector>

std::vector<int> help_to_decrease_key;
std::vector<int> help_to_increase_key;

void SiftUpMinHeap(std::vector<std::pair<int, int>>& heap, int index) {
  while (index != 0) {
    int parent = (index - 1) / 2;
    if (heap[parent].first <= heap[index].first) {
      break;
    }
    std::swap(help_to_decrease_key[heap[parent].second],
              help_to_decrease_key[heap[index].second]);
    std::swap(heap[parent], heap[index]);
    index = parent;
  }
}

void SiftDownMinHeap(std::vector<std::pair<int, int>>& heap, int index,
                     int size_heap) {
  while (2 * index + 1 < size_heap) {
    int first_son = 2 * index + 1;
    int min_son = first_son;
    int second_son = 2 * index + 2;
    if (second_son < size_heap &&
        heap[second_son].first < heap[first_son].first) {
      min_son = second_son;
    }
    if (heap[min_son] >= heap[index]) {
      break;
    }
    std::swap(help_to_decrease_key[heap[min_son].second],
              help_to_decrease_key[heap[index].second]);
    std::swap(heap[min_son], heap[index]);
    index = min_son;
  }
}

void InsertMinHeap(std::vector<std::pair<int, int>>& heap, int insert_number,
                   int size_heap, int index_of_request) {
  heap.push_back({0, 0});
  heap[size_heap].first = insert_number;
  heap[size_heap].second = index_of_request;
  help_to_decrease_key[index_of_request] = size_heap;
  SiftUpMinHeap(heap, size_heap);
}

void ExtractMin(std::vector<std::pair<int, int>>& heap, int size_heap) {
  std::swap(help_to_decrease_key[heap[size_heap - 1].second],
            help_to_decrease_key[heap[0].second]);
  std::swap(heap[size_heap - 1], heap[0]);
  heap.pop_back();
  SiftDownMinHeap(heap, 0, size_heap - 1);
}

void DecreaseKey(std::vector<std::pair<int, int>>& heap,
                 int index_of_insert_request, int delta) {
  heap[help_to_decrease_key[index_of_insert_request]].first -= delta;
  SiftUpMinHeap(heap, help_to_decrease_key[index_of_insert_request]);
}

void SiftUpMaxHeap(std::vector<std::pair<int, int>>& heap, int index) {
  while (index != 0) {
    int parent = (index - 1) / 2;
    if (heap[parent].first >= heap[index].first) {
      break;
    }
    std::swap(help_to_increase_key[heap[parent].second],
              help_to_increase_key[heap[index].second]);
    std::swap(heap[parent], heap[index]);
    index = parent;
  }
}

void SiftDownMaxHeap(std::vector<std::pair<int, int>>& heap, int index,
                     int size_heap) {
  while (2 * index + 1 < size_heap) {
    int first_son = 2 * index + 1;
    int max_son = first_son;
    int second_son = 2 * index + 2;
    if (second_son < size_heap &&
        heap[second_son].first > heap[first_son].first) {
      max_son = second_son;
    }
    if (heap[max_son] <= heap[index]) {
      break;
    }
    std::swap(help_to_increase_key[heap[max_son].second],
              help_to_increase_key[heap[index].second]);
    std::swap(heap[max_son], heap[index]);
    index = max_son;
  }
}

void InsertMaxHeap(std::vector<std::pair<int, int>>& heap, int insert_number,
                   int size_heap, int index_of_request) {
  heap.push_back({0, 0});
  heap[size_heap].first = insert_number;
  heap[size_heap].second = index_of_request;
  help_to_increase_key[index_of_request] = size_heap;
  SiftUpMaxHeap(heap, size_heap);
}

void ExtractMax(std::vector<std::pair<int, int>>& heap, int size_heap) {
  std::swap(help_to_increase_key[heap[size_heap - 1].second],
            help_to_increase_key[heap[0].second]);
  std::swap(heap[size_heap - 1], heap[0]);
  heap.pop_back();
  SiftDownMaxHeap(heap, 0, size_heap - 1);
}

void IncreaseKey(std::vector<std::pair<int, int>>& heap,
                 int index_of_insert_request, int delta) {
  heap[help_to_increase_key[index_of_insert_request]].first += delta;
  SiftUpMaxHeap(heap, help_to_increase_key[index_of_insert_request]);
}

void ExtractMinInProgram(std::vector<std::pair<int, int>>& min_heap,
                         std::vector<std::pair<int, int>>& max_heap,
                         int& size_heap) {
  if (size_heap == 0) {
    std::cout << "error" << '\n';
  } else {
    std::cout << min_heap[0].first << '\n';
    const int kInf = 1e9;
    IncreaseKey(max_heap, min_heap[0].second, kInf);
    ExtractMax(max_heap, size_heap);
    ExtractMin(min_heap, size_heap);
    --size_heap;
  }
}

void ExtractMaxInProgram(std::vector<std::pair<int, int>>& max_heap,
                         std::vector<std::pair<int, int>>& min_heap,
                         int& size_heap) {
  if (size_heap == 0) {
    std::cout << "error" << '\n';
  } else {
    std::cout << max_heap[0].first << '\n';
    const int kInf = 1e9;
    DecreaseKey(min_heap, max_heap[0].second, kInf);
    ExtractMin(min_heap, size_heap);
    ExtractMax(max_heap, size_heap);
    --size_heap;
  }
}

void GetMin(std::vector<std::pair<int, int>>& min_heap, int size_heap) {
  if (size_heap == 0) {
    std::cout << "error" << '\n';
  } else {
    std::cout << min_heap[0].first << '\n';
  }
}

void GetMax(std::vector<std::pair<int, int>>& max_heap, int size_heap) {
  if (size_heap == 0) {
    std::cout << "error" << '\n';
  } else {
    std::cout << max_heap[0].first << '\n';
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  std::cout.tie(0);
  int number_of_request;
  std::cin >> number_of_request;
  std::string command;
  help_to_decrease_key.resize(number_of_request + 1, 0);
  help_to_increase_key.resize(number_of_request + 1, 0);
  std::vector<std::pair<int, int>> min_heap;
  std::vector<std::pair<int, int>> max_heap;
  int size_heap = 0;
  int insert_number;
  for (int i = 0; i < number_of_request; ++i) {
    std::cin >> command;
    if (command == "insert") {
      std::cin >> insert_number;
      InsertMaxHeap(max_heap, insert_number, size_heap, i + 1);
      InsertMinHeap(min_heap, insert_number, size_heap, i + 1);
      ++size_heap;
      std::cout << "ok" << '\n';
    }
    if (command == "extract_min") {
      ExtractMinInProgram(min_heap, max_heap, size_heap);
    }
    if (command == "extract_max") {
      ExtractMaxInProgram(max_heap, min_heap, size_heap);
    }
    if (command == "get_min") {
      GetMin(min_heap, size_heap);
    }
    if (command == "get_max") {
      GetMax(max_heap, size_heap);
    }
    if (command == "size") {
      std::cout << size_heap << '\n';
    }
    if (command == "clear") {
      size_heap = 0;
      min_heap.resize(0);
      max_heap.resize(0);
      std::cout << "ok" << '\n';
    }
  }
  return 0;
}
