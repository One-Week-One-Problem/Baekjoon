#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;

struct q_val {
    int row;
    int col;
    int time;
    bool is_building;
};

int dr[4] = {0, 0, -1, 1};
int dc[4] = {1, -1, 0, 0};

int R, C;
int Tg, Tb, X, B;
char pnuMap[1001][1001];
queue<q_val> q_virus;
queue<q_val> q_building;
int visited[1001][1001] = {};
int virus[1001][1001] = {};
int infection_time[1001][1001] = {};

q_val search() {
    if (q_virus.empty()) {
        q_val ret_val = q_building.front();
        q_building.pop();
        return ret_val;
    }

    if (q_building.empty()) {
        q_val ret_val = q_virus.front();
        q_virus.pop();
        return ret_val;
    }

    // 시간 비교 로직 (기존 코드 유지)
    if (q_virus.front().time < q_building.front().time) {
        q_val ret_val = q_virus.front();
        q_virus.pop();
        return ret_val;
    } else {
        q_val ret_val = q_building.front();
        q_building.pop();
        return ret_val;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    fill_n(&infection_time[0][0], 1001*1001, -1);
    cin >> R >> C >> Tg >> Tb >> X >> B;

    for (int r = 0; r < R; r++) {
        for (int c = 0; c < C; c++) {
            cin >> pnuMap[r][c];
            if (pnuMap[r][c] == '*') {
                q_virus.push({r, c, 0, false});
                visited[r][c] = 1;
            }
        }
    }

    while (!q_virus.empty() || !q_building.empty()) {
        q_val cur = search();
        if (cur.time > Tg) break;

        virus[cur.row][cur.col] = 1;
        if (cur.is_building) visited[cur.row][cur.col] = 0;

        for (int i = 0; i < 4; i++) {
            int nr = cur.row + dr[i], nc = cur.col + dc[i];
            if (nr < 0 || nr >= R || nc < 0 || nc >= C || visited[nr][nc]) continue;

            visited[nr][nc] = 1;
            if (pnuMap[nr][nc] == '#') {
                q_building.push({nr, nc, cur.time + Tb, true});
                infection_time[nr][nc] = cur.time;
            } else if (pnuMap[nr][nc] == '.') {
                q_virus.push({nr, nc, cur.time + 1, false});
            }
        }
    }

    // 핵심 수정 부분: 건물 우선 판단 로직
    vector<pair<int, int>> ans;
    for (int r = 0; r < R; r++) {
        for (int c = 0; c < C; c++) {
            bool safe = false;
            if (pnuMap[r][c] == '#') {
                safe = (infection_time[r][c] == -1) || (Tg - infection_time[r][c] < Tb);
            } else {
                safe = (virus[r][c] == 0);
            }
            if (safe) ans.emplace_back(r+1, c+1);
        }
    }

    sort(ans.begin(), ans.end());
    if (ans.empty()) cout << -1;
    else for (auto &p : ans) cout << p.first << ' ' << p.second << '\n';
}
