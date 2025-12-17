vector dfn (n + 1, 0), low (n + 1, 0), q (0, 0);
vector ans (0, vector (0, 0));

auto dfs = [&](auto &&self, int u, int fa, int &cnt) -> void {
    dfn[u] = low[u] = ++cnt;
    q.push_back (u);
    if (!e[u].size ()) ans.push_back ({u});

    for (auto v : e[u]) if (v != fa) {
        if (!dfn[v]) {
            self (self, v, u, cnt);
            cmin (low[u], low[v]);
            if (low[v] >= dfn[u]) {
                vector vec (0, 0);
                
                int x = q.back (); q.pop_back ();
                vec.push_back (x);
                while (q.size () && x != v) {
                    x = q.back (); q.pop_back ();
                    vec.push_back (x);
                }
                vec.push_back (u);

                ans.push_back (vec);
            }
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
