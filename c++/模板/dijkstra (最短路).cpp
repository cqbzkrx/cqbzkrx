vector dis (n + 1, INF);
auto dijkstra = [&](int s) -> void {
    vector vis (n + 1, 0);
    fill (all(dis), INF); dis[s] = 0;

    priority_queue <pair <ll, int>, vector <pair <ll, int>>, greater <pair <ll, int>>> pq;
    pq.push ({0ll, s});
    dis[s] = 0;

    while (pq.size ()) {
        auto u = pq.top().second; pq.pop();
        if (vis[u]) continue; vis[u] = 1;

        for (auto &[v, w] : e[u]) if (dis[u] + w < dis[v]) {
            dis[v] = dis[u] + w;
            pq.push ({dis[v], v});
        }
    }
};
