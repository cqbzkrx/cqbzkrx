vector dfn (n + 1, -1), low (n + 1, -1);
vector ans (0, pair (0, 0));
int cnt = 0;
auto dfs = [&](auto &&self, int u, int fa) -> void {
    dfn[u] = low[u] = cnt++;
    for (auto v : e[u]) if (v != fa) {
        if (dfn[v] == -1) {
            self (self, v, u);
            if (low[v] > dfn[u]) ans.push_back ({min (v, u), max (v, u)});
            cmin (low[u], low[v]);
        }
        else cmin (low[u], dfn[v]);
    }
};

dfs (dfs, 1, 0);

for (auto [v, u] : ans) cout << v << ' ' << u << '\n';
