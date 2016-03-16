#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class Solution {
 private:
  // Use flood fill algorithm to "fill" the connected ('O') cells.
  // Special character '#' indicates this cell has been 'filled'.
  void floodFill(vector<vector<char>> &board, int i, int j) {
    queue<int> q;
    q.push(i*board[0].size()+j);
    while (!q.empty()) {
      int row = q.front() / board[0].size();
      int col = q.front() % board[0].size();
      q.pop();
      // Fill up, down, left, and right neighbors
      if (row > 0 && board[row-1][col] == 'O') {
        q.push((row-1)*board[0].size()+col);
        board[row-1][col] = '#';
      }
      if (row < board.size()-1 && board[row+1][col] == 'O') {
        q.push((row+1)*board[0].size()+col);
        board[row+1][col] = '#';
      }
      if (col > 0 && board[row][col-1] == 'O') {
        q.push(row*board[0].size()+col-1);
        board[row][col-1] = '#';
      }
      if (col < board[0].size()-1 && board[row][col+1] == 'O') {
        q.push(row*board[0].size()+col+1);
        board[row][col+1] = '#';
      }
    }
  }
 public:
  void solve(vector<vector<char>>& board) {
    if (board.size() <= 1 || board[0].size() <= 1) {
      return;
    }
    // For each 'O' cell on the boundary, color it to '#' and do floodFill
    for (int row = 0; row < board.size(); ++row) {
      if (board[row][0] == 'O') {
        board[row][0] = '#';
        floodFill(board, row, 0);
      }
      if (board[row][board[0].size()-1] == 'O') {
        board[row][board[0].size()-1] = '#';
        floodFill(board, row, board[0].size()-1);
      }
    }
    for (int col = 0; col < board[0].size(); ++col) {
      if (board[0][col] == 'O') {
        board[0][col] = '#';
        floodFill(board, 0, col);
      }
      if (board[board.size()-1][col] == 'O') {
        board[board.size()-1][col] = '#';
        floodFill(board, board.size()-1, col);
      }
    }
    // After floodFill, now the remaining 'O' cells are surrounded regions:
    // change them to 'X'. Change the '#' cells back to 'O'.
    for (int i = 0; i < board.size(); ++i) {
      for (int j = 0; j < board[0].size(); ++j) {
        if (board[i][j] == '#') {
          board[i][j] = 'O';
        } else {
          board[i][j] = 'X';
        }
      }
    }
  }
};

void dumpBoard(vector<vector<char>> &board)
{
  for (auto vec : board) {
    for (auto ch : vec) {
      cout << ch << " ";
    }
    cout << endl;
  }
}

#if 0

./a.out < input.txt

cat input.txt
4 4
X X X X
X O O X
X X O X
X O X X

#endif

int main(int argc, char *argv[])
{
  int nRow = 0, nCol = 0;
  cin >> nRow >> nCol;
  vector<vector<char>> board(nRow, vector<char>(nCol, 'U'));
  dumpBoard(board);
  for (int i = 0; i < nRow; ++i) {
    for (int j = 0; j < nCol; ++j) {
      cin >> board[i][j];
    }
  }
  cout << endl;
  dumpBoard(board);
  Solution sol;
  sol.solve(board);
  cout << endl;
  dumpBoard(board);
  return 0;
}
