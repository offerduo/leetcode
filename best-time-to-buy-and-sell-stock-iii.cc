#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int maxProfit(vector<int>& prices) {
    if (prices.size() <= 1) return 0;
    // local[i][j] indicates the max profit at i-th day with up to j
    // transactions; and last sell must be on i-th day.
    vector<vector<int> > local(prices.size(), vector<int>(3));
    // global[i][j] indicates the max profix at i-th day with up to j
    // transactions; and last sell might be or might not be on i-th day.
    vector<vector<int> > global(prices.size(), vector<int>(3));
    for (int i = 1; i < prices.size(); ++i) {
      for (int j = 1; j < 3; ++j) {
        int delta = prices[i] - prices[i-1];
        // To calculate local[i][j], there are two possible cases:
        // case a: extends last sell to i-th day for local[i-1][j].
        //         global[i-1][j] cannot be used since the last sell is not
        //         guaranteed at (i-1)-th day; thus there's not a "extension".
        // case b: Given global[i-1][j-1] and delta,
        //         if delta > 0, last transaction is buy at (i-1)-th day, sell
        //         at i-th day;
        //         if delta < 0, last transaction is buy and sell at i-th day
        //         to avoid profit loss.
        local[i][j] = max(local[i-1][j]+delta,             // case a
                          global[i-1][j-1]+max(delta, 0)); // case b
        // To calculate global[i][j], there are two possible cases:
        // case a: last sell is on i-th day
        // case b: last sell is on any of the previous days
        global[i][j] = max(local[i][j], global[i-1][j]);
      }
    }
    return global[prices.size()-1][2];
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
