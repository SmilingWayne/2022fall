// {{'5','3','.','.','7','.','.','.','.'},
// {'6','.','.','1','9','5','.','.','.'},
// {'.','9','8','.','.','.','.','6','.'},
// {'8','.','.','.','6','.','.','.','3'},
// {'4','.','.','8','.','3','.','.','1'},
// {'7','.','.','.','2','.','.','.','6'},
// {'.','6','.','.','.','.','2','8','.'},
// {'.','.','.','4','1','9','.','.','5'},
// {'.','.','.','.','8','.','.','7','9'}}

#include <iostream>
#include <vector>
#include <ctime>
using namespace std;
// const int N = 3

class Soduku_V2
{
private:
    bool columns[9][9];
    bool rows[9][9];
    bool block[3][3][9];
    vector<pair<int, int> > spaces;
    char board[9][9];

public:
    Soduku_V2() {}
    Soduku_V2(vector<vector<char> > &ipt_board)
    {
        memset(columns, false, sizeof(columns));
        memset(rows, false, sizeof(rows));
        memset(block, false, sizeof(block));
        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                board[i][j] = ipt_board[i][j];
                if (ipt_board[i][j] != '.')
                {
                    int num = (int)(ipt_board[i][j] - '1');
                    columns[j][num] = true;
                    rows[i][num] = true;
                    block[i / 3][j / 3][num] = true;
                }
                else
                {
                    spaces.push_back(make_pair(i, j));
                }
            }
        }
        // display();
        dfs(0);
    }
    void display()
    {
        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                cout << board[i][j] << " ";
            }
            cout << "\n";
        }
    }

    bool isValid(int r, int c, int t)
    {
        if (columns[c][t - 1] || rows[r][t - 1] || block[r / 3][c / 3][t - 1])
        {
            return false;
        }
        board[r][c] = (char)(t + '0');
        columns[c][t - 1] = true;
        rows[r][t - 1] = true;
        block[r / 3][c / 3][t - 1] = true;
        return true;
    }
    void dfs(int pos)
    {
        if (pos == spaces.size())
        {
            display();
            return;
        }
        for (int i = 1; i <= 9; i++)
        {
            int r = spaces[pos].first;
            int c = spaces[pos].second;
            if (isValid(r, c, i))
            {
                dfs(pos + 1);
            }
            else
            {
                continue;
            }
            board[r][c] = '.';
            columns[c][i - 1] = false;
            rows[r][i - 1] = false;
            block[r / 3][c / 3][i - 1] = false;
        }
    }
};

// 这是初代版本的Soduku 击败52% 的速度提交
class Soduku_1
{
private:
    vector<vector<char> > board;
    int rows;
    int cols;
    vector<vector<bool> > visited;

public:
    Soduku_1(){};
    Soduku_1(vector<vector<char> > b)
    {
        board = b;
        rows = b.size();
        cols = b[0].size();
        for (int i = 0; i < rows; i++)
        {
            visited.push_back(vector<bool>(cols, false));
            for (int j = 0; j < cols; j++)
            {
                if (board[i][j] != '.')
                {
                    visited[i][j] = true;
                }
            }
        }
    }
    /**
     * 展示数独最后的情况
     * */
    void display()
    {
        for (auto &a : board)
        {
            for (auto &b : a)
            {
                cout << b << " ";
            }
            cout << endl;
        }
    }

    bool dfs(int r, int c)
    {
        if (r == rows)
        {
            display();
            return true;
        }
        if (c == cols)
        {
            return dfs(r + 1, 0);
        }
        if (board[r][c] != '.')
        {
            return dfs(r, c + 1);
        }
        for (char i = '1'; i <= '9'; i++)
        {
            // cout << i << endl;
            if (!isValid(r, c, i))
            {
                continue;
            }
            board[r][c] = i;
            if (dfs(r, c))
            {
                return true;
            }
            board[r][c] = '.';
        }
        return false;
    }

    bool isValid(int row, int col, char c)
    {
        if (visited[row][col] == true)
        {
            return false;
        }
        for (int i = 0; i < rows; i++)
        {
            if (board[i][col] == c)
            {
                return false;
            }
            if (board[row][i] == c)
            {
                return false;
            }
            if (board[3 * (row / 3) + i / 3][3 * (col / 3) + i % 3] == c)
            {
                return false;
            }
        }
        return true;
    }
};

int main()
{

    clock_t startTime, endTime;
    startTime = clock();

    vector<vector<char> > b = {{'5', '3', '.', '.', '7', '.', '.', '.', '.'},
                               {'6', '.', '.', '1', '.', '5', '.', '.', '.'},
                               {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
                               {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
                               {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
                               {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
                               {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
                               {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
                               {'.', '.', '.', '.', '8', '.', '.', '7', '9'}};
    // Soduku_1 sdk_1 = Soduku_1(b);
    // sdk_1.dfs(0, 0);
    Soduku_V2 sdk_2 = Soduku_V2(b);
    // Factorial_3();
    endTime = clock();
    cout << "The run time is: " << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
}
