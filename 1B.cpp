#include <cmath>
#include <iostream>
#include <vector>

int main() {
  const int kAccuracy = 10;
  std::cout.precision(kAccuracy);
  int quantity;
  std::cin >> quantity;
  std::vector<long double> mandagors(quantity);
  long double mandagor;
  for (int i = 0; i < quantity; ++i) {
    std::cin >> mandagor;
    mandagors[i] = log(mandagor);
  }
  std::vector<long double> prefix_sum(quantity + 1, 0);
  for (int i = 1; i <= quantity; ++i) {
    prefix_sum[i] = prefix_sum[i - 1] + mandagors[i - 1];
  }
  int number_of_request;
  std::cin >> number_of_request;
  int left;
  int right;
  for (int i = 0; i < number_of_request; ++i) {
    std::cin >> left >> right;
    std::cout << std::fixed
              << exp((prefix_sum[right + 1] - prefix_sum[left]) /
                     (right - left + 1))
              << '\n';
  }
  return 0;
}
