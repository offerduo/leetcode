#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int maxProfit(vector<int>& prices) {
    if (prices.size() <= 1) return 0;
    int ret = 0;
    for (int i = 0; i < prices.size()-1; ++i) {
      int delta = prices[i+1] - prices[i];
      ret = delta > 0 ? ret + delta : ret;
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
