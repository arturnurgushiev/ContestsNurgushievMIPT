#include <iostream>
#include <vector>

int SmallMassiveSizeFiveMedian(std::vector<int>& number) {
  if (number[0] > number[1]) {
    std::swap(number[0], number[1]);
  }
  if (number[3] > number[4]) {
    std::swap(number[3], number[4]);
  }
  if (number[0] > number[3]) {
    std::swap(number[0], number[3]);
    std::swap(number[1], number[4]);
  }
  if (number[2] >= number[1]) {
    if (number[1] <= number[3]) {
      return std::min(number[2], number[3]);
    }
    return std::min(number[1], number[4]);
  }
  if (number[2] >= number[3]) {
    return std::min(number[2], number[4]);
  }
  return std::min(number[1], number[3]);
}

int SmallQuickSelectStupidSort(std::vector<int>& number, int left, int right,
                               int which_one) {
  for (int i = left; i < right; ++i) {
    int imin = i;
    for (int j = i + 1; j < right; ++j) {
      if (number[imin] > number[j]) {
        imin = j;
      }
    }
    std::swap(number[imin], number[i]);
    if (i == left + which_one - 1) {
      return number[i];
    }
  }
  return -1;
}

std::pair<int, int> Partition(std::vector<int>& number, int left, int right,
                              int pivot) {
  int pointer = -1;
  for (int i = left; i < right; ++i) {
    if (number[i] < pivot) {
      std::swap(number[i], number[left + ++pointer]);
    }
  }
  int first = pointer;
  for (int i = left + pointer + 1; i < right; ++i) {
    if (number[i] <= pivot) {
      std::swap(number[i], number[left + ++pointer]);
    }
  }
  int second = pointer;
  return {first, second};
}

int DeterministicQuickSelect(std::vector<int>& number, int left, int right,
                             int which_one) {
  const int kSmallerMassiveMedianHelpConst = 10;
  const int kBase = 10;
  if (right - left <= kBase) {
    return SmallQuickSelectStupidSort(number, left, right, which_one);
  }
  std::vector<int> help(5);
  std::vector<int> medians_of_small_massives((right - left + 4) / 5);
  bool is_divisible_by_five = (right - left) % 5 == 0;
  if (right - left < 5) {
    help.resize(0);
  }
  for (int i = left; i < right; ++i) {
    if (!is_divisible_by_five && i >= right - (right - left) % 5) {
      help.push_back(number[i]);
    } else {
      help[(i - left) % 5] = number[i];
    }
    if ((i - left) % 5 == 4) {
      medians_of_small_massives[(i - left) / 5] =
          SmallMassiveSizeFiveMedian(help);
      if (!is_divisible_by_five && i + 1 == right - (right - left) % 5) {
        help.resize(0);
      }
    }
  }
  if (!is_divisible_by_five) {
    medians_of_small_massives[(right - left + 4) / 5 - 1] =
        SmallQuickSelectStupidSort(help, 0, static_cast<int>(help.size()),
                                   help.size() / 2 + 1);
  }
  int pivot = DeterministicQuickSelect(
      medians_of_small_massives, 0, (right - left + 4) / 5,
      (right - left + 4) / kSmallerMassiveMedianHelpConst + 1);
  std::pair<int, int> pointer = Partition(number, left, right, pivot);
  if (pointer.first >= which_one - 1) {
    return DeterministicQuickSelect(number, left, pointer.first + left + 1,
                                    which_one);
  }
  if (pointer.second < which_one - 1) {
    return DeterministicQuickSelect(number, pointer.second + left + 1, right,
                                    which_one - pointer.second - 1);
  }
  return pivot;
}

int main() {
  const int kFirstRecursiveConst = 123;
  const int kSecondRecursiveConst = 45;
  const int kThirdRecursiveConst = 10004321;
  int size;
  int which_one;
  std::cin >> size >> which_one;
  std::vector<int> number(size);
  std::cin >> number[0] >> number[1];
  for (int i = 2; i < size; ++i) {
    number[i] = (number[i - 1] * kFirstRecursiveConst +
                 number[i - 2] * kSecondRecursiveConst) %
                kThirdRecursiveConst;
  }
  std::cout << DeterministicQuickSelect(number, 0, size, which_one) << '\n';
  return 0;
}
