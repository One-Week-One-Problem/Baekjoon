N, M = map(int,input().split())
e = []
l = []
a = N%(2*M)
if a == 0:
  a = 2*M
for i in range(M):
  f,s = map(int,input().split())
  e.append(f)
  e.append(s)
  l.append([f,s])
e.sort()
j = e[a-1]
for k in l: 
  if j in k:
    print(l.index(k)+1)
