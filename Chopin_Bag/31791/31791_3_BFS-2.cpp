#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

enum class State { PROPAGATING, INFECTED };

struct Virus {
    int row, col;
    State state;
    int infection_lv;
    int start_time;
    Virus(int r, int c, State s = State::INFECTED, int lv = 1, int t = 0)
        : row(r), col(c), state(s), infection_lv(lv), start_time(t) {}
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int N, M;
    long long Tg, Tb;
    int X, B;
    cin >> N >> M >> Tg >> Tb >> X >> B;

    vector<pair<int,int>> safe_zones(X), bact_zones(B);
    for (int i = 0; i < X; ++i) {
        cin >> safe_zones[i].first >> safe_zones[i].second;
        --safe_zones[i].first; --safe_zones[i].second;
    }
    for (int i = 0; i < B; ++i) {
        cin >> bact_zones[i].first >> bact_zones[i].second;
        --bact_zones[i].first; --bact_zones[i].second;
    }

    vector<vector<bool>> is_building(N, vector<bool>(M,false));
    vector<vector<int>> status(N, vector<int>(M,-1));
    queue<Virus> q;
    // 박테리아 초기 위치
    for (auto &p : bact_zones) {
        q.emplace(p.first, p.second, State::INFECTED);
        status[p.first][p.second] = 0;
    }
    // 초기 안전지대
    for (auto &p : safe_zones) {
        is_building[p.first][p.second] = true;
        status[p.first][p.second] = 0;
    }

    vector<pair<int,int>> dirs = {{1,0},{0,1},{-1,0},{0,-1}};
    for (int t = 0; t < Tg && !q.empty(); ++t) {
        int sz = q.size();
        while (sz--) {
            Virus cur = q.front(); q.pop();
            if (cur.state == State::PROPAGATING && is_building[cur.row][cur.col]) {
                if (cur.infection_lv >= Tb) {
                    cur.state = State::INFECTED;
                    status[cur.row][cur.col] = 0;
                    q.push(cur);
                } else {
                    cur.infection_lv++;
                    q.push(cur);
                }
                continue;
            }
            if (cur.state == State::INFECTED) {
                for (auto &d : dirs) {
                    int nr = cur.row + d.first, nc = cur.col + d.second;
                    if (nr < 0 || nr >= N || nc < 0 || nc >= M || status[nr][nc] != -1)
                        continue;
                    if (is_building[nr][nc]) {
                        q.emplace(nr, nc, State::PROPAGATING, 1, t + 1);
                        status[nr][nc] = t + 1;
                    } else {
                        q.emplace(nr, nc, State::INFECTED);
                        status[nr][nc] = 0;
                    }
                }
            }
        }
    }

    vector<pair<int,int>> ans;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            if (status[i][j] == -1) {
                ans.emplace_back(i + 1, j + 1);
            } else if (status[i][j] > 0 && is_building[i][j]) {
                int elapsed = Tg - status[i][j] + 1;
                if (elapsed < Tb)
                    ans.emplace_back(i + 1, j + 1);
            }
        }
    }

    if (ans.empty()) {
        cout << -1;
    } else {
        sort(ans.begin(), ans.end());
        for (auto &p : ans)
            cout << p.first << ' ' << p.second << '\n';
    }
    return 0;
}