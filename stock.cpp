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
1. I read a related problem online, about maximum subsequence.
   The algorithm was roughly:
   for i..n:
     max(sequence_before_i + a[i], a[i])

   You either add the next element, or start a new sequence.
   i.e. if the element is positive you add it, else you start over.
   This feels wrong however, because it could be -1 followed 2,
   therefore profitable to include it.

2. During interview I hand waved about wanting to find min and max,
   but min before max.
   Let ignore figuring out exactly 1. maybe it isn't useful or I misread it.
   Let's focus on this kinda min so far, max so far idea.
   Let's think about problems of local maximum and local minimum (screening interview),
   but we really want a global maximum to the right of a global minimum.
   "a global" is an oxymoron.

Let's examine maybe tricky cases:
Stock goes up and up, then falls to a new low, and back up not as far.

  10 100 0 99

Just thinking about this case actually provides some intuition.
What we do is accept the up as long as we can.
Then go down as far as we can. And back up. Over and over.
But each time we find a peak, see if it is a new peak.

The answer is basically to find every local min/max pair, and compare them, iteratively.
That's not a great explanation.
But it helps to say that a "local maximum" is sort of any element immediately before a lower element.
That's not the right explanation, but in the context of stocks and time going only forward, it is useful.
*/
#include <algorithm>
unsigned stock(unsigned prices[], size_t n)
{
	if (n < 2) return 0;
	unsigned result = 0;
	unsigned min = prices[0];
	unsigned max = prices[0];
	for (size_t i = 1; i < n; ++i)
	{
		if (prices[i] < min) {
			// Going down, take the lowest we can.
			min = prices[i];
			// Going down, we must throw out our prior max.
			max = min;
		}
		else if (prices[i] > max) {
			// Going up, we keep prior min, and get the best max we can.
			max = prices[i];
			result = std::max(result, max - min);
		}
	}
	return result;
}

#include <vector>
#include <stdio.h>

int main()
{
	std::vector<unsigned> data {20, 40, 52, 15, 18, 50, 20, 45};
	printf("stock:%u\n", stock(&data[0], data.size()));
}
