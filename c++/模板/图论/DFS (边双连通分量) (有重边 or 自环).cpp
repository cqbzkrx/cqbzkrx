vector e (n + 1, vector (0, pair (0, 0)));
for (int i = 1; i <= m; i++) {
    int v, u; cin >> v >> u;
    e[v].push_back ({u, (i << 1)});
    e[u].push_back ({v, ((i << 1) | 1)});
}

vector dfn (n + 1, 0), low (n + 1, 0);
vector ans (0, vector (0, 0));

auto dfs = [&](auto &&self, int u, int fa, int idx, int &cnt, vector <int> &q) -> void {
    low[u] = dfn[u] = ++cnt;
    q.push_back (u);
    for (auto [v, id] : e[u]) if (id != (idx ^ 1)) {
        if (!dfn[v]) {
            self (self, v, u, id, cnt, q);
            cmin (low[u], low[v]);
        }
        else cmin (low[u], dfn[v]);
    }

    if (dfn[u] == low[u]) {
        vector vec (0, 0);
        vec.push_back (u);
        while (q.size () && q.back () != u) {
            vec.push_back (q.back ());
            q.pop_back ();
        }
        ans.push_back (vec);
    }
};

auto calc = [&](int u) -> void {
    int cnt = 0;
    vector q (0, 0);
    dfs (dfs, u, 0, 0, cnt, q);
};

for (int i = 1; i <= n; i++) if (!dfn[i])
    calc (i);

cout << ans.size () << '\n';
for (auto &vec : ans) {
    cout << vec.size () << ' ';
    for (auto v : vec) cout << v << ' ';
    cout << '\n';
}
