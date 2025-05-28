/*
Question statement
# Given predicted stock prices for next n days for a stock, find the maximum
# profit that can be made with a single buy-sell transaction (e.g. you can buy
# single share of stock on one day, and then sell it on a subsequent day).  If
# no profit can be made return 0.


# For example, given this list of daily stock predictions:
# (20, 40, 52, 15, 18, 50, 20, 45),
# buying at 15 and selling at 50 gives maximum profit of 35.
*/

/*
OK, it took embarrassingly long to arrive at this solution:
  Track the minimum before the current element.
  Compute current minus minimum.
  And the maximum of that.
*/
#include <algorithm>
unsigned stock(unsigned prices[], size_t n) {
  if (n < 2)
    return 0;
  unsigned result = 0;
  unsigned min = prices[0];
  for (size_t i = 1; i < n; ++i) {
    unsigned p = prices[i];
    if (p > min)
      result = std::max(result, p - min);
    min = std::min(min, p);
  }
  return result;
}

#include <stdio.h>
#include <vector>

int main() {
  {
    std::vector<unsigned> data{20, 40, 52, 15, 18, 50, 20, 45};
    printf("stock:%u\n", stock(&data[0], data.size()));
  }

  {
    std::vector<unsigned> data{10, 100, 90, 110};
    printf("stock:%u\n", stock(&data[0], data.size()));
  }
}
