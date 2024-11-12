#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>

using namespace std;

const char EMPTY = '-';
const char HUMAN = 'X';
const char AI = 'O';
const int BOARD_SIZE = 4;
const int MAX_DEPTH = 6; // Limiting recursion depth for performance

// Function to initialize the board
vector<vector<char>> createBoard()
{
    return vector<vector<char>>(BOARD_SIZE, vector<char>(BOARD_SIZE, EMPTY));
}

// Function to print the board
void printBoard(const vector<vector<char>> &board)
{
    for (const auto &row : board)
    {
        for (char cell : row)
        {
            cout << cell << " ";
        }
        cout << endl;
    }
    cout << endl;
}

// Function to check for a winner
char checkWinner(const vector<vector<char>> &board)
{
    // Check rows and columns
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        if (all_of(board[i].begin(), board[i].end(), [](char c)
                   { return c == HUMAN; }))
            return HUMAN;
        if (all_of(board[i].begin(), board[i].end(), [](char c)
                   { return c == AI; }))
            return AI;

        bool colHumanWin = true, colAIWin = true;
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if (board[j][i] != HUMAN)
                colHumanWin = false;
            if (board[j][i] != AI)
                colAIWin = false;
        }
        if (colHumanWin)
            return HUMAN;
        if (colAIWin)
            return AI;
    }

    // Check diagonals
    bool diag1HumanWin = true, diag1AIWin = true;
    bool diag2HumanWin = true, diag2AIWin = true;
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        if (board[i][i] != HUMAN)
            diag1HumanWin = false;
        if (board[i][i] != AI)
            diag1AIWin = false;
        if (board[i][BOARD_SIZE - i - 1] != HUMAN)
            diag2HumanWin = false;
        if (board[i][BOARD_SIZE - i - 1] != AI)
            diag2AIWin = false;
    }
    if (diag1HumanWin || diag2HumanWin)
        return HUMAN;
    if (diag1AIWin || diag2AIWin)
        return AI;

    // Check for a tie
    bool isTie = true;
    for (const auto &row : board)
    {
        if (any_of(row.begin(), row.end(), [](char c)
                   { return c == EMPTY; }))
        {
            isTie = false;
            break;
        }
    }

    return isTie ? 'T' : '\0'; // 'T' for Tie, '\0' for ongoing game
}

// Minimax algorithm with alpha-beta pruning and depth limit
int minimax(vector<vector<char>> &board, int depth, bool isMaximizing, int alpha, int beta)
{
    char result = checkWinner(board);
    if (result == HUMAN)
        return -10 + depth;
    if (result == AI)
        return 10 - depth;
    if (result == 'T' || depth >= MAX_DEPTH)
        return 0;

    if (isMaximizing)
    {
        int maxEval = numeric_limits<int>::min();
        for (int i = 0; i < BOARD_SIZE; i++)
        {
            for (int j = 0; j < BOARD_SIZE; j++)
            {
                if (board[i][j] == EMPTY)
                {
                    board[i][j] = AI;
                    int eval = minimax(board, depth + 1, false, alpha, beta);
                    board[i][j] = EMPTY;
                    maxEval = max(maxEval, eval);
                    alpha = max(alpha, eval);
                    if (beta <= alpha)
                        break;
                }
            }
        }
        return maxEval;
    }
    else
    {
        int minEval = numeric_limits<int>::max();
        for (int i = 0; i < BOARD_SIZE; i++)
        {
            for (int j = 0; j < BOARD_SIZE; j++)
            {
                if (board[i][j] == EMPTY)
                {
                    board[i][j] = HUMAN;
                    int eval = minimax(board, depth + 1, true, alpha, beta);
                    board[i][j] = EMPTY;
                    minEval = min(minEval, eval);
                    beta = min(beta, eval);
                    if (beta <= alpha)
                        break;
                }
            }
        }
        return minEval;
    }
}

// Function to find the best move for AI
pair<int, int> findBestMove(vector<vector<char>> &board)
{
    int bestVal = numeric_limits<int>::min();
    pair<int, int> bestMove = {-1, -1};
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if (board[i][j] == EMPTY)
            {
                board[i][j] = AI;
                int moveVal = minimax(board, 0, false, numeric_limits<int>::min(), numeric_limits<int>::max());
                board[i][j] = EMPTY;
                if (moveVal > bestVal)
                {
                    bestVal = moveVal;
                    bestMove = {i, j};
                }
            }
        }
    }
    return bestMove;
}

// Main game loop
void playGame()
{
    vector<vector<char>> board = createBoard();
    cout << "4x4 Tic Tac Toe" << endl;
    printBoard(board);

    while (true)
    {
        // Human move
        int row, col;
        cout << "Enter your move (row and column): ";
        cin >> row >> col;
        if (row < 0 || row >= BOARD_SIZE || col < 0 || col >= BOARD_SIZE || board[row][col] != EMPTY)
        {
            cout << "Invalid move, try again." << endl;
            continue;
        }
        board[row][col] = HUMAN;
        printBoard(board);

        // Check for winner after human move
        char winner = checkWinner(board);
        if (winner != '\0')
        {
            if (winner == HUMAN)
                cout << "You win!" << endl;
            else if (winner == AI)
                cout << "AI wins!" << endl;
            else
                cout << "It's a tie!" << endl;
            break;
        }

        // AI move
        cout << "AI's turn:" << endl;
        pair<int, int> aiMove = findBestMove(board);
        if (aiMove.first == -1 && aiMove.second == -1)
        {
            cout << "It's a tie!" << endl;
            break;
        }
        board[aiMove.first][aiMove.second] = AI;
        printBoard(board);

        // Check for winner after AI move
        winner = checkWinner(board);
        if (winner != '\0')
        {
            if (winner == HUMAN)
                cout << "You win!" << endl;
            else if (winner == AI)
                cout << "AI wins!" << endl;
            else
                cout << "It's a tie!" << endl;
            break;
        }
    }
}

// Entry point
int main()
{
    playGame();
    return 0;
}
