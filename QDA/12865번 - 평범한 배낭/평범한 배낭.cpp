/* ************************************************************************** */
/*                                                                            */
/*                                                      :::    :::    :::     */
/*   Problem Number: 12865                             :+:    :+:      :+:    */
/*                                                    +:+    +:+        +:+   */
/*   By: jsw0510 <boj.kr/u/jsw0510>                  +#+    +#+          +#+  */
/*                                                  +#+      +#+        +#+   */
/*   https://boj.kr/12865                          #+#        #+#      #+#    */
/*   Solved: 2025/05/19 19:28:22 by jsw0510       ###          ###   ##.kr    */
/*                                                                            */
/* ************************************************************************** */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int dp[100001] = { 0, };
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N, K;
    cin >> N >> K;

    for (int i = 0; i < N; ++i) {
        int weight, value;
        cin >> weight >> value;
        for (int j = K; j >= weight; --j) {
            dp[j] = max(dp[j], dp[j - weight] + value);
        }
    }
    cout << dp[K] << endl;
    return 0;
}