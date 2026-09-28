
n = int(input())
line_data = input().split()
arr = []
for i in range(n):
    arr.append(int(line_data[i]))

if n == 1:
    print(arr[0], "\n1")
    exit()

if n == 2:
    print('-1')
    exit()

sum_muh = [0] * n
ind = [0] * n

sum_muh[0] = arr[0]
sum_muh[1] = -1
sum_muh[2] = arr[0] + arr[2]
ind[2] = 0

for i in range(3, n):
    if sum_muh[i-3] > sum_muh[i-2]:
        sum_muh[i] = sum_muh[i-3]+arr[i]
        ind[i] = i-3
    else :
        sum_muh[i] = sum_muh[i - 2] + arr[i]
        ind[i] = i - 2

print(sum_muh[n-1])

way = []
index = n-1
while index != 0:
    way.append(index+1)
    index = ind[index]

way.append(1)

way.reverse()
print(*way)
