#include <iostream>
#include <vector>

void LSDSort(std::vector<long long>& initial_number) {
  int size = static_cast<int>(initial_number.size());
  std::vector<std::pair<long long, long long>> number(size);
  std::vector<std::pair<long long, long long>> copy_number(size);
  long long max_number = -1;
  for (int i = 0; i < size; ++i) {
    number[i] = {initial_number[i], initial_number[i]};
    copy_number[i] = {initial_number[i], initial_number[i]};
    max_number = std::max(max_number, number[i].second);
  }
  const int kBase = 256;
  std::vector<int> count(kBase);
  while (max_number > 0) {
    for (int i = 0; i < size; ++i) {
      ++count[number[i].first % kBase];
    }
    for (int i = 1; i < kBase; ++i) {
      count[i] += count[i - 1];
    }
    for (int i = size - 1; i >= 0; --i) {
      copy_number[--count[number[i].first % kBase]] = {number[i].first / kBase,
                                                       number[i].second};
    }
    number = copy_number;
    max_number /= kBase;
    for (int i = 0; i < kBase; ++i) {
      count[i] = 0;
    }
  }
  for (int i = 0; i < size; ++i) {
    initial_number[i] = number[i].second;
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int size;
  std::cin >> size;
  std::vector<long long> number(size);
  for (int i = 0; i < size; ++i) {
    std::cin >> number[i];
  }
  LSDSort(number);
  for (int i = 0; i < size; ++i) {
    std::cout << number[i] << '\n';
  }
  return 0;
}
