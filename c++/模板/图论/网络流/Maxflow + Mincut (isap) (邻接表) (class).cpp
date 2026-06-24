template <typename T>
class maxflow {
public:
    static constexpr ll INVALID = INF;
    vector <vector <tuple <int, T, int>>> e;
    vector <int> dis, gap;

    using Iter = typename vector <tuple <int, T, int>> :: iterator;
    vector <Iter> cur;
    int n, s, t;

    maxflow () : n (0), s (0), t (0) {}
    maxflow (int n, int s, int t) {
        this -> n = n;
        e.assign (n + 1, vector (0, tuple (0, T (0), 0)));
        dis.assign (n + 2, n);
        gap.assign (n + 2, 0);
        cur.resize (n + 1);
        this -> s = s; this -> t = t;
    }

    void bfs () {
        fill (all(dis), n); dis[t] = 0;
        fill (all(gap), 0); gap[0] = 1;
        for (int i = 0; i <= n; i++) cur[i] = e[i].begin ();
        queue <int> q; q.push (t);
        while (q.size ()) {
            auto u = q.front (); q.pop ();
            for (auto &[v, w, id] : e[u]) if (dis[v] == n && get <1> (e[v][id]) > 0) {
                dis[v] = dis[u] + 1;
                gap[dis[v]]++;
                q.push (v);
            }
        }
    }

    T dfs (int u, T flow) {
        if (u == t) return flow;
        T sum = 0;
        for (auto &it = cur[u]; it != e[u].end (); it++) {
            auto &[v, w, id] = *it;
            if (w > 0 && dis[u] == dis[v] + 1) {
                auto res = dfs (v, min (flow - sum, w));
                w -= res; get <1> (e[v][id]) += res;
                sum += res;
                if (dis[s] >= n) return sum;
                if (sum == flow) return sum;
            }
        }

        gap[dis[u]]--;
        if (gap[dis[u]] == 0) {dis[s] = n; return sum;}

        int minn = n;
        for (auto &[v, w, id] : e[u]) if (w > 0)
            cmin (minn, dis[v]);

        dis[u] = minn + 1;
        gap[dis[u]]++;
        cur[u] = e[u].begin ();

        return sum;
    }

    void insert (int v, int u, T w) {
        int idv = e[v].size (), idu = e[u].size ();
        e[v].emplace_back (u, w, idu);
        e[u].emplace_back (v, 0, idv);
    }

    T flow () {
        bfs ();
        if (dis[s] == n) return 0;
        T ans = 0;
        while (dis[s] < n) ans += dfs (s, INVALID);
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
