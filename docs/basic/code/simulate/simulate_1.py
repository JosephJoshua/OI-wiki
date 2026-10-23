u, d, n = map(int, input().split())
time = dist = 0
while True:  # enumerate with an infinite loop
    dist += u
    time += 1
    if dist >= n:  # leave the loop once the condition holds
        break
    dist -= d
print(time)  # print the result
