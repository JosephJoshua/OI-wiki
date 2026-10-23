from heapq import heappush, heapreplace

a = [tuple(map(int, input().split())) for _ in range(int(input()))]
a.sort(key=lambda job: job[0])  # sort by deadline, ascending

ans = 0  # total profit
q = []  # min-heap keeps the smallest value
for d, p in a:
    if d <= len(q):  # past the deadline
        if q[0] < p:  # undo an earlier choice
            ans += p - heapreplace(q, p)
    else:  # just add it to the queue
        ans += p
        heappush(q, p)
print(ans)
