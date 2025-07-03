auto bfs = [&](int st, int en) -> int {
    deque <pair <int, int>> q;
    vector <int> vis (n, 0), dis (n, 0);
    vis[st] = 1, vis[en] = 2;
    q.push_back ({st, 1});
    q.push_back ({en, 2});
    dis[st] = dis[en] = 1;

    while (q.size ()) {
        auto u = q.front ().x, f = q.front ().y; q.pop_front ();
        for (auto v : e[u]) {
            if (vis[v] == f) continue;
            else if (vis[v] == 3 - f) return dis[v] + dis[u];
            else vis[v] = f, dis[v] = dis[u] + 1, q.push_back ({v, f});
        }
    }

    return -1;  
};
