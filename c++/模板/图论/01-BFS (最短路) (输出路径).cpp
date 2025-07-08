auto bfs = [&](int s) -> pair <vector <int>, vector <int>> {
    vector dis (n + 1, inf), vis (n + 1, 0);
    vector fa (n + 1, 0);
    dis[s] = 0;
    deque <int> q = {s};

    while (q.size ()) {
        auto u = q.front(); q.pop_front();
        if (vis[u] == 1) continue; vis[u] = 1;

        for (auto &[v, w] : e[u]) if (!vis[v]) {
            if (w == 0) q.push_front (v);
            else q.push_back (v);
            dis[v] = dis[u] + w;
            fa[v] = u;
        }
    }

    return {dis, fa};
};
