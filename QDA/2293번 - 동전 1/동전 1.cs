var temp = Console.ReadLine()
    .Split()
    .Select(int.Parse)
    .ToArray();
int n = temp[0], k = temp[1];
var coins = Enumerable.Range(0, n)
    .Select(_ => int.Parse(Console.ReadLine()))
    .ToArray();
int[] dp = new int[k + 1];
dp[0] = 1;

foreach (var coin in coins)
{
    for (int i = coin; i < k + 1; i++)
    {
        dp[i] += dp[i - coin];
    }
}

Console.WriteLine(dp[k]);