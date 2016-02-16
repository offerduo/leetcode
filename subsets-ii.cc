#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<vector<int> > subsetsWithDup(vector<int>& nums) {
    vector<vector<int> > ret;
    ret.push_back(vector<int>());
    if (nums.size() == 0) return ret;
    sort(nums.begin(), nums.end());
    int prevRetSize = 0;
    for (int i = 0; i < nums.size(); ++i) {
      int currRetSize = ret.size();
      int start = 0;
      if (i > 0 && nums[i] == nums[i-1]) {
        start = prevRetSize;
      }
      prevRetSize = currRetSize;
      for (int j = start; j < currRetSize; ++j) {
        vector<int> newSubSet = ret[j];
        newSubSet.push_back(nums[i]);
        ret.push_back(newSubSet);
      }
    }
    return ret;
  }
};

int main(int argc, char *argv[])
{
  vector<int> nums;
  for (int i = 1; i < argc; ++i) {
    nums.push_back(atoi(argv[i]));
  }
  Solution sol;
  vector<vector<int> > ret = sol.subsetsWithDup(nums);
  for (auto vec : ret) {
    cout << "[ ";
    for (auto num : vec) {
      cout << num << " ";
    }
    cout << "]" << endl;
  }
  return 0;
}
