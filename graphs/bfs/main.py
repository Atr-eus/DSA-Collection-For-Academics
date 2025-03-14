from collections import deque


def bfs(adj_ls, n, src):
    q = deque([src])
    visited = set([src])

    dists = [-1] * (n + 1)
    dists[src] = 0
    parents = [-1] * (n + 1)

    while q:
        v = q.popleft()
        for u in adj_ls[v]:
            if u not in visited:
                visited.add(u)
                q.append(u)

                dists[u] = dists[v] + 1
                parents[u] = v

    return parents, visited


def shortest_path(u, v):
    if u == v:
        print(f"{u}")
        return

    adj_ls = {
        1: [2, 5],
        2: [1, 3, 5],
        3: [2, 4],
        4: [3, 5, 6],
        5: [1, 2, 4],
        6: [4],
    }
    parents, visited = bfs(adj_ls, 6, u)
    if v not in visited:
        print("No path found.")
        return

    path = []
    vp = v
    while parents[v] != -1:
        path.append(parents[v])
        v = parents[v]
    path.reverse()

    print(*path, sep=" -> ", end=f" -> {vp}\n")


shortest_path(6, 6)
