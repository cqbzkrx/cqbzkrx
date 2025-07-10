vector dfn (n + 1, -1), low (n + 1, -1);
vector ans (0, pair (0, 0));

auto dfs = [&](auto &&self, int u, int fa, int &cnt) -> void {
    dfn[u] = low[u] = ++cnt;
    for (auto v : e[u]) if (v != fa) {
        if (!dfn[v]) {
            self (self, v, u);
            if (low[v] > dfn[u]) ans.push_back ({u, v});
            cmin (low[u], low[v]);
        }
        else cmin (low[u], dfn[v]);
    }
};

auto calc = [&](int u) -> void {
    int cnt = 0;
    dfs (dfs, u, 0, cnt);
};

for (int i = 1; i <= n; i++) if (!dfn[i])
    calc (i);
