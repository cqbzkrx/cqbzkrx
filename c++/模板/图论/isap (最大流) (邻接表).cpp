namespace isap {
    vector <vector <ll>> e;
    vector <vector <int>> e2;
    vector <int> dis, gap;
    int n, s, t;

    void bfs () {
        dis.assign (n + 1, -1); dis[t] = 0;
        gap.assign (n + 1, 0); gap[0] = 1;
        queue <int> q; q.push (t);
        while (q.size ()) {
            auto u = q.front (); q.pop ();
            for (int v = 1; v <= n; v++) if (dis[v] == -1) {
                q.push (v);
                dis[v] = dis[u] + 1;
                gap[dis[v]]++;
            }
        }
    }

    ll dfs (int u, ll flow) {
        ll sum = 0; int minn = n - 1;
        if (u == t) return flow;
        for (auto v : e2[u]) if (e[u][v] > 0) {
            if (dis[u] == dis[v] + 1) {
                auto res = dfs (v, min (flow - sum, e[u][v]));
                e[u][v] -= res;
                e[v][u] += res;
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

    ll isap () {
        bfs ();
        ll ans = 0;
        while (dis[s] < n) ans += dfs (s, INF);
        return ans;
    }
}

void solve () {
    int m; cin >> isap :: n >> m;
    isap :: s = 1;
    isap :: t = isap :: n;
    isap :: e.assign (isap :: n + 1, vector (isap :: n + 1, 0ll));
    isap :: e2.assign (isap :: n + 1, vector (0, 0));
    for (int i = 1; i <= m; i++) {
        int v, u; ll w; cin >> v >> u >> w;
        isap :: e2[v].push_back (u);
        isap :: e2[u].push_back (v);
        isap :: e[v][u] += w;
    }

    cout << isap :: isap () << '\n';
}
