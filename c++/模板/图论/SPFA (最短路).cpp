vector dis (n + 1, INF);
auto spfa = [&](int s) -> bool {
    vector vis (n + 1, 0);
    // vector cnt (n + 1, 0);
    fill (all(dis), INF); dis[s] = 0;
    deque <int> dq; dq.push_back (s);
    while (dq.size()) {
        auto u = dq.front(); dq.pop_front();
        vis[u] = 0;
        for (auto &[v, w] : e[u]) if (dis[u] + w < dis[v]) {
            dis[v] = dis[u] + w;
            if (!vis[v]) {
                vis[v] = 1; dq.push_back (v);
                // cnt[v]++;
            }
            // if (cnt[v] > n) return 0;
        }
    }
    return 1;
};
