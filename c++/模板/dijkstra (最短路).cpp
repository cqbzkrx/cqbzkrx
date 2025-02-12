struct Node {
    int v; ll w;
    Node () : v(0), w(0ll) {}
    Node (int x, ll y) {v = x, w = y;}
};

vector dis(n + 1, 0ll), vis(n + 1, 0);

void dij (int s) {
    fill(all(dis), INF); dis[s] = 0ll;
    fill(all(vis), 0);
    priority_queue <pair <ll, int>, vector <pair <ll, int>>, greater <pair <ll, int>>> pq;
    pq.push({0ll, s});
    while(pq.size()) {
        auto u = pq.top().second; pq.pop();
        if (vis[u]) continue; vis[u] = 1;
        for (auto &[v, w] : e[u]) if (dis[u] + w < dis[v]) {
            dis[v] = dis[u] + w;
            pq.push({dis[v], v});
        }
    }
}
