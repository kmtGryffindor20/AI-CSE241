#define ll long long
#define vin vector<int>
#define um unordered_map
using namespace std;
#include <bits/stdc++.h>
#include <chrono>
/**
 * Prints the current state of the chessboard.
 * 
 * @param board The 2D array representing the chessboard.
 * @param n The size of the chessboard.
 */
void printBoard(int **board, int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << "Row " << i << ": ";
        for (int j = 0; j < n; j++)
        {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
   
}



/**
 * Initializes the chessboard with random queen positions.
 * 
 * @param board The 2D array representing the chessboard.
 * @param allQueenPositions A vector to store the positions of all the queens.
 * @param n The size of the chessboard.
 */
void initializeBoard(int **board, vector<pair<int, int>>* allQueenPositions, int n)
{
    for (int i = 0; i < n; i++)
    {
        int x = rand() % n;
        board[x][i] = 1;
        (*allQueenPositions)[i] = {x, i};
    }
}

/**
 * @brief Reinitializes the chessboard and queen positions.
 * 
 * This function resets the chessboard by setting all the cells to 0 and
 * repositions the queens randomly on the board.
 * 
 * @param board The 2D array representing the chessboard.
 * @param allQueenPositions A vector containing the positions of all the queens.
 * @param n The size of the chessboard.
 */
void reinitializeBoard(int **board, vector<pair<int, int>>* allQueenPositions, int n)
{
    for (int i = 0; i < n; i++)
    {
        board[(*allQueenPositions)[i].first][(*allQueenPositions)[i].second] = 0;
        (*allQueenPositions)[i] = {0, 0};
    }

    initializeBoard(board, allQueenPositions, n);
    
}   



/**
 * Calculates the error value for a given set of queen positions on an N-Queens board.
 * The error value represents the number of conflicts between queens.
 * A conflict occurs when two queens are in the same row, column, or diagonal.
 *
 * @param allQueenPositions A pointer to a vector containing the positions of all queens.
 * @param n The size of the N-Queens board.
 * @return The error value, representing the number of conflicts between queens.
 */
int calculateError(vector<pair<int, int>> *allQueenPositions, int n)
{
    int error = 0;
    for (int i = 0; i < n; i++)
    {
        int x = (*allQueenPositions)[i].first;
        int y = (*allQueenPositions)[i].second;
        for (int j = 0; j < n; j++)
        {
            if (i == j)
                continue;
            int x1 = (*allQueenPositions)[j].first;
            int y1 = (*allQueenPositions)[j].second;
            if (x == x1 || y == y1 || abs(x - x1) == abs(y - y1))
                error++;
        }
    }
    return error;
}

/**
 * Finds the queen with the maximum error on the chessboard.
 * 
 * @param board The chessboard represented as a 2D array.
 * @param allQueenPositions A vector containing the positions of all the queens on the chessboard.
 * @param n The size of the chessboard.
 * @return The index of the queen with the maximum error.
 */
int queenWithMaxError(int **board, vector<pair<int, int>> *allQueenPositions, int n)
{
    int maxError = 0;
    int maxErrorQueen = 0;
    for (int i = 0; i < n; i++)
    {
        int x = (*allQueenPositions)[i].first;
        int y = (*allQueenPositions)[i].second;
        int error = 0;
        for (int j = 0; j < n; j++)
        {
            if (i == j)
                continue;
            int x1 = (*allQueenPositions)[j].first;
            int y1 = (*allQueenPositions)[j].second;
            if (x == x1 || y == y1 || abs(x - x1) == abs(y - y1))
                error++;
        }
        if (error > maxError)
        {
            maxError = error;
            maxErrorQueen = i;
        }
    }
    return maxErrorQueen;
}


/**
 * Moves the queen up by one position on the chessboard.
 * 
 * @param board The chessboard represented as a 2D array.
 * @param allQueenPositions A vector containing the positions of all the queens on the chessboard.
 * @param n The size of the chessboard.
 * @param i The index of the queen to be moved.
 * @return The error value after moving the queen up.
 */
int moveQueenUp(int **board, vector<pair<int, int>> *allQueenPositions, int n, int i)
{
    int x = (*allQueenPositions)[i].first;
    int y = (*allQueenPositions)[i].second;
    if (x == 0)
        return INT32_MAX;
    
    int **boardCopy = new int *[n];
    for (int i = 0; i < n; i++)
        boardCopy[i] = new int[n];

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            boardCopy[i][j] = board[i][j];

    boardCopy[x][y] = 0;
    boardCopy[x - 1][y] = 1;

    vector<pair<int, int>> allQueenPositionsCopy(n);
    for (int i = 0; i < n; i++)
        allQueenPositionsCopy[i] = (*allQueenPositions)[i];

    allQueenPositionsCopy[i] = {x - 1, y};

    return calculateError(&allQueenPositionsCopy, n);
}

/**
 * Moves the queen down one row on the chessboard.
 * 
 * @param board The chessboard represented as a 2D array.
 * @param allQueenPositions A vector containing the positions of all the queens on the chessboard.
 * @param n The size of the chessboard.
 * @param i The index of the queen to be moved.
 * @return The error value after moving the queen down.
 */
int moveQueenDown(int **board, vector<pair<int, int>> *allQueenPositions, int n, int i)
{
    int x = (*allQueenPositions)[i].first;
    int y = (*allQueenPositions)[i].second;
    if (x == n-1)
        return INT32_MAX;
    
    int **boardCopy = new int *[n];
    for (int i = 0; i < n; i++)
        boardCopy[i] = new int[n];

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            boardCopy[i][j] = board[i][j];

    boardCopy[x][y] = 0;
    boardCopy[x + 1][y] = 1;

    vector<pair<int, int>> allQueenPositionsCopy(n);
    for (int i = 0; i < n; i++)
        allQueenPositionsCopy[i] = (*allQueenPositions)[i];

    allQueenPositionsCopy[i] = {x + 1, y};

    return calculateError(&allQueenPositionsCopy, n);
}

int main()
{
    int n;
    cin >> n;
    int** board = new int*[n];
    for (int i = 0; i < n; i++)
        board[i] = new int[n];

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            board[i][j] = 0;

    vector<pair<int, int>> allQueenPositions(n);

    initializeBoard(board, &allQueenPositions, n);

    printBoard(board, n);

    int main_error = calculateError(&allQueenPositions, n);

    chrono::steady_clock::time_point begin = chrono::steady_clock::now();
    while(main_error > 0){

        int queen = queenWithMaxError(board, &allQueenPositions, n);
        int up = moveQueenUp(board, &allQueenPositions, n, queen);
        int down = moveQueenDown(board, &allQueenPositions, n, queen);

        cout << "Queen: " << queen << endl;
        cout << "Up: " << up << " Down: " << down << " Current: " << main_error << endl;

        printBoard(board, n);
        int minError = min(up, down);

        if (minError != 0 and minError >= main_error)
        {
            cout << "Reinitializing board" << endl;
            reinitializeBoard(board, &allQueenPositions, n);
            main_error = calculateError(&allQueenPositions, n);
            continue;
        }
        else if(minError == INT64_MAX)
            break;
        else if(minError == up){
            cout << "Moving queen " << queen << " up" << endl;
            board[allQueenPositions[queen].first][allQueenPositions[queen].second] = 0;
            board[allQueenPositions[queen].first - 1][allQueenPositions[queen].second] = 1;
            allQueenPositions[queen].first--;
        }
        else if(minError == down){
            cout << "Moving queen " << queen << " down" << endl;
            board[allQueenPositions[queen].first][allQueenPositions[queen].second] = 0;
            board[allQueenPositions[queen].first + 1][allQueenPositions[queen].second] = 1;
            allQueenPositions[queen].first++;
        }
        main_error = calculateError(&allQueenPositions, n);
       
    }
    chrono::steady_clock::time_point end = chrono::steady_clock::now();

    printBoard(board, n);

    cout << "Time taken: " << chrono::duration_cast<chrono::milliseconds>(end - begin).count() << " milliseconds" << endl;
    // Deallocate memory
    for (int i = 0; i < n; i++)
        delete[] board[i];
    delete[] board;
}