vector dfn (n + 1, 0), low (n + 1, 0), blo (n + 1, 0);
int cnt2 = 0;

auto dfs = [&](auto &&self, int u, int fa, int &cnt, vector <int> &q) -> void {
    low[u] = dfn[u] = ++cnt;
    q.push_back (u);
    for (auto v : e[u]) if (v != fa) {
        if (!dfn[v]) {
            self (self, v, u, cnt, q);
            cmin (low[u], low[v]);
        }
        else cmin (low[u], dfn[v]);
    }

    if (low[u] == dfn[u]) {
        cnt2++;
        auto v = q.back (); q.pop_back ();
        blo[v] = cnt2;
        while (v != u && q.size ()) {
            v = q.back (); q.pop_back ();
            blo[v] = cnt2;
        }
    }
};

auto calc = [&](int u) -> void {
    int cnt = 0;
    vector q (0, 0);
    dfs (dfs, u, 0, cnt, q);
};

for (int i = 1; i <= n; i++) if (!dfn[i])
    calc (i);

vector ans (cnt2 + 1, vector (0, 0));
for (int i = 1; i <= n; i++) ans[blo[i]].push_back (i);
