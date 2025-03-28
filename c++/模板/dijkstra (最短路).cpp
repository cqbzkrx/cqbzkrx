auto dijkstra = [&](int s) -> vector <ll> {
    vector dis (n + 1, INF); dis[s] = 0;
    vector vis (n + 1, 0);
    priority_queue <pair <ll, int>, vector <pair <ll, int>>, greater <pair <ll, int>>> pq;
    pq.push ({0ll, s});

    while (pq.size ()) {
        auto u = pq.top().y; pq.pop();
        if (vis[u]) continue; vis[u] = 1;
        
        for (auto &[v, w] : e[u]) if (dis[u] + w < dis[v])
            dis[v] = dis[u] + w, pq.push ({dis[v], v});
    }

    return dis;
};
