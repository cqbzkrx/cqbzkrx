// int
auto dijkstra = [&](int s) -> vector <array <int, 2>> {
    vector dis (n + 1, array <int, 2> ({INF, INF}));
    vector vis (n + 1, array <int, 2> ({0, 0}));
    dis[s][0] = 0;
    priority_queue <array <int, 3>, vector <array <int, 3>>, greater <array <int, 3>>> pq;
    pq.push ({0, s, 0});

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

// long long
struct Node {
    ll w, v, id;
    Node (ll _w = 0, ll _v = 0, ll _id = 0) : w (_w), v (_v), id (_id) {}
    bool operator < (const Node &b) const {return w > b.w;}
};

auto dijkstra = [&](int s) -> vector <array <ll, 2>> {
    vector dis (n + 1, array <ll, 2> ({INF, INF}));
    vector vis (n + 1, array <int, 2> ({0, 0}));
    dis[s][0] = 0;
    priority_queue <Node> pq;
    pq.push (Node (0, s, 0));

    while (pq.size ()) {
        auto [_w, u, id] = pq.top (); pq.pop ();
        if (vis[u][id]) continue; vis[u][id] = 1;

        for (auto [v, w] : e[u]) {
            if (dis[u][id] + w == dis[v][0]) continue;
            else if (dis[u][id] + w < dis[v][0]) {
                dis[v][1] = dis[v][0], dis[v][0] = dis[u][id] + w;
                pq.push (Node (dis[v][0], v, 0)), pq.push (Node (dis[v][1], v, 1));
            }
            else if (dis[u][id] + w < dis[v][1])
                dis[v][1] = dis[u][id] + w, pq.push (Node (dis[v][1], v, 1));
        }
    }

    return dis;
};
