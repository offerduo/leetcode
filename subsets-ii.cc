#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    void helper(vector<vector<int> > &ret,
                vector<int>         &nums,
                int                  nextNumIndex,
                int                 &lastRetSize)
    {
      if (nextNumIndex == -1) {
        // Base case: add empty vector to ret
        ret.push_back(vector<int>());
        return;
      }
      // Append nums[nextNumIndex-1] to ret
      helper(ret, nums, nextNumIndex-1, lastRetSize);
      // After calling helper, lastRetSize indicates the size of ret before
      // appending nums[nextNumIndex-1].

      // Start appending nums[nextNumIndex]
      int currRetSize = ret.size(); // Remember current ret size since we keep
                                    // appending new entry to ret.
      int start = 0;  // Append nums[nextNumIndex] to all entries in ret by default
      if (nextNumIndex > 0 && nums[nextNumIndex] == nums[nextNumIndex-1]) {
        // We are adding same num as previous one
        // Instead of appending nums[nextNumIndex] to all entries in ret, we
        // only do this to newly added entries starting from index lastRetSize.
        start = lastRetSize;
      }
      lastRetSize = currRetSize; // Update lastRetSize
      for (int i = start; i < currRetSize; ++i) {
        vector<int> newSubset(ret[i]);
        newSubset.push_back(nums[nextNumIndex]);
        ret.push_back(newSubset);
      }
    }
    vector<vector<int> > subsetsWithDup(vector<int>& nums) {
        vector<vector<int> > ret;
        sort(nums.begin(), nums.end());
        int lastRetSize = 0;
        helper(ret, nums, nums.size()-1, lastRetSize);
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
