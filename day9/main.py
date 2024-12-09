from copy import deepcopy

s = input()
ans1, ans2 = 0, 0
n = len(s)
empty = False
arr = []
pid = 0
for i in range(n):
    if empty:
        arr += ['.'] * int(s[i])
    else:
        arr += [str(pid)] * int(s[i])
        pid += 1
    empty = not empty


arr2 = deepcopy(arr)
n = len(arr)
j = 0
for i in range(n - 1, -1, -1):
    if arr[i] != '.':
        while j < i and arr[j] != '.':
            j += 1
        if j < i:
            arr[i], arr[j] = arr[j], arr[i]
i = n - 1
while i >= 0:
    ch = arr2[i]
    if arr2 != '.':
        j = i
        while j >= 0 and arr2[j] == arr2[i]:
            j -= 1
        cnt = i - j
        pos = -1
        for k in range(i):
            t = k
            while t < n and arr2[t] == '.':
                t += 1
            if t - k >= cnt:
                pos = k
                break

        if pos >= 0:
            for k in range(j + 1, i + 1):
                arr2[k] = '.'
            for k in range(pos, pos + cnt):
                arr2[k] = ch
        else:
            i = j + 1
    i -= 1

for i in range(n):
    if arr[i] != '.':
        ans1 += int(arr[i]) * i
    if arr2[i] != '.':
        ans2 += int(arr2[i]) * i

print("PART 1:", ans1)
print("PART 2:", ans2)