auto spfa = [&](int s, const vector <vector <pair <int, ll>>> &e) -> pair <vector <ll>, bool> {
    vector dis (n + 1, INF); dis[s] = 0;
    vector vis (n + 1, 0);
    // vector cnt (n + 1, 0);
    queue <int> q; q.push (s);
    while (q.size ()) {
        auto u = q.front (); q.pop ();
        vis[u] = 0;
        for (auto [v, w] : e[u]) {
            if (dis[v] > dis[u] + w) {
                dis[v] = dis[u] + w;
                if (!vis[v]) vis[v] = 1, q.push (v);
                // cnt[v]++;
            }
            // if (cnt[v] > n) return {vector (0, 0ll), 0};
        }
    }
    return {dis, 1};
};
