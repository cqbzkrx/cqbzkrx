void solve () {
    int n, m; cin >> n >> m;
    vector e (n + 1, vector (0, pair (0, 0)));
    for (int i = 0; i < m; i++) {
        int v, u; cin >> v >> u;
        e[v].emplace_back (u, i);
        e[u].emplace_back (v, i);
    }

    for (int i = 1; i <= n; i++) if (e[i].size () % 2) {
        cout << "IMPOSSIBLE\n";
        return ;
    }

    vector ans (0, 0), vis (m, 0);
    auto dfs = [&](auto &&self, int u) -> void {
        while (e[u].size ()) {
            auto [v, id] = e[u].back (); e[u].pop_back ();
            if (vis[id]) continue; vis[id] = 1;
            self (self, v);
        }

        ans.push_back (u);
    };

    dfs (dfs, 1);

    for (int i = 0; i < m; i++) if (!vis[i]) {
        cout << "IMPOSSIBLE\n";
        return ;
    }

    for (auto v : ans) cout << v << ' ';
    cout << '\n';
}
