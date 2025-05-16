#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <utility>

using namespace std;

// 감염상태
enum class State{
    NORMAL = 0, // NORMAL 은 아마 쓰이지 않음
    PROPAGATING,
    INFECTED
};

// 타도 유해조류 산지니 바이러스
class Virus {
    public:
        State state_;
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
            vector<pair<int, int>>& virus_pos, vector<Virus>& viruses){

            vector<Virus> ret_vec;

            if(is_building[row_][col_] && state_ == State::PROPAGATING){
                if(infection_lv_ == time_delay) {
                    state_ = State::INFECTED;
                    cout << get_status() << "(building) status changed : P -> I" << endl; // 디버깅용 출력
                }
                else infection_lv_++;
            }

            if(state_ == State::PROPAGATING){
               state_ = State::INFECTED;
               cout << get_status() << "status changed : P -> I" << endl; // 디버깅용 출력
               virus_pos.emplace_back(make_pair(row_,col_));
               return ret_vec; 
            }

            vector<pair<int,int>> offsets{{1,0}, {0,1}, {-1,0}, {0,-1}};
            
            cout << "[TEST] " << row_+1 << "," << col_+1 << endl; // 디버깅용 출력

            
            for (auto p : offsets){

                cout << "[OFFSET] (" << p.first << "," << p.second << ")" << endl; // 디버깅용 출력

                if(status_check(row_+p.first, col_+p.second, size_row, size_col, virus_pos, viruses)){
                    ret_vec.emplace_back(Virus(row_+p.first, col_+p.second, State::PROPAGATING));
                }
            }
            return ret_vec;
        }

        // row, col : 확인할 칸의 좌표정보, size_row, col : 전체 보드의 크기정보

        bool status_check(int row, int col, int size_row, int size_col,
            vector<pair<int, int>> virus_pos, vector<Virus> viruses){

            cout << "[POINT] " << row+1 << "," << col+1 << endl; // 디버깅용 출력

            if(row < 0 || col < 0 || row >= size_row || col >= size_col) {

                cout << "Invalid : size issue" << '\n' << endl; // 디버깅용 출력
                return false;
            }
            if(find(virus_pos.begin(), virus_pos.end(),make_pair(row, col)) != virus_pos.end()){

                cout << "Invalid : virus infected" << '\n'  << endl; // 디버깅용 출력
                return false;
            }
            if(find_if(viruses.begin(), viruses.end(), [row, col](Virus i){
                return (i.row_ == row) && (i.col_ == col) && (i.state_ == State::PROPAGATING);
            }) != viruses.end()) {

                cout << "Invalid : virus propagating" << '\n'  << endl; // 디버깅용 출력
                return false;
            }

            cout << "Valid\n" << endl; // 디버깅용 출력
            return true;
        }
        
        //디버깅용 
        string get_status(){
            return "(" + to_string(row_+1) + "," + to_string(col_+1) + ")";
        }

    private:
    int row_, col_;
    int infection_lv_=0;
};



int main() {
    
    // cout << "Enter the size of Grid: Row Column: " << endl; // 디버깅용 출력
    // int grid_row, grid_col;
    // cin >> grid_row >> grid_col;
    // cin.ignore();

    // cout << "Enter the delayed time, the spreading time,"
    // << " the number of building, the number of initial virus point: " << endl; // 디버깅용 출력
    // int time_delay, time_total, num_init, num_building;
    // string line;
    // getline(cin, line); 
    // stringstream ss(line);
    // ss >> time_delay >> time_total >> num_init >> num_building;

    // vector<string> grid(grid_row, string(grid_col, ' ')); // 입력
    // for (int i = 0; i < grid_row; ++i) {
    //     getline(cin, line);
    //     stringstream row_ss(line);
    //     int col = 0;
    //     char cell;
    //     while (row_ss >> cell && col < grid_col) {
    //         grid[i][col++] = cell;
    //     }
    // }

    // 디버깅용 입력
    int grid_row = 5, grid_col = 5, time_delay = 1, time_total = 3, num_init = 2, num_building = 3;
    vector<vector<char>> grid = {
    {'.','.','.','.','.'},
    {'.','.','*','#','.'},
    {'.','*','#','.','.'},
    {'.','.','#','.','.'}, 
    {'.','.','.','.','.'}
};

    // 바이러스 위치 및 건물 위치 파악
    vector<pair<int, int>> virus_pos; // 바이러스 현황
    vector<vector<bool>> is_building(grid_row, vector<bool>(grid_col, false)); // 빌딩이 있는가?
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
    // 입력값 검증

    // 바이러스 객체 벡터
    vector<Virus> viruses;
    // 초기화 설정
    for(auto i : virus_pos){
        viruses.emplace_back(Virus(i.first, i.second, State::INFECTED));
    }


    // // 시뮬레이션 시작 : 전체 반복
    for(int t = 0; t < time_total; ++t){
        // 바이러스 객체 별로 1시간 동안의 행위 시작
        vector<Virus> temp_vec;
        for (Virus& v : viruses){
            vector<Virus> bin = v.propagate(is_building,time_delay, grid_row, grid_col, virus_pos, viruses);
            temp_vec.insert(temp_vec.end(),bin.begin(),bin.end());
        }
        viruses.insert(viruses.end(),temp_vec.begin(),temp_vec.end());
    }
    sort(viruses.begin(), viruses.end());
    viruses.erase(std::unique(viruses.begin(), viruses.end()), viruses.end());

    // 1회만 시행
    // vector<Virus> temp_vec;
    // for (Virus& v : viruses){
    //     vector<Virus> bin = v.propagate(is_building,time_delay, grid_row, grid_col, virus_pos, viruses);
    //     temp_vec.insert(temp_vec.end(),bin.begin(),bin.end());
    // }
    // viruses.insert(viruses.end(),temp_vec.begin(),temp_vec.end());
    
    for(Virus& i : viruses){
        cout << i.get_status() << endl;
    }
}
