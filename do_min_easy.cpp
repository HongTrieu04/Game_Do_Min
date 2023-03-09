#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

// Hàm sinh bản đồ mìn
vector<vector<int>> generate_map(int m, int n, int k) {
    // Tạo một vector 2 chiều để lưu bản đồ mìn
    vector<vector<int>> mine_map(m, vector<int>(n, 0));
    int count = 0;
    // Sinh ngẫu nhiên K quả mìn
    while (count < k) {
        int x = rand() % m;
        int y = rand() % n;
        if (mine_map[x][y] == 0) {
            mine_map[x][y] = 9; // Đánh dấu ô chứa mìn bằng số 9
            count++;
        }
    }
    // Tính số mìn xung quanh mỗi ô trống
 /*   for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (mine_map[i][j] == 9) continue;
            int count = 0;
            if (i > 0 && j > 0 && mine_map[i - 1][j - 1] == 9) count++;
            if (i > 0 && mine_map[i - 1][j] == 9) count++;
            if (i > 0 && j < n - 1 && mine_map[i - 1][j + 1] == 9) count++;
            if (j > 0 && mine_map[i][j - 1] == 9) count++;
            if (j < n - 1 && mine_map[i][j + 1] == 9) count++;
            if (i < m - 1 && j > 0 && mine_map[i + 1][j - 1] == 9) count++;
            if (i < m - 1 && mine_map[i + 1][j] == 9) count++;
            if (i < m - 1 && j < n - 1 && mine_map[i + 1][j + 1] == 9) count++;
            mine_map[i][j] = count;
        }
    }*/
    return mine_map;
}

int main() {
    // Thiết lập seed cho hàm sinh số ngẫu nhiên
    srand(time(NULL));
    // Nhập kích thước bản đồ và số lượng mìn từ bàn phím
    int m, n, k;
    cout << "Nhap kich thuoc ban do (m, n) va so luong min (k): ";
    cin >> m >> n >> k;
    // Sinh bản đồ mìn
    vector<vector<int>> mine_map = generate_map(m, n, k);
    // Lặp đến khi người chơi chọn ô có mìn hoặc đã mở tất cả các ô trống
    int open_count = 0;
    while (open_count < m * n - k) {
        // Hiển thị bản đồ hiện tại
        cout << "Ban do hien tai:\n";
        if (open_count == 0) {
            for (int i = 0; i < m; i++) {
                for (int j = 0; j < n; j++) {
                    cout << " . ";
                    /*if (mine_map[i][j] == 9) {
                        cout << " * ";
                    }
                    else if (mine_map[i][j] == -1) {
                        cout << " X ";
                    }
                    else if (mine_map[i][j] == 0) {
                        cout << " . ";
                    }
                    else {
                        cout << " " << mine_map[i][j] << " ";
                    }*/
                }
                cout << endl;
            }
        }
        // Nhập tọa độ ô cần mở từ bàn phím
        int x, y;
        do {
            cout << "Nhap toa do o (x, y): ";
            cin >> x >> y;
        } while (x >= m || y >= n || mine_map[x][y] == -2);
        
        // Kiểm tra ô có mìn hay không
        if (mine_map[x][y] == 9) {
            mine_map[x][y] = -1;
            cout << "YOU'RE DEAD!" << endl;
            // In lại bản đồ với tất cả các quả mìn ra màn hình
            cout << "Ban do hoan tat:\n";
            for (int i = 0; i < m; i++) {
                for (int j = 0; j < n; j++) {
                    if (mine_map[i][j] == 0) {
                        cout << " . ";
                    }
                    else if (mine_map[i][j] == -1) {
                        cout << " X ";
                    }
                    else if (mine_map[i][j] == -2) {
                        cout << " O ";
                    }
                    else if (mine_map[i][j] == 9) {
                        cout << " * ";
                    }
                }
                cout << endl;
            }
            break; // Kết thúc trò chơi
        }
        else {
            mine_map[x][y] = -2;
            for (int i = 0; i < m; i++) {
                for (int j = 0; j < n; j++) {
                    if (mine_map[i][j] == -2) cout << " O ";
                    else cout << " . ";
                }
                cout << endl;
            }
            open_count++;
        }
    }
    if (open_count == m * n - k) {
        cout << "YOU WIN" << endl << "Ban do hoan tat:" << endl;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (mine_map[i][j] == 9) cout << " * ";
                else cout << " O ";
            }
            cout << endl;
        }
    }
}