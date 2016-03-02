#include <iostream>
#include <algorithm>
#include <queue>
#include <string>
#include <unordered_set>

using namespace std;

class Solution {
 public:
  int ladderLength(string beginWord,
                   string endWord,
                   unordered_set<string>& wordList) {
    int nCurr = 1, // Number of candidate string in current level
        nNext = 0, // Number of candidate string in next level
        level = 1; // Current level, starting from 1 (beginWord at level 1)
    queue<string> q;  // For BST
    unordered_set<string> visited; // Hashset that contains visited string
    q.push(beginWord);
    visited.insert(beginWord);
    // Start Breath-First-Search
    while (!q.empty()) {
      string curr = q.front(); q.pop();
      --nCurr;
      // For a given string, do tranformation by changing the character at
      // position i to ch:
      //   if the new string equals to endWord, we're done;
      //   otherwise, if the new string is a condidate:
      //     add new string to queue
      //     increase number of candidate string for next level
      //     mark new string as visited
      // A candidate string must meet the following criteria:
      //   string is not visited;
      //   wordList contains this string.
      for (int i = 0; i < curr.size(); ++i) {
        string temp(curr); // Make a copy to keep original data un-touched
        for (char ch = 'a'; ch <= 'z'; ++ch) {
          temp[i] = ch;
          if (endWord == temp) {
            return level + 1;
          }
          // Check if temp is candidate string
          if (visited.find(temp) == visited.end() &&
              wordList.find(temp) != wordList.end()) {
            q.push(temp);
            ++nNext;
            visited.insert(temp);
          }
        }
      }
      // Once done with current leve, move the next one
      if (nCurr == 0) {
        nCurr = nNext;
        nNext = 0;
        ++level;
      }
    }
    return 0;
  }
};

int main(int argc, char *argv[])
{
  // First two strings are beginWord and endWord repectively
  if (argc < 3) return 0;
  string beginWord(argv[1]), endWord(argv[2]);
  unordered_set<string> wordList;
  for (int i = 3; i < argc; ++i) {
    wordList.insert(argv[i]);
  }
  Solution sol;
  cout << sol.ladderLength(beginWord, endWord, wordList) << endl;
  return 0;
}
