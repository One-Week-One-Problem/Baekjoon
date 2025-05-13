const int VOID = 0, APPLE = 1, BODY = 2;


int N = int.Parse(Console.ReadLine());
int K = int.Parse(Console.ReadLine());

int[][] grid = new int[N][];
for (int i = 0; i < N; i++) grid[i] = new int[N];
for (int i = 0; i < K; i++)
{
    var line = Console.ReadLine().Split();
    int r = int.Parse(line[0]);
    int c = int.Parse(line[1]);
    grid[r - 1][c - 1] = APPLE;
}

int L = int.Parse(Console.ReadLine());

int[] dy = { 0, 1, 0, -1 };
int[] dx = { 1, 0, -1, 0 };
int currentDirection = 0;
int time = 0;
LinkedList<(int y, int x)> snake = new();
snake.AddLast((0, 0));
grid[0][0] = BODY;
for (int i = 0; i < L; i++)
{
    var line = Console.ReadLine().Split();
    int X = int.Parse(line[0]);
    int C = line[1].Equals("D") ? 1 : -1;

    while (time < X)
    {
        time++;

        var (hy, hx) = snake.Last.Value;
        int ny = hy + dy[currentDirection];
        int nx = hx + dx[currentDirection];
        if (!CanMove(ny, nx) || grid[ny][nx] == BODY)
        {
            Console.WriteLine(time);
            return;
        }

        if (grid[ny][nx] != APPLE)
        {
            var (ty, tx) = snake.First.Value;
            snake.RemoveFirst();
            grid[ty][tx] = VOID;
        }

        snake.AddLast((ny, nx));
        grid[ny][nx] = BODY;
    }

    currentDirection = (currentDirection + C + 4) % 4;
}
while (true)
{
    time++;

    var (hy, hx) = snake.Last.Value;
    int ny = hy + dy[currentDirection];
    int nx = hx + dx[currentDirection];
    if (!CanMove(ny, nx) || grid[ny][nx] == BODY)
    {
        Console.WriteLine(time);
        return;
    }

    if (grid[ny][nx] != APPLE)
    {
        var (ty, tx) = snake.First.Value;
        snake.RemoveFirst();
        grid[ty][tx] = VOID;
    }

    snake.AddLast((ny, nx));
    grid[ny][nx] = BODY;
}

bool CanMove(int y, int x)
{
    return 0 <= y && y < N && 0 <= x && x < N;
}