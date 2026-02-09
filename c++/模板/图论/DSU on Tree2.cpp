// https://codeforces.com/contest/741/problem/D
// https://codeforces.com/contest/741/submission/362155326

void solve () {
    int n; cin >> n;
    vector e (n + 1, vector (0, 0));
    vector num (n + 1, 0);
    for (int i = 2; i <= n; i++) {
        int u; char c; cin >> u >> c;
        e[u].push_back (i);
        e[i].push_back (u);
        num[i] = (1 << (c - 'a'));
    }

    vector dep (n + 1, 0), son (n + 1, -1);
    auto dfs = [&](auto &&self, int u, int fa) -> int {
        num[u] ^= num[fa]; dep[u] = dep[fa] + 1;
        int maxn = 0, siz = 1;
        for (auto v : e[u]) if (v != fa) {
            auto csiz = self (self, v, u);
            siz += csiz;
            if (csiz > maxn) maxn = csiz, son[u] = v;
        }
        return siz;
    };

    dfs (dfs, 1, 0);

    vector dfn (n + 1, 0), out (n + 1, 0), rnk (n + 1, 0);
    int num2 = 0;
    auto dfs2 = [&](auto &&self, int u, int fa) -> void {
        rnk[num2] = u; dfn[u] = num2++;
        if (son[u] != -1) self (self, son[u], u);
        for (auto v : e[u]) if (v != fa && v != son[u])
            self (self, v, u);
        out[u] = num2;
    };

    dfs2 (dfs2, 1, 0);

    vector maxdep (1 << M, -inf), ans (n + 1, 0);
    auto add = [&](int p, int u) -> void {
        cmax (ans[u], maxdep[num[p]] + dep[p] - dep[u] * 2);
        for (int i = 0; i < M; i++) cmax (ans[u], maxdep[num[p] ^ (1 << i)] + dep[p] - dep[u] * 2);
    };

    auto add2 = [&](int p) -> void {
        cmax (maxdep[num[p]], dep[p]);
    };

    auto del = [&](int p) -> void {
        maxdep[num[p]] = -inf;
    };

    auto dfs3 = [&](auto &&self, int u, int fa) -> void {
        for (auto v : e[u]) if (v != fa && v != son[u]) {
            self (self, v, u);
            cmax (ans[u], ans[v]);
            for (int i = dfn[v]; i < out[v]; i++) del (rnk[i]);
        }

        if (son[u] != -1) {
            self (self, son[u], u);
            cmax (ans[u], ans[son[u]]);

            for (auto v : e[u]) if (v != fa && v != son[u]) {
                for (int i = dfn[v]; i < out[v]; i++) add (rnk[i], u);
                for (int i = dfn[v]; i < out[v]; i++) add2 (rnk[i]);
            }
        }

        add (u, u);
        add2 (u);
    };

    dfs3 (dfs3, 1, 0);

    for (int i = 1; i <= n; i++) cout << ans[i] << ' ';
    cout << '\n';
}
