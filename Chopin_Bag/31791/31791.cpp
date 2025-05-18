#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <utility>

using namespace std;

// 감염상태
enum class State{
    PROPAGATING = 0,
    INFECTED
};

// 타도 유해조류 산지니 바이러스
class Virus {
    public:
        State state_;
        int row_, col_;
        int infection_lv_= 1;

        Virus()= default;
        Virus(int row, int col, State state=State::INFECTED)
        :row_{row}, col_{col}, state_{state}
        {};

        // std::sort를 위한 비교 연산자
        bool operator<(const Virus& other) const {
            if (row_ != other.row_) {
                return row_ < other.row_;
            }
            if (col_ != other.col_) {
                return col_ < other.col_;
            }
            return state_ < other.state_; // 상태도 비교 기준에 포함
        }

        // std::unique를 위한 동등 연산자
        bool operator==(const Virus& other) const {
            return row_ == other.row_ &&
                   col_ == other.col_ &&
                   state_ == other.state_; // 상태도 동일성 판단에 포함
        }

        vector<Virus> propagate(const vector<vector<bool>> is_building, const int time_delay, 
            const int size_row, const int size_col,
            const vector<Virus>& current_viruses, const vector<Virus>& temp_new_viruses){ 

            vector<Virus> ret_vec;

            if(is_building[row_][col_] && state_ == State::PROPAGATING){
                if(infection_lv_ == time_delay) {
                    state_ = State::INFECTED; // 상태만 변경
                    // cout << get_status() << "[STATUS][B] P -> I" << endl; // 디버깅용 출력
                }
                else {
                    infection_lv_++;
                    // cout << get_status() << "[STATUS][B] infection lv" << infection_lv_-1 << "->" << infection_lv_ << endl; // 디버깅용 출력
                }
                return ret_vec; // 이번 턴 전파 없음
            }

            // 건물이 아닌 곳에서 Propagate 함수가 실행되었다는 것은, 이미 state_ == State::INFECTED 라는 뜻이 아닐까?

            // if(state_ == State::PROPAGATING){ // 건물 아닌 곳의 PROPAGATING
            //    state_ = State::INFECTED; // 상태만 변경
            //    cout << get_status() << "[STATUS] P -> I" << endl; // 디버깅용 출력
            //    return ret_vec; // 이번 턴 전파 없음
            // }

            // INFECTED 상태일 때만 전파 시도
            if (state_ == State::INFECTED) {
                vector<pair<int,int>> offsets{{1,0}, {0,1}, {-1,0}, {0,-1}};
                
                // cout << "_____________________________________________________________________" << endl; // 디버깅용 출력
                // cout << "[TEST] " << get_status() << " is INFECTED and trying to spread\n" << endl; // 디버깅용 출력
                
                for (auto p : offsets){
                    int next_row = row_ + p.first;
                    int next_col = col_ + p.second;

                    // cout << "[OFFSET] (" << p.first << "," << p.second << ")" << " | "; // 디버깅용 출력

                    if(status_check(next_row, next_col, size_row, size_col, current_viruses, temp_new_viruses)){
                        if(is_building[next_row][next_col]) ret_vec.emplace_back(Virus(next_row, next_col, State::PROPAGATING));
                        else ret_vec.emplace_back(Virus(next_row, next_col, State::INFECTED)); 
                    }
                }
            }
            return ret_vec;
        }

        // row, col : 확인할 칸의 좌표정보, size_row, col : 전체 보드의 크기정보
        bool status_check(int row, int col, int size_row, int size_col,
            const vector<Virus>& current_viruses, const vector<Virus>& temp_new_viruses){ // 파라미터 변경

            // cout << "[POINT] " << row+1 << "," << col+1 << " | "; // 디버깅용 출력

            if(row < 0 || col < 0 || row >= size_row || col >= size_col) {
                // cout << "Invalid : size issue" << '\n' << endl; // 디버깅용 출력
                return false;
            }

            // current_viruses 목록에서 해당 위치에 INFECTED 또는 PROPAGATING 바이러스가 있는지 확인
            for(const auto& v : current_viruses) {
                if (v.row_ == row && v.col_ == col) {
                    // cout << "Invalid : virus (state: " << (int)v.state_ << ") already exists in current_viruses" << '\n' << endl; // 디버깅용 출력
                    return false; // 이미 어떤 상태로든 바이러스가 존재하면 전파 불가
                }
            }

            // temp_new_viruses (이번 턴에 새로 생성된 PROPAGATING 바이러스) 목록에 있는지 확인
            for(const auto& v : temp_new_viruses) {
                 if (v.row_ == row && v.col_ == col) {
                    // cout << "Invalid : virus (PROPAGATING) already exists in temp_new_viruses" << '\n' << endl; // 디버깅용 출력
                    return false;
                 }
            }
            
            // cout << "Valid\n" << endl; // 디버깅용 출력
            return true;
        }
        
        //디버깅용 
        string get_status(){
            return "(" + to_string(row_+1) + "," + to_string(col_+1) + ")";
        }
};



int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    // 디버깅용 입력
    int grid_row, grid_col, time_delay, time_total, num_init_virus, num_building;
    cin >> grid_row >> grid_col;
    cin >> time_total >> time_delay >> num_init_virus >> num_building;
    
    vector<Virus> viruses; // 바이러스 객체 벡터
    vector<vector<bool>> is_building(grid_row, vector<bool>(grid_col, false)); // 빌딩이 있는가?    

    vector<vector<char>> grid_input(grid_row, vector<char>(grid_col)); // grid_input으로 변경하여 is_building과 구분

    

    for (int i = 0; i < grid_row; ++i) {
        for (int j = 0; j < grid_col; ++j) {
            cin >> grid_input[i][j]; // 각 문자를 grid_input에 직접 저장
            if (grid_input[i][j] == '*') {
                viruses.emplace_back(Virus(i, j, State::INFECTED)); // 초기 바이러스는 INFECTED
            } else if (grid_input[i][j] == '#') {
                is_building[i][j] = true;
            }
        }
    }

    // 시뮬레이션 시작 : 전체 반복
    for(int t = 0; t < time_total; ++t){ // t < time_total 로 바꿀 것
        vector<Virus> temp_newly_propagated_viruses; // 이번 턴에 새로 전파된 바이러스들
        
        size_t current_virus_count = viruses.size(); // 루프 시작 시점의 바이러스 수
        for (size_t i = 0; i < current_virus_count; ++i) {
            // propagate 함수는 바이러스 자신의 상태를 변경하거나, 새로운 바이러스를 생성함
            // propagate 호출 시 current_viruses와 temp_newly_propagated_viruses를 const&로 전달
            vector<Virus> propagated_in_this_step = viruses[i].propagate(is_building, time_delay, grid_row, grid_col, viruses, temp_newly_propagated_viruses);
            temp_newly_propagated_viruses.insert(temp_newly_propagated_viruses.end(), propagated_in_this_step.begin(), propagated_in_this_step.end());
        }
        
        viruses.insert(viruses.end(), temp_newly_propagated_viruses.begin(), temp_newly_propagated_viruses.end());

        // 매 턴 종료 후 중복 제거 및 정렬
        sort(viruses.begin(), viruses.end());
        viruses.erase(std::unique(viruses.begin(), viruses.end()), viruses.end());
    }

    // INFECTED 상태의 바이러스 좌표 출력 - 디버깅용 출력
    // cout << "\n\nFinal OUTPUT\n" << endl; // 디버깅용 출력
    // for(auto& v : viruses){ // const auto& 사용
    //     if(v.state_ == State::INFECTED) cout << v.get_status() << endl;
    //     if(v.state_ == State::PROPAGATING) cout << "[Propagating]" << v.get_status() << ", lv: " << v.infection_lv_ << endl;
    // }

    vector<vector<bool>> is_infected_grid(grid_row, vector<bool>(grid_col, false));
    int is_exist = grid_col * grid_row;
    for (const auto& virus : viruses) {
        if (virus.state_ == State::INFECTED) {
            if (virus.row_ >= 0 && virus.row_ < grid_row && virus.col_ >= 0 && virus.col_ < grid_col) { // 혹시 모를 범위 체크
                is_infected_grid[virus.row_][virus.col_] = true;
                is_exist--;
            }
        }
    }

    if(is_exist==0){
        cout << -1;
        return 0;
    }

    bool found_safe_zone = false;
    for (int r = 0; r < grid_row; ++r) {
        for (int c = 0; c < grid_col; ++c) {
            if (!is_infected_grid[r][c]) {
                // 문제에서 요구하는 출력 형식 (예: "행번호 열번호")
                cout << r + 1 << " " << c + 1 << "\n";
                found_safe_zone = true;
            }
        }
    }
    return 0;
}