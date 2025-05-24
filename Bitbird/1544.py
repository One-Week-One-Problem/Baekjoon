N = int(input())

recycle = []
empty = []
cycle = [input() for i in range(N)]

for i in cycle:
  recycle_prime = [i[j:]+i[:j] for j in range(len(i))]
  recycle_prime.sort()
  recycle.append(recycle_prime)

for i in recycle:
  if i not in empty:
    empty.append(i)

print(len(empty))