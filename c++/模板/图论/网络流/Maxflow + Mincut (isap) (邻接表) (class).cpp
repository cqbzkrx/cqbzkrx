template <typename T>
class maxflow {
public:
    static constexpr ll MAXX = INF;
    vector <vector <tuple <int, T, int>>> e;
    vector <int> dis, gap;
    int n, s, t;

    maxflow () : n (0), s (0), t (0) {}
    maxflow (int _n, int _s, int _t) {
        n = _n;
        e.assign (n + 1, vector (0, tuple (0, T (0), 0)));
        s = _s; t = _t;
    }

    void bfs () {
        dis.assign (n + 1, -1); dis[t] = 0;
        gap.assign (n + 1, 0); gap[0] = 1;
        queue <int> q; q.push (t);
        while (q.size ()) {
            auto u = q.front (); q.pop ();
            for (auto &[v, w, id] : e[u]) if (dis[v] == -1) {
                q.push (v);
                dis[v] = dis[u] + 1;
                gap[dis[v]]++;
            }
        }
    }

    T dfs (int u, T flow) {
        T sum = 0; int minn = n - 1;
        if (u == t) return flow;
        for (auto &[v, w, id] : e[u]) if (w > 0) {
            if (dis[u] == dis[v] + 1) {
                auto res = dfs (v, min (flow - sum, w));
                w -= res;
                get <1> (e[v][id]) += res;
                sum += res;
                if (dis[s] >= n) return sum;
                if (sum == flow) break;
            }
            cmin (minn, dis[v]);
        }
        
        if (sum == 0) {
            gap[dis[u]]--;
            if (gap[dis[u]] == 0) dis[s] = n;
            dis[u] = minn + 1;
            gap[dis[u]]++;
        }
        return sum;
    }

    void insert (int v, int u, T w) {
        int idv = e[v].size (), idu = e[u].size ();
        e[v].emplace_back (u, w, idu);
        e[u].emplace_back (v, 0, idv);
    }

    T flow () {
        bfs ();
        if (dis[s] == -1) return 0;
        T ans = 0;
        while (dis[s] < n) ans += dfs (s, MAXX);
        return ans;
    }

    vector <pair <int, int>> mincut () {
        vector vis (n + 1, 0), c (0, 0); c.reserve (n);
        auto dfs = [&](auto &&self, int u) -> void {
            if (vis[u]) return ;
            vis[u] = 1; c.push_back (u);
            for (auto [v, w, id] : e[u]) if (!vis[v] && w > 0)
                self (self, v);
        };

        vector ans (0, pair (0, 0));
        dfs (dfs, s);
        for (auto u : c) for (auto [v, w, id] : e[u]) if (!vis[v])
            ans.emplace_back (u, v);
        return ans;
    }
};
