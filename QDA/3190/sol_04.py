import sys
input = sys.stdin.readline


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
dir_trans_list.append((float("inf"), "L"))

class Point:
    def __init__(self, x=0, y=0, next=None):
        self.x = x
        self.y = y
        self.next: Point = next

def can_move(y, x):
    return 0 <= y < N and 0 <= x < N


dy = [0, 1, 0, -1]
dx = [1, 0, -1, 0]
head = Point(0, 0)
tail = head
current_direction = 0
grid[0][0] = BODY


elapsed_time = 0
for x, c in dir_trans_list:
    while elapsed_time < x:
        elapsed_time += 1
        ny = head.y + dy[current_direction]
        nx = head.x + dx[current_direction]

        if not can_move(ny, nx) or grid[ny][nx] == BODY:
            print(elapsed_time)
            exit()

        head.next = Point(x=nx, y=ny)
        head = head.next

        if grid[ny][nx] != APPLE:
            ty, tx = tail.y, tail.x
            tail = tail.next
            grid[ty][tx] = VOID

        grid[ny][nx] = BODY

    current_direction += c
    current_direction %= 4
