#include <iostream>
#include <string>

using namespace std;

class Solution {
 public:
  bool isPalindrome(string s) {
    if (s.empty()) return true;
    int start = 0, end = s.size()-1;
    while (start <= end) {
      bool alNum = true;
      if (!isalnum(s[start])) {
        ++start;
        alNum = false;
      }
      if (!isalnum(s[end])) {
        --end;
        alNum = false;
      }
      if (alNum) {
        if (tolower(s[start]) != tolower(s[end])) {
          return false;
        } else {
          ++start; --end;
        }
      } else {
        continue;
      }
    }
    return true;
  }
};

int main(int argc, char *argv[])
{
  string s;
  cout << "Say something: " << endl;
  getline(cin, s);
  Solution sol;
  bool result = sol.isPalindrome(s);
  if (result) cout << "Valid palindrome" << endl;
  else cout << "Invalid palindrame" << endl;
  return 0;
}
