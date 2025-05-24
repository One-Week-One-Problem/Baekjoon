/* ************************************************************************** */
/*                                                                            */
/*                                                      :::    :::    :::     */
/*   Problem Number: 2293                              :+:    :+:      :+:    */
/*                                                    +:+    +:+        +:+   */
/*   By: jsw0510 <boj.kr/u/jsw0510>                  +#+    +#+          +#+  */
/*                                                  +#+      +#+        +#+   */
/*   https://boj.kr/2293                           #+#        #+#      #+#    */
/*   Solved: 2025/05/16 23:34:16 by jsw0510       ###          ###   ##.kr    */
/*                                                                            */
/* ************************************************************************** */
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    int n, k;
    cin >> n >> k;
    vector<int> coins(n);
    for (int i = 0; i < n; i++)
    {
        cin >> coins[i];
    }

    vector<int> dp(k + 1);
    dp[0] = 1;
    for (int coin : coins)
    {
        for (int i = coin; i < k + 1; i++)
        {
            dp[i] += dp[i - coin];
        }
    }

    cout << dp[k];
}