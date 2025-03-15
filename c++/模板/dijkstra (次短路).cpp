auto dijkstra = [&](int s) -> vector <array <ll, 2>> {
    vector dis (n + 1, array <ll, 2> ({INF, INF}));
    vector vis (n + 1, array <ll, 2> ({0, 0}));
    dis[s][0] = 0ll;
    priority_queue <array <ll, 3>, vector <array <ll, 3>>, greater <array <ll, 3>>> pq;
    pq.push ({0ll, s, 0});

    while (pq.size ()) {
        auto [_w, u, id] = pq.top (); pq.pop ();
        if (vis[u][id]) continue; vis[u][id] = 1;

        for (auto [v, w] : e[u]) {
            if (dis[u][id] + w == dis[v][0]) continue;
            else if (dis[u][id] + w < dis[v][0]) {
                dis[v][1] = dis[v][0], dis[v][0] = dis[u][id] + w;
                pq.push ({dis[v][0], v, 0}), pq.push ({dis[v][1], v, 1});
            }
            else if (dis[u][id] + w < dis[v][1])
                dis[v][1] = dis[u][id] + w, pq.push ({dis[v][1], v, 1});
        }
    }

    return dis;
}; 
