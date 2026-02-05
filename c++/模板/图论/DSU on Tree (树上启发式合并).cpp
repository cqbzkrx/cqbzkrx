// https://www.hackerrank.com/challenges/coloring-tree/problem
// https://vjudge.net/contest/685860#problem/A

void solve () {
    int n, m, rt; cin >> n >> m >> rt;
    vector e (n + 1, vector (0, 0));
    for (int i = 1; i < n; i++) {
        int v, u; cin >> v >> u;
        e[v].push_back (u);
        e[u].push_back (v);
    }

    vector a (n + 1, 0), pool (n, 0);
    for (int i = 1; i <= n; i++) cin >> a[i], pool[i - 1] = a[i];
    sort (all(pool)); pool.erase (unique (all(pool)), pool.end ());
    for (int i = 1; i <= n; i++) a[i] = lower_bound (all(pool), a[i]) - pool.begin ();

    vector son (n + 1, -1);
    auto dfs = [&](auto &&self, int u, int fa) -> int {
        int maxn = 0, siz = 1;
        for (auto v : e[u]) if (v != fa) {
            auto csiz = self (self, v, u);
            siz += csiz;
            if (csiz > maxn) son[u] = v;
        }
        return siz;
    };

    dfs (dfs, rt, 0);

    vector dfn (n + 1, 0), out (n + 1, 0), rnk (n + 1, 0);
    int num = 0;
    auto dfs2 = [&](auto &&self, int u, int fa) -> void {
        rnk[num] = u; dfn[u] = num++;
        if (son[u] != -1) self (self, son[u], u);
        for (auto v : e[u]) if (v != fa && v != son[u])
            self (self, v, u);
        out[u] = num;
    };

    dfs2 (dfs2, rt, 0);

    vector cnt (n + 1, 0);
    int cur = 0;
    auto add = [&](int p, int val) -> void {
        if (!cnt[a[p]]) cur++;
        cnt[a[p]] += val;
        if (!cnt[a[p]]) cur--;
    };

    vector ans (n + 1, 0);
    auto dfs3 = [&](auto &&self, int u, int fa) -> void {
        for (auto v : e[u]) if (v != fa && v != son[u]) {
            self (self, v, u);
            for (int i = dfn[v]; i < out[v]; i++) add (rnk[i], -1);
        }

        if (son[u] != -1) {
            self (self, son[u], u);
            for (int i = out[son[u]]; i < out[u]; i++) add (rnk[i], 1);
        }

        add (u, 1);
        ans[u] = cur;
    };

    dfs3 (dfs3, rt, 0);

    while (m--) {
        int p; cin >> p;
        cout << ans[p] << '\n';
    }
}
