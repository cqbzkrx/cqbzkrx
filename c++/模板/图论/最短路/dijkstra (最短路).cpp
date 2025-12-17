auto dij = [&](int s, const vector <vector <pair <int, ll>>> &e) -> vector <ll> {
    vector dis (n + 1, INF); dis[s] = 0;
    vector vis (n + 1, 0);
    using T = pair <ll, int>;
    priority_queue <T, vector <T>, greater <T>> q; q.emplace (0ll, s);
    while (q.size ()) {
        auto [_w, u] = q.top (); q.pop ();
        if (vis[u]) continue; vis[u] = 1;
        for (auto [v, w] : e[u]) if (dis[v] > dis[u] + w)
            dis[v] = dis[u] + w, q.emplace (dis[v], v);
    }
    return dis;
};
