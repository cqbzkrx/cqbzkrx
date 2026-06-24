template <typename T>
class maxflow {
public:
    static constexpr ll INVALID = INF;
    vector <vector <tuple <int, T, int>>> e;
    vector <int> dis;

    using Iter = typename vector <tuple <int, T, int>> :: iterator;
    vector <Iter> cur;
    int n, s, t;

    maxflow () : n (0), s (0), t (0) {}
    maxflow (int n, int s, int t) {
        this -> n = n;
        e.assign (n + 1, vector (0, tuple (0, T (0), 0)));
        dis.assign (n + 1, 0);
        cur.resize (n + 1);
        this -> s = s; this -> t = t;
    }

    void insert (int v, int u, T w) {
        int idv = e[v].size (), idu = e[u].size ();
        e[v].emplace_back (u, w, idu);
        e[u].emplace_back (v, 0, idv);
    }

    bool bfs () {
        fill (all(dis), 0);
        for (int i = 0; i <= n; i++) cur[i] = e[i].begin ();
        dis[s] = 1;
        queue <int> q; q.push (s);
        while (q.size ()) {
            int u = q.front (); q.pop ();
            for (auto &[v, w, id] : e[u]) if (!dis[v] && w) {
                dis[v] = dis[u] + 1;
                q.push (v);
            }
        }
        return dis[t] != 0;
    }

    T dfs (int u, T flow) {
        if (u == t) return flow;
        T ans = 0;
        for (auto &it = cur[u]; it != e[u].end (); it++) {
            auto &[v, w, id] = *it;
            if (dis[v] == dis[u] + 1 && w) {
                T res = dfs (v, min (flow, w));
                ans += res;
                w -= res; get <1> (e[v][id]) += res;
                flow -= res;
                if (!flow) break;
            }
        }
        if (!ans) dis[u] = -1;
        return ans;
    }

    T flow () {
        T ans = 0;
        while (bfs ()) ans += dfs (s, INVALID);
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
