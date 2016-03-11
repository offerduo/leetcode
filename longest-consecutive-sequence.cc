#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
 private:
  typedef unordered_set<int> hash_set;
  typedef hash_set::const_iterator hash_iter;
  // Find sequance start with |num|:
  //   if offset == -1, search for consecutive numbers lower than |num|;
  //   otherwise, the larger numbers.
  void findSequence(hash_set &hashSet, int num, int offset, int &len)
  {
    hash_iter search;
    int target = num + offset;
    while ((search = hashSet.find(target)) != hashSet.end()) {
      hashSet.erase(search); // No number 'reuse' here
      target += offset;
      ++len;
    }
  }
 public:
  int longestConsecutive(vector<int>& nums) {
    unordered_set<int> hashSet;
    int ret = 0;
    for (int i : nums) {
      hashSet.insert(i);
    }
    while (!hashSet.empty()) {
      // Randomly choose a number in hashSet, search for consecutive sequence
      // bi-directionally.
      int num = *hashSet.begin(),
          len = 1; // Sequence starts with only one number
      hashSet.erase(num);
      // Search for consecutive sequence for numbers lower than |num|
      findSequence(hashSet, num, -1, len);
      // Now search for sequence for numbers larger than |num|
      // No need to reset len
      findSequence(hashSet, num, 1, len);
      // Update ret if len > ret
      ret = (len > ret ) ? len : ret;
    }
    return ret;
  }
};

int main(int argc, char *argv[])
{
  vector<int> nums;
  vector<int>::const_iterator iter;
  for (int i = 1; i < argc; ++i) {
    int num = atoi(argv[i]);
    iter = find(nums.begin(), nums.end(), num);
    if (iter == nums.end()) {
      nums.push_back(num);
    } else {
      cout << "Found duplicate number: " << num << endl;
    }
  }
  Solution sol;
  int ret = sol.longestConsecutive(nums);
  cout << "longest consecutive sequence length: " << ret << endl;
  return 0;
}
