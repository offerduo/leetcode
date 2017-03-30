#include <iostream>
#include <cmath>

using namespace std;

class Solution {
private:
    bool is_palindrome(int x, int num_digits) {
        if (num_digits == 1) return true;
        if (num_digits == 2) {
            return x / 10 == x % 10;
        }
        int high = x / pow(10, num_digits - 1);
        int low = x % (int)(pow(10, 1));
        if (high != low) return false;
        x -= high * pow(10, num_digits - 1);
        x /= 10;
        return is_palindrome(x, num_digits - 2);
    }
public:
    bool isPalindrome(int x) {
        if (x < 0) return false;
        int num_digits = 0;
        while (x / pow(10, ++num_digits) >= 1);
        return is_palindrome(x, num_digits);
    }
};

int main(int argc, char **argv)
{
	Solution s;
  bool result = s.isPalindrome(atoi(argv[1]));
  if (result) cout << "true" << endl;
  else cout << "false" << endl;
  return 0;
}
