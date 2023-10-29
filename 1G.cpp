#include <iostream>
#include <vector>

void LSDSort(std::vector<long long>& initialnumber, int size) {
  std::vector<std::pair<long long, long long>> number(size);
  std::vector<std::pair<long long, long long>> copy_number(size);
  long long max_num = -1;
  for (int i = 0; i < size; ++i) {
    number[i] = {initialnumber[i], initialnumber[i]};
    copy_number[i] = {initialnumber[i], initialnumber[i]};
    max_num = std::max(max_num, number[i].second);
  }
  const int kBase = 256;
  std::vector<int> cnt(kBase);
  while (max_num > 0) {
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
    number = copy_number;
    max_num /= kBase;
    for (int i = 0; i < kBase; ++i) {
      cnt[i] = 0;
    }
  }
  for (int i = 0; i < size; ++i) {
    initialnumber[i] = number[i].second;
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  int size;
  std::cin >> size;
  std::vector<long long> number(size);
  for (int i = 0; i < size; ++i) {
    std::cin >> number[i];
  }
  LSDSort(number, size);
  for (int i = 0; i < size; ++i) {
    std::cout << number[i] << '\n';
  }
  return 0;
}
