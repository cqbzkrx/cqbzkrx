void solve () {
    int n, m; cin >> n >> m;
    vector e (n + 1, vector (0, 0));
    for (int i = 0; i < m; i++) {
        int v, u; cin >> v >> u;
        e[v].emplace_back (u);
    }

    vector ans (0, 0);
    auto dfs = [&](auto &&self, int u) -> void {
        while (e[u].size ()) {
            auto v = e[u].back (); e[u].pop_back ();
            self (self, v);
        }
      
        ans.push_back (u);
    };

    dfs (dfs, 1);

    for (auto v : ans) cout << v << ' ';
    cout << '\n';
}
