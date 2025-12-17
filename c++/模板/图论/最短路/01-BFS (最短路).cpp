auto bfs = [&](int s) -> vector <int> {
    vector dis (n + 1, inf), vis (n + 1, 0);
    dis[s] = 0;
    deque <int> q = {s};

    while (q.size ()) {
        auto u = q.front(); q.pop_front();
        for (auto &[v, w] : e[u]) if (!vis[v]) {
            vis[v] = 1;
            if (w == 0) q.push_front (v);
            else q.push_back (v);
            dis[v] = dis[u] + w;
        }
    } 

    return dis;
};
