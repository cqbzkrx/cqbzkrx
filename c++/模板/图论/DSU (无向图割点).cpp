vector dfn (n + 1, 0), low (n + 1, 0), vis (n + 1, 0);

auto dfs = [&](auto &&self, int u, int fa, int &cnt, int &rson) -> void {
    dfn[u] = low[u] = ++cnt;
    for (auto v : e[u]) if (v != fa) {
        if (!dfn[v]) {
            self (self, v, u, cnt, rson);
            if (low[v] >= dfn[u]) {
                if (fa == 0) rson++;
                else vis[u] = 1;
            }
            cmin (low[u], low[v]);
        }
        else cmin (low[u], dfn[v]);
    }
};

auto calc = [&](int u) -> void {
    int cnt = 0, rson = 0;
    dfs (dfs, u, 0, cnt, rson);
    if (rson > 1) vis[u] = 1;
};

for (int i = 1; i <= n; i++) if (!dfn[i])
    calc (i);

vector ans (0, 0);
for (int i = 1; i <= n; i++) if (vis[i])
    ans.push_back (i);
