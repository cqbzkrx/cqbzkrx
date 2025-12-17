class LCA {
public:
    vector <vector <int>> f, e;
    vector <int> dep;
    int n, lim;

    LCA (vector <vector <int>> &a, int n, int rt) {init (a, n, rt);}
    void init (vector <vector <int>> &a, int n, int rt) {
        e = move (a);
        this -> n = n;
        lim = __lg (n) + 1;

        f.assign (lim + 1, vector (n + 1, 0));
        dep.assign (n + 1, 0);

        auto dfs = [&](auto &&self, int u, int fa) -> void {
            dep[u] = dep[fa] + 1;
            f[0][u] = fa;
            for (auto v : e[u]) if (v != fa)
                self (self, v, u);
        };

        dfs (dfs, rt, 0);
        for (int i = 1; i <= lim; i++) for (int j = 1; j <= n; j++)
            f[i][j] = f[i - 1][f[i - 1][j]];
    }

    int lca (int v, int u) {
        if (dep[v] > dep[u]) swap (v, u);
        for (int i = lim; i >= 0; i--) if (dep[u] - (1 << i) >= dep[v])
            u = f[i][u];

        if (v == u) return u;
        for (int i = lim; i >= 0; i--) {
            if (f[i][u] == 0) continue;
            if (f[i][u] != f[i][v]) v = f[i][v], u = f[i][u];
        }

        return f[0][u];
    }

    int len (int v, int u) {
        return dep[v] + dep[u] - 2 * dep[lca (v, u)];
    }
};
