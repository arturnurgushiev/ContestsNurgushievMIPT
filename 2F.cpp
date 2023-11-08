#include <iostream>
#include <string>
#include <vector>

const int kMaxSizeOfHeap = 100000;

std::vector<int> help_to_decrease_key;

void SiftUp(std::vector<std::pair<long long, int>>& heap, int index) {
  while (index != 0) {
    int parent = (index - 1) / 2;
    if (heap[parent].first > heap[index].first) {
      std::swap(help_to_decrease_key[heap[parent].second],
                help_to_decrease_key[heap[index].second]);
      std::swap(heap[parent], heap[index]);
    }
    index = parent;
  }
}

void SiftDown(std::vector<std::pair<long long, int>>& heap, int index,
              int size_heap) {
  while (2 * index + 1 < size_heap) {
    int first_son = 2 * index + 1;
    int min_son = first_son;
    int second_son = 2 * index + 2;
    if (second_son < size_heap &&
        heap[second_son].first < heap[first_son].first) {
      min_son = second_son;
    }
    if (heap[min_son] < heap[index]) {
      std::swap(help_to_decrease_key[heap[min_son].second],
                help_to_decrease_key[heap[index].second]);
      std::swap(heap[min_son], heap[index]);
    }
    index = min_son;
  }
}

void Insert(std::vector<std::pair<long long, int>>& heap, int insert_number,
            int size_heap, int index_of_request) {
  heap[size_heap] = {insert_number, index_of_request};
  help_to_decrease_key[index_of_request] = size_heap;
  SiftUp(heap, size_heap);
}

void ExtractMin(std::vector<std::pair<long long, int>>& heap, int size_heap) {
  std::swap(help_to_decrease_key[heap[size_heap - 1].second],
            help_to_decrease_key[heap[0].second]);
  std::swap(heap[size_heap - 1], heap[0]);
  SiftDown(heap, 0, size_heap - 1);
}

void DecreaseKey(std::vector<std::pair<long long, int>>& heap,
                 int index_of_insert_request, int delta) {
  heap[help_to_decrease_key[index_of_insert_request]].first -= delta;
  SiftUp(heap, help_to_decrease_key[index_of_insert_request]);
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  int number_of_requests;
  std::cin >> number_of_requests;
  help_to_decrease_key.resize(number_of_requests + 1, 0);
  std::vector<std::pair<long long, int>> heap(kMaxSizeOfHeap);
  int size_heap = 0;
  std::string command;
  int help_number;
  int index_of_insert_request;
  for (int i = 0; i < number_of_requests; ++i) {
    std::cin >> command;
    if (command == "insert") {
      std::cin >> help_number;
      Insert(heap, help_number, size_heap, i + 1);
      ++size_heap;
    }
    if (command == "getMin") {
      std::cout << heap[0].first << '\n';
    }
    if (command == "extractMin") {
      ExtractMin(heap, size_heap);
      --size_heap;
    }
    if (command == "decreaseKey") {
      std::cin >> index_of_insert_request;
      std::cin >> help_number;
      DecreaseKey(heap, index_of_insert_request, help_number);
    }
  }
  return 0;
}
