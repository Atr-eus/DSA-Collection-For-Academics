def heapify(a, n, i):
    l = i * 2 + 1
    r = i * 2 + 2
    lg = i

    if l < n and a[l] > a[lg]:
        lg = l
    if r < n and a[r] > a[lg]:
        lg = r
    if lg != i:
        a[i], a[lg] = a[lg], a[i]
        heapify(a, n, lg)


def heap_sort(a, n):
    for i in range(n // 2 - 1, -1, -1):
        heapify(a, n, i)
    for i in range(n - 1, 0, -1):
        (
            a[0],
            a[i],
        ) = (
            a[i],
            a[0],
        )
        heapify(a, i, 0)


n = int(input())
a = [int(input()) for _ in range(n)]
heap_sort(a, n)
print(*a, sep="\n")
