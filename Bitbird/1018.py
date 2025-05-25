#입력
N, M = map(int,input().split())
chess = []
result = []
for _ in range(N):
    chess.append(input())

#예시
case1 = ['BWBWBWBW', 'WBWBWBWB', 'BWBWBWBW', 'WBWBWBWB', 'BWBWBWBW', 'WBWBWBWB', 'BWBWBWBW', 'WBWBWBWB']
case2 = ['WBWBWBWB', 'BWBWBWBW', 'WBWBWBWB', 'BWBWBWBW', 'WBWBWBWB', 'BWBWBWBW', 'WBWBWBWB', 'BWBWBWBW']

#시작점 초기화
for i in range(N-7):
    for j in range(M-7):
        cnt1 = 0
        cnt2 = 0
        #체스칸 나누기
        for x in range(8):
            for y in range(8):
                if chess[i+x][j+y] != case1[x][y]:
                    cnt1 += 1
                if chess[i+x][j+y] != case2[x][y]:
                    cnt2 += 1
        result.append(cnt1)
        result.append(cnt2)            

result.sort()
print(result[0])