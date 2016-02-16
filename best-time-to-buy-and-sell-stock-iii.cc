#include <iostream>
#include <vector>

using namespace std;

class Solution {
 private:
  // For a pivot point i that divides prices into [0, i] and [i+1, n-1], the
  // profit is the sum of max profits of these two time intervals.
  // We do calculation for all possible pivot points for |prices| and store the
  // result into |left| and |right|.
  void helper(vector<int> &prices, vector<int> &left, vector<int> &right) {
    int local = 0;
    left[0] = 0;
    for (int i = 0; i < prices.size()-1; ++i) {
      int delta = prices[i+1] - prices[i];
      local = max(0, local+delta);
      left[i+1] = max(left[i], local);
    }
    local = 0;
    right[prices.size()-1] = 0;
    for (int i = prices.size()-1; i > 0; --i) {
      int delta = prices[i] - prices[i-1];
      local = max(0, local+delta);
      right[i-1] = max(right[i], local);
    }
  }
 public:
  int maxProfit(vector<int>& prices) {
    if (prices.size() <= 1) return 0;
    int ret = 0;
    vector<int> left(prices.size()), right(prices.size());
    helper(prices,left, right);
    for (int i = 0; i < prices.size(); ++i) {
      ret = max(ret, left[i]+right[i]);
    }
    return ret;
  }
};

int main(int argc, char *argv[])
{
  vector<int> prices;
  for (int i = 1; i < argc; ++i) {
    prices.push_back(atoi(argv[i]));
  }
  Solution sol;
  cout << sol.maxProfit(prices) << endl;
  return 0;
}
