#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

// khai báo kích thước bàn cờ
const int ROWS = 10;
const int COLS = 10;
const int NUM_MINES = 10;

// khai báo kiểu dữ liệu ô cờ
struct Cell {
    bool isMine; // có mìn hay không
    bool isRevealed; // đã được mở ra hay chưa
    int numAdjacentMines; // số lượng ô có mìn xung quanh
};

// tạo bàn cờ mới với các ô chưa được mở ra
vector<vector<Cell>> createBoard() {
    vector<vector<Cell>> board(ROWS, vector<Cell>(COLS));
    for (int row = 0; row < ROWS; row++) {
        for (int col = 0; col < COLS; col++) {
            board[row][col].isMine = false;
            board[row][col].isRevealed = false;
            board[row][col].numAdjacentMines = 0;
        }
    }
    return board;
}

// tạo mìn ngẫu nhiên trên bàn cờ
void placeMines(vector<vector<Cell>>& board, int numMines) {
    int numPlacedMines = 0;
    while (numPlacedMines < numMines) {
        int row = rand() % ROWS;
        int col = rand() % COLS;
        if (!board[row][col].isMine) {
            board[row][col].isMine = true;
            numPlacedMines++;
        }
    }
}

// tính số lượng ô có mìn xung quanh của từng ô trên bàn cờ
void calculateAdjacentMines(vector<vector<Cell>>& board) {
    for (int row = 0; row < ROWS; row++) {
        for (int col = 0; col < COLS; col++) {
            if (board[row][col].isMine) {
                continue; // nếu ô hiện tại là mìn thì bỏ qua
            }
            int count = 0;
            for (int r = row - 1; r <= row + 1; r++) {
                for (int c = col - 1; c <= col + 1; c++) {
                    if (r >= 0 && r < ROWS && c >= 0 && c < COLS && board[r][c].isMine) {
                        count++;
                    }
                }
            }
            board[row][col].numAdjacentMines = count;
        }
    }
}

// hiển thị bàn cờ
void displayBoard(vector<vector<Cell>>& board) {
    cout << "    ";
    for (int j = 0; j < COLS; ++j) {
        cout << j << " ";
    }
    cout << endl;
    cout << "   ";
    for (int j = 0; j < COLS; ++j) {
        cout << "__";
    }
    cout << endl;
    for (int i = 0; i < ROWS; ++i) {
        cout << i << " | ";
        for (int j = 0; j < COLS; ++j) {
            if (!board[i][j].isRevealed) {
                cout << ". ";
            }
            else if (board[i][j].isMine) {
                cout << "* ";
            }
            else {
                cout << board[i][j].numAdjacentMines << " ";
            }
        }
        cout << endl;
    }
}

// mở một ô cờ
bool revealCell(vector<vector<Cell>>& board, int row, int col) {
    if (board[row][col].isMine) {
        board[row][col].isRevealed = true;
        return false; // ô hiện tại là mìn
    }
    if (board[row][col].isRevealed) {
        return true; // ô đã được mở trước đó
    }
    board[row][col].isRevealed = true;
    if (board[row][col].numAdjacentMines == 0) {
        // nếu ô không có mìn xung quanh, tiến hành mở các ô xung quanh
        for (int r = row - 1; r <= row + 1; r++) {
            for (int c = col - 1; c <= col + 1; c++) {
                if (r >= 0 && r < ROWS && c >= 0 && c < COLS) {
                    revealCell(board, r, c);
                }
            }
        }
    }
    return true;
}

int main() {
    srand(time(NULL)); // khởi tạo seed cho hàm rand()
    vector<vector<Cell>> board = createBoard();
    placeMines(board, NUM_MINES);
    calculateAdjacentMines(board);
    bool gameOver = false;
    while (!gameOver) {
        displayBoard(board);
        int row, col;
        cout << "Enter row and column (separated by space): ";
        cin >> row >> col;
        gameOver = !revealCell(board, row, col);
    }
    cout << "Game over!" << endl;
    return 0;
}

