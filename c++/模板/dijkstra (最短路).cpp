template <class info>
class dijkstra {
    public:
    vector <vector <info>> e;
    vector <int> dis, vis;

    void dij (int s) {
        fill(all(dis), inf); dis[s] = 0;
        fill(all(vis), 0);
        priority_queue <pair <int, int>, vector <pair <int, int>>, greater <pair <int, int>>> pq;
        pq.push({0, s});
        while(pq.size()) {
            auto u = pq.top().second; pq.pop();
            if (vis[u]) continue; vis[u] = 1;
            for (auto &i : e[u]) if (dis[u] + i.w < dis[i.v]) {
                dis[i.v] = dis[u] + i.w;
                pq.push({dis[i.v], i.v});
            }
        }
    }

    dijkstra () : dis(vector (0, 0)), vis(vector (0, 0)) {}
    dijkstra (int n, const vector <vector <info>> &a) {dis = vector (n + 1, 0), vis = vector (n + 1, 0), e = a;}
};

struct Node {
    int v, w;
    Node () : v(0), w(0) {}
    Node (int x, int y) {v = x, w = y;}
};
