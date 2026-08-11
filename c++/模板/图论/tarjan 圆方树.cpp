vector e2 (n * 2 + 1, vector (0, 0));
vector dfn (n + 1, 0), low (n + 1, 0), s (0, 0); s.reserve (n);
int cnt = n, num = 0;
auto dfs = [&](auto &&self, int u) -> void {
    dfn[u] = low[u] = ++num;
    s.push_back (u);
    for (auto v : e[u]) {
        if (!dfn[v]) {
            self (self, v);
            cmin (low[u], low[v]);
            if (low[v] == dfn[u]) {
                cnt++;
                while (s.size () && s.back () != v) {
                    auto x = s.back (); s.pop_back ();
                    e2[cnt].push_back (x);
                    e2[x].push_back (cnt);
                }
                e2[cnt].push_back (v);
                e2[v].push_back (cnt);
                s.pop_back ();

                e2[cnt].push_back (u);
                e2[u].push_back (cnt);
            }
        }
        else cmin (low[u], dfn[v]);
    }
};

for (int i = 1; i <= n; i++) if (!dfn[i]) {
    dfs (dfs, i);
    s.clear ();
}
