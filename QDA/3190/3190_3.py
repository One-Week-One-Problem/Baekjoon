import sys
input = sys.stdin.readline

from collections import deque

VOID = 0
APPLE = 1
BODY = 2


N = int(input())
K = int(input())
grid = [[VOID]*N for _ in range(N)]
for _ in range(K):
    r, c = map(int, input().split())
    grid[r-1][c-1] = APPLE
L = int(input())
dir_trans_list = []
for _ in range(L):
    X, C = input().split()
    X = int(X)
    C = -1 if C == 'L' else 1
    dir_trans_list.append((X, C))

dy = [0, 1, 0, -1]
dx = [1, 0, -1, 0]
snake = deque()
snake.append((0, 0))
current_direction = 0
grid[0][0] = BODY

def can_move(y, x):
    return 0 <= y < N and 0 <= x < N

elapsed_time = 0
for x, c in dir_trans_list:
    while elapsed_time < x:
        elapsed_time += 1
        hy, hx = snake[-1]
        ny = hy + dy[current_direction]
        nx = hx + dx[current_direction]

        if not can_move(ny, nx) or grid[ny][nx] == BODY:
            print(elapsed_time)
            exit()

        snake.append((ny, nx))

        if grid[ny][nx] != APPLE:
            ty, tx = snake[0]
            snake.popleft()
            grid[ty][tx] = VOID

        grid[ny][nx] = BODY

    current_direction += c
    current_direction %= 4
while True:
    elapsed_time += 1
    hy, hx = snake[-1]
    ny = hy + dy[current_direction]
    nx = hx + dx[current_direction]

    if not can_move(ny, nx) or grid[ny][nx] == BODY:
        print(elapsed_time)
        exit()

    snake.append((ny, nx))

    if grid[ny][nx] != APPLE:
        ty, tx = snake[0]
        snake.popleft()
        grid[ty][tx] = VOID

    grid[ny][nx] = BODY