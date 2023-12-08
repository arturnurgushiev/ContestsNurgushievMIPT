#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

void SparseTableBuilding(
    std::vector<std::vector<std::pair<int, int>>>& sparse_table,
    std::vector<int>& numbers, int sparse_table_size, int size) {
  int length = 2;
  for (int i = 0; i < size - 1; ++i) {
    if (numbers[i] > numbers[i + 1]) {
      sparse_table[1][i] = {i + 1, i};
    } else {
      sparse_table[1][i] = {i, i + 1};
    }
  }
  for (int k = 1; k < sparse_table_size - 1; ++k) {
    length *= 2;
    for (int i = 0; i < size - 1; ++i) {
      int middle = std::min(size, i + length / 2);
      std::vector<std::pair<int, int>> help(4);
      help[0] = {numbers[sparse_table[k][i].first], sparse_table[k][i].first};
      help[1] = {numbers[sparse_table[k][i].second], sparse_table[k][i].second};
      help[2] = {numbers[sparse_table[k][middle].first],
                 sparse_table[k][middle].first};
      help[3] = {numbers[sparse_table[k][middle].second],
                 sparse_table[k][middle].second};
      std::sort(help.begin(), help.end());
      help.resize(unique(help.begin(), help.end()) - help.begin());
      sparse_table[k + 1][i] = {help[0].second, help[1].second};
    }
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int size;
  int number_of_request;
  std::cin >> size >> number_of_request;
  std::vector<int> numbers(size);
  int sparse_table_size = 1;
  int sparse_table_size_help = 1;
  while (sparse_table_size_help <= size) {
    sparse_table_size_help *= 2;
    ++sparse_table_size;
  }
  std::vector<std::vector<std::pair<int, int>>> sparse_table(
      sparse_table_size, std::vector<std::pair<int, int>>(size + 1));
  for (int& help_to_input : numbers) {
    std::cin >> help_to_input;
  }
  SparseTableBuilding(sparse_table, numbers, sparse_table_size, size);
  for (int i = 0; i < number_of_request; ++i) {
    int left;
    int right;
    std::cin >> left >> right;
    int least_length = static_cast<int>(log2(right - left + 1));
    std::vector<std::pair<int, int>> help(4);
    help[0] = {numbers[sparse_table[least_length][left - 1].first],
               sparse_table[least_length][left - 1].first};
    help[1] = {numbers[sparse_table[least_length][left - 1].second],
               sparse_table[least_length][left - 1].second};
    help[2] = {
        numbers[sparse_table[least_length][right - pow(2, least_length)].first],
        sparse_table[least_length][right - pow(2, least_length)].first};
    help[3] = {numbers[sparse_table[least_length][right - pow(2, least_length)]
                           .second],
               sparse_table[least_length][right - pow(2, least_length)].second};
    std::sort(help.begin(), help.end());
    help.resize(unique(help.begin(), help.end()) - help.begin());
    std::cout << help[1].first << '\n';
  }
}
