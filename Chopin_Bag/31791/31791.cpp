#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

// 타도 유해조류 산지니 바이러스
class Virus {
    public:
        Virus()= default;

    private:
};

int main() {
    
    cout << "Enter the size of Grid: Row Column: " << endl; // 디버깅용 출력
    int grid_row, grid_col;
    cin >> grid_row >> grid_col;
    cin.ignore();

    cout << "Enter the delayed time, the spreading time, the number of building, the number of initial virus point: " << endl; // 디버깅용 출력
    int time_delay, time_spread, num_init, num_building;
    string line;
    getline(cin, line); 
    stringstream ss(line);
    ss >> time_delay >> time_spread >> num_init >> num_building;

    
    vector<string> grid(grid_row, string(grid_col, ' '));
    for (int i = 0; i < grid_row; ++i) {
        getline(cin, line);
        stringstream row_ss(line);
        int col = 0;
        char cell;
        while (row_ss >> cell && col < grid_col) {
            grid[i][col++] = cell;
        }
    }

    // 바이러스 위치 및 건물 위치 파악
    vector<pair<int, int>> virus_pos;
    vector<vector<bool>> is_building(grid_row, vector<bool>(grid_col, false));
    for (int i = 0; i < grid_row; ++i) {
        for (int j = 0; j < grid_col; ++j) {
            if (grid[i][j] == '*') {
                virus_pos.emplace_back(i, j);
            } else if (grid[i][j] == '#') {
                is_building[i][j] = true;
            }
        }
    }

    // 여기까지가 입력처리
}
