vector dis(n + 1, 0ll), inq (n + 1, 0);

void spfa (int x) {
    fill (all(dis), INF); dis[x] = 0ll;
    queue <int> q; q.push(x);

    while (q.size()) {
        inq[q.front()] = 0;
        auto u = q.front(); q.pop();
        for (auto &[v, w] : e[u]) if (dis[u] + w < dis[v]) {
            dis[v] = dis[u] + w;
            if (inq[v] == 0) inq[v] = 1, q.push(v);
        }
    }
}
