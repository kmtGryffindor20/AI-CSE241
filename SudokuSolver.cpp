using namespace std;
#include <bits/stdc++.h>
#define N 9
#define MAX_ITER 1e10

int startState[N][N];

void aStarSudoku(int arr[N][N]);

int main()
{
    int arr[N][N] = { { 5, 3, 0, 0, 7, 0, 0, 0, 0 },
                       { 6, 0, 0, 1, 9, 5, 0, 0, 0 },
                       { 0, 9, 8, 0, 0, 0, 0, 6, 0 },
                       { 8, 0, 0, 0, 6, 0, 0, 0, 3 },
                       { 4, 0, 0, 8, 0, 3, 0, 0, 1 },
                       { 7, 0, 0, 0, 2, 0, 0, 0, 6 },
                       { 0, 6, 0, 0, 0, 0, 2, 8, 0 },
                       { 0, 0, 0, 4, 1, 9, 0, 0, 5 },
                       { 0, 0, 0, 0, 8, 0, 0, 7, 9 } };
    aStarSudoku(arr);
    return 0;
}

/**
 * Checks if the numbers in a given row of a Sudoku grid are valid.
 * 
 * @param arr The Sudoku grid represented as a 2D array.
 * @param row The row index to be checked.
 * @return True if the row is valid, False otherwise.
 */
bool isValidRow(int arr[N][N], int row)
{
    set<int> s;
    for (int i = 0; i < N; i++)
    {
        if(arr[row][i] == 0)
        {
            continue;
        }
        if (s.find(arr[row][i]) != s.end())
        {
            return false;
        }
        if (arr[row][i] != 0)
        {
            s.insert(arr[row][i]);
        }
    }
    return true;
}

/**
 * Checks if the numbers in the specified column of the Sudoku grid are valid.
 *
 * @param arr The Sudoku grid represented as a 2D array.
 * @param col The column index to check.
 * @return True if the column is valid, false otherwise.
 */
bool isValidCol(int arr[N][N], int col)
{
    set<int> s;
    for (int i = 0; i < N; i++)
    {
        if(arr[i][col] == 0)
        {
            continue;
        }
        if (s.find(arr[i][col]) != s.end())
        {
            return false;
        }
        if (arr[i][col] != 0)
        {
            s.insert(arr[i][col]);
        }
    }
    return true;
}

/**
 * Checks if the 3x3 box in the Sudoku grid is valid.
 * 
 * @param arr The Sudoku grid.
 * @return True if the box is valid, false otherwise.
 */
bool isValidBox(int arr[N][N])
{
    set<int> s;
    for (int i = 0; i < N; i += 3)
    {
        for (int j = 0; j < N; j += 3)
        {
            s.clear();
            for (int k = 0; k < 3; k++)
            {
                for (int l = 0; l < 3; l++)
                {
                    if(arr[i + k][j + l] == 0)
                    {
                        continue;
                    }
                    if (s.find(arr[i + k][j + l]) != s.end())
                    {
                        return false;
                    }
                    if (arr[i + k][j + l] != 0)
                    {
                        s.insert(arr[i + k][j + l]);
                    }
                }
            }
        }
    }
    return true;
}

/**
 * Checks if a move is valid in a Sudoku puzzle.
 * 
 * @param arr The Sudoku puzzle grid.
 * @param row The row index of the move.
 * @param col The column index of the move.
 * @param num The number to be placed in the grid.
 * @return True if the move is valid, false otherwise.
 */
bool isValidMove(int arr[N][N], int row, int col, int num)
{
    int arrCopy[N][N];
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            arrCopy[i][j] = arr[i][j];
        }
    }
    arrCopy[row][col] = num;
    bool res = isValidRow(arrCopy, row) && isValidCol(arrCopy, col) && isValidBox(arrCopy);
    return res;
}

/**
 * Checks if the Sudoku grid is complete.
 * 
 * @param arr The Sudoku grid represented as a 2D array.
 * @return True if the grid is complete, false otherwise.
 */
bool isComplete(int arr[N][N])
{
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            if(arr[i][j] == 0)
            {
                return false;
            }
        }
    }
    return true;
}

/**
 * Checks if the given Sudoku puzzle is a goal state.
 * A goal state is a Sudoku puzzle where all rows, columns, and boxes are valid,
 * and the puzzle is complete.
 *
 * @param arr The Sudoku puzzle grid.
 * @return True if the puzzle is a goal state, false otherwise.
 */
bool isGoalState(int arr[N][N])
{
    for(int i = 0; i < N; i++)
    {
        if (!isValidRow(arr, i) || !isValidCol(arr, i))
        {
            return false;
        }
    }
    if (!isValidBox(arr))
    {
        return false;
    }
    if (!isComplete(arr))
    {
        return false;
    }
    cout << "Goal State" << endl;
    return true;
}

/**
 * Returns a vector of pairs representing the possible values for a given variable in a Sudoku grid.
 * Each pair contains the coordinates of the variable (row, col) and the value itself.
 *
 * @param arr The Sudoku grid represented as a 2D array.
 * @param row The row index of the variable.
 * @param col The column index of the variable.
 * @return A vector of pairs representing the possible values for the variable.
 */
vector<pair<pair<int, int>, int>> valuesForVariable(int arr[N][N], int row, int col)
{
    vector<pair<pair<int, int>, int>> v;
    for(int i = 1; i <= 9; i++)
    {
        if(isValidMove(arr, row, col, i))
        {
            v.push_back({{row, col}, i});
        }
    }
    return v;
}

/**
 * Returns a vector of pairs representing the most constrained variables in the Sudoku grid.
 * A variable is considered constrained if it is empty (0) and has the fewest valid moves available.
 * Each pair in the vector contains the coordinates of the variable (row, column) and the number of valid moves.
 *
 * @param arr The Sudoku grid represented as a 2D array.
 * @return A vector of pairs representing the most constrained variables.
 */
vector<pair<pair<int,int>, int>> mostConstrainedVariableHeuristic(int arr[N][N])
{
    vector<pair<pair<int, int>, int>> v;
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            int constraints = 0;
            if(arr[i][j] == 0)
            {
                for(int k = 1; k <= 9; k++)
                {
                    if(isValidMove(arr, i, j, k))
                    {
                        constraints++;
                    }
                }
            }
            if (constraints != 0)
                v.push_back({{i, j}, constraints});
        }
    }
    // return all with minimum possible values
    sort(v.begin(), v.end(), [](pair<pair<int, int>, int> a, pair<pair<int, int>, int> b) {
        return a.second < b.second;
    });
    vector<pair<pair<int, int>, int>> res;
    for(int i = 0; i < v.size(); i++)
    {
        if(v[i].second == v[0].second)
        {
            res.push_back(v[i]);
        }
    }
    return res;
}

/**
 * Calculates the total number of empty variables in a given row of a Sudoku grid.
 * 
 * @param arr The Sudoku grid represented as a 2D array.
 * @param row The row index for which the count of empty variables needs to be calculated.
 * @return The total number of empty variables in the specified row, excluding the current variable being checked.
 */
int totalEmptyRowVariableAffected(int arr[N][N], int row)
{
    int count = 0;
    for (int i = 0; i < N; i++)
    {
        if (arr[row][i] == 0)
        {
            count++;
        }
    }
    return count - 1;
}

/**
 * Counts the number of empty cells in a specific column of a Sudoku grid.
 *
 * @param arr The Sudoku grid represented as a 2D array.
 * @param col The column index to count the empty cells in.
 * @return The number of empty cells in the specified column, excluding the first empty cell.
 */
int totalEmptyColVariableAffected(int arr[N][N], int col)
{
    int count = 0;
    for (int i = 0; i < N; i++)
    {
        if (arr[i][col] == 0)
        {
            count++;
        }
    }
    return count - 1;
}

/**
 * Calculates the total number of empty boxes affected by a given box in a Sudoku grid.
 * An empty box is represented by the value 0.
 * The affected boxes are the ones in the same 3x3 subgrid as the given box.
 *
 * @param arr The Sudoku grid.
 * @param row The row index of the given box.
 * @param col The column index of the given box.
 * @return The total number of empty boxes affected by the given box, excluding the given box itself.
 */
int totalEmptyBoxVariableAffected(int arr[N][N], int row, int col)
{
    int count = 0;
    int startRow = row - row % 3, startCol = col - col % 3;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (arr[i + startRow][j + startCol] == 0)
            {
                count++;
            }
        }
    }
    return count - 1;
}

/**
 * Returns a vector of pairs representing the most impacting variables based on a heuristic.
 * The variables are sorted in descending order of their impact.
 * The impact of a variable is determined by the total number of empty cells affected by that variable.
 * 
 * @param arr The Sudoku grid represented as a 2D array.
 * @return A vector of pairs, where each pair contains the coordinates of a variable and its impact.
 */
vector<pair<pair<int,int>, int>> mostImpactingVariableHeuristic(int arr[N][N])
{
    vector<pair<pair<int, int>, int>> v = mostConstrainedVariableHeuristic(arr);
    vector<pair<pair<int, int>, int>> res;


    for(int i = 0; i < v.size(); i++)
    {
        int row = v[i].first.first;
        int col = v[i].first.second;
        int totalEmptyRow = totalEmptyRowVariableAffected(arr, row);
        int totalEmptyCol = totalEmptyColVariableAffected(arr, col);
        int totalEmptyBox = totalEmptyBoxVariableAffected(arr, row, col);
        res.push_back({{row, col}, totalEmptyRow + totalEmptyCol + totalEmptyBox});
    }
    sort(res.begin(), res.end(), [](pair<pair<int, int>, int> a, pair<pair<int, int>, int> b) {
        return a.second > b.second;
    });

    vector<pair<pair<int, int>, int>> res2;
    for(int i = 0; i < res.size(); i++)
    {
        if(res[i].second == res[0].second)
        {
            res2.push_back(res[i]);
        }
    }
    return res2;

}


/**
 * Counts the number of empty cells in a Sudoku grid.
 * 
 * @param arr The Sudoku grid represented as a 2D array.
 * @return The count of empty cells in the grid.
 */
int countEmpty(int arr[N][N])
{
    int count = 0;
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            if(arr[i][j] == 0)
            {
                count++;
            }
        }
    }
    return count;
}

/**
 * Calculates the actual cost of the Sudoku puzzle solution.
 * The cost is determined by counting the number of cells that differ from the initial state.
 *
 * @param arr The Sudoku puzzle grid.
 * @return The actual cost of the Sudoku puzzle solution.
 */
int actualCost(int arr[N][N])
{
    int cost = 0;
    for(int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if(arr[i][j] != startState[i][j])
            {
                cost++;
            }
        }
    }
    return cost;
}


/**
 * Applies the A* algorithm to solve a Sudoku puzzle.
 * 
 * @param arr The Sudoku puzzle grid.
 */
void aStarSudoku(int arr[N][N])
{   
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            startState[i][j] = arr[i][j];
        }
    }
    // priority queue of next states and their heuristic + actual cost
    priority_queue<pair<double, int (*)[N]>, vector<pair<double, int (*)[N]>>, less<pair<double, int (*)[N]>>> pq;
    // set to store the visited states
    set<int (*)[N]> visited;
    // push the start state into the priority queue
    pq.push({mostImpactingVariableHeuristic(arr)[0].second, arr});
    long long iters = MAX_ITER;
    while(!pq.empty() && iters--)
    {
        int (*currState)[N] = pq.top().second;
        int currCost = pq.top().first;
        pq.pop();
        visited.insert(currState);
        if (isGoalState(currState))
        {
            for(int i = 0; i < N; i++)
            {
                for(int j = 0; j < N; j++)
                {
                    cout << currState[i][j] << " ";
                }
                cout << endl;
            }
            return;
        }
        
        vector<pair<pair<int, int>, int>> variableToAssign = mostImpactingVariableHeuristic(currState);
        for (int i = 0; i < variableToAssign.size(); i++)
        {
            
            int row = variableToAssign[i].first.first;
            int col = variableToAssign[i].first.second;
            int heuristic = variableToAssign[i].second;

            vector<pair<pair<int, int>, int>> possibilities = valuesForVariable(currState, row, col);
            for(int i = 0; i < possibilities.size(); i++)
            {
                int (*newState)[N] = new int[N][N];
                for(int j = 0; j < N; j++)
                {
                    for(int k = 0; k < N; k++)
                    {
                        newState[j][k] = currState[j][k];
                    }
                }
                newState[possibilities[i].first.first][possibilities[i].first.second] = possibilities[i].second;
                if(visited.find(newState) == visited.end())
                {
                    pq.push({heuristic + actualCost(newState), newState});
                }
            }
        }
        system("cls");
        for(int i = 0; i < N; i++)
        {
            for(int j = 0; j < N; j++)
            {
                cout << currState[i][j] << " ";
            }
            cout << endl;
        }
        cout << "Empty Cells: " << countEmpty(currState) << endl;
    }
}