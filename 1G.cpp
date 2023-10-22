#include <cstdio>
#include <iostream>
#include <vector>

const int kBase = 256;

void CountingSort(std::vector<std::pair<long long, long long>>& number,
                  std::vector<std::pair<long long, long long>>& copy_number,
                  int& size) {
  std::vector<int> cnt(kBase);
  for (int i = 0; i < size; ++i) {
    ++cnt[number[i].first % kBase];
  }
  for (int i = 1; i < kBase; ++i) {
    cnt[i] += cnt[i - 1];
  }
  for (int i = size - 1; i >= 0; --i) {
    copy_number[--cnt[number[i].first % kBase]] = {number[i].first / kBase,
                                                   number[i].second};
  }
  for (int i = size - 1; i >= 0; --i) {
    number[i] = copy_number[i];
  }
}

void LSDSort(std::vector<std::pair<long long, long long>>& number,
             std::vector<std::pair<long long, long long>>& copy_number,
             int& size, long long& max_num) {
  while (max_num > 0) {
    CountingSort(number, copy_number, size);
    max_num /= kBase;
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  int size;
  std::cin >> size;
  std::vector<std::pair<long long, long long>> number(size);
  long long max_num = -1;
  for (int i = 0; i < size; ++i) {
    std::cin >> number[i].first;
    number[i].second = number[i].first;
    max_num = std::max(max_num, number[i].second);
  }
  std::vector<std::pair<long long, long long>> copy_numbers(size);
  for (int i = 0; i < size; ++i) {
    copy_numbers[i] = number[i];
  }
  LSDSort(number, copy_numbers, size, max_num);
  for (int i = 0; i < size; ++i) {
    std::cout << number[i].second << '\n';
  }
  return 0;
}
