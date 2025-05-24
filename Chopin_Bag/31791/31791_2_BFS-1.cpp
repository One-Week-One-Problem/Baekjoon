#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>

using namespace std;

// 감염 상태
enum class State {
    PROPAGATING = 0,
    INFECTED
};

// 바이러스 정보
struct Virus {
    int row, col;
    State state;
    int infection_lv; // PROPAGATING 상태에서 시간 지연 추적
    int start_time;   // PROPAGATING 시작 시간

    Virus(int r, int c, State s = State::INFECTED, int lv = 1, int t = 0)
        : row(r), col(c), state(s), infection_lv(lv), start_time(t) {}
};

int main() {
    //입출력 최적화
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    // 입력
    int grid_row, grid_col, time_total, time_delay, num_init_virus, num_building; //num_init_virus, num_building 변수는 사용하지 않으나, 문제의 필수 입력값임
    cin >> grid_row >> grid_col >> time_total >> time_delay >> num_init_virus >> num_building;

    
    vector<vector<char>> grid_input(grid_row, vector<char>(grid_col));

    

    // 디버깅용 입력
    // int grid_row = 5, grid_col = 5, time_delay = 1, time_total = 3;
    // // int num_init = 2, num_building = 3; // 이 변수들은 현재 사용되지 않음
    // vector<vector<char>> grid_input = { // grid_input으로 변경하여 is_building과 구분
    // {'.','.','.','.','.'},
    // {'.','.','*','#','.'},
    // {'.','*','#','.','.'},
    // {'.','.','#','.','.'}, 
    // {'.','.','.','.','.'}
    // };

    queue<Virus> virus_queue;
    vector<vector<bool>> is_building(grid_row, vector<bool>(grid_col, false));

    // 입력 처리
    for (int i = 0; i < grid_row; ++i) {
        for (int j = 0; j < grid_col; ++j) {
            cin >> grid_input[i][j];
            if (grid_input[i][j] == '*') {
                virus_queue.emplace(Virus(i, j, State::INFECTED, 1, 0));
            } else if (grid_input[i][j] == '#') {
                is_building[i][j] = true;
            }
        }
    }

    // 상태 추적: -1 (미방문), 0 (INFECTED), >0 (PROPAGATING, stores start_time)
    vector<vector<int>> status(grid_row, vector<int>(grid_col, -1));
    vector<pair<int, int>> directions = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
    

    // 초기 바이러스 상태 설정
    queue<Virus> initial_queue = virus_queue;
    while (!initial_queue.empty()) {
        Virus v = initial_queue.front();
        initial_queue.pop();
        status[v.row][v.col] = 0; // INFECTED
    }

    // BFS 시뮬레이션
    for (int t = 0; t < time_total&& !virus_queue.empty(); ++t) { 
        int queue_size = virus_queue.size(); // 현재 턴의 바이러스만 처리
        for (int i = 0; i < queue_size; ++i) {
            Virus current = virus_queue.front();
            virus_queue.pop();

            // PROPAGATING 상태에서 빌딩 처리
            if (current.state == State::PROPAGATING && is_building[current.row][current.col]) {
                if (current.infection_lv >= time_delay) {
                    // 1) INFECTED 로 전환
                    current.state = State::INFECTED;
                    status[current.row][current.col] = 0; // INFECTED
                    // 2) 큐에 다시 넣어야 다음 턴 전파가 가능
                    virus_queue.push(current);
                    continue;
                } else {
                    Virus next = current;
                    next.infection_lv++;
                    virus_queue.push(next);
                    continue;
                }
            }

            // INFECTED 상태에서만 전파
            if (current.state == State::INFECTED) {
                for (const auto& dir : directions) {
                    int nr = current.row + dir.first;
                    int nc = current.col + dir.second;

                    // 범위 체크 및 방문 여부 확인
                    if (nr >= 0 && nr < grid_row && nc >= 0 && nc < grid_col && status[nr][nc] == -1) {
                        if (is_building[nr][nc]) {
                            virus_queue.emplace(Virus(nr, nc, State::PROPAGATING, 1, t + 1));
                            status[nr][nc] = t + 1; // PROPAGATING 시작 시간
                        } else {
                            virus_queue.emplace(Virus(nr, nc, State::INFECTED, 1, 0));
                            status[nr][nc] = 0; // INFECTED
                        }
                    }
                }
            }
        }
    }

   // INFECTED 상태인 구역(status == 0)만 출력
//    for (int r = 0; r < grid_row; ++r) {
//        for (int c = 0; c < grid_col; ++c) {
//            if (status[r][c] == 0) {
//                cout << r+1 << " " << c+1 << "\n";
//            }
//        }
//    }
    

    // 안전 구역 찾기
    vector<pair<int, int>> safe_zones;
    for (int r = 0; r < grid_row; ++r) {
        for (int c = 0; c < grid_col; ++c) {
            if (status[r][c] == -1) {
                // 미방문 셀은 안전
                safe_zones.emplace_back(r + 1, c + 1);
            } else if (status[r][c] > 0 && is_building[r][c]) {
                // PROPAGATING 셀이며, time_total 내에 INFECTED가 되지 않는 경우
                int time_since_start = time_total - status[r][c] + 1; // PROPAGATING 기간
                if (time_since_start < time_delay) {
                    safe_zones.emplace_back(r + 1, c + 1);
                }
            }
        }
    }

    // 출력
    if (safe_zones.empty()) {
        cout << -1 << "\n";
    } else {
        // 행, 열 기준으로 정렬
        sort(safe_zones.begin(), safe_zones.end());
        for (const auto& zone : safe_zones) {
            cout << zone.first << " " << zone.second << "\n";
        }
    }

    return 0;
}