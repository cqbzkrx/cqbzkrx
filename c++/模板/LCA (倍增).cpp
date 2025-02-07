class LCA {
    void dfs (int v, int fa) {
        dep[v] = dep[fa] + 1;
        f[0][v] = fa;
        for (auto &[u, w] : e[v]) if (u != fa)
            dfs (u, v);
    }

    public:

    static constexpr int N = 1e4 + 5;
    int n, lim;
    vector <vector <int>> f;
    vector <vector <pair <int, ll>>> e;
    vector <int> dep;
    vector <ll> s;
    
    LCA () : n(0), lim(0), f(vector (__lg(N) + 1, vector (N, 0))),
            e(vector (N, vector (0, pair (0, 0ll)))), dep(N, 0) {}
    LCA (int sz, int rt, const vector <vector <pair <int, ll>>> &a) {init (sz, rt, a);}
    
    int lca (int v, int u) {
        if (dep[v] > dep[u]) swap (v, u);

        for (int i = lim; i >= 0; i--) if (dep[u] - (1 << i) >= dep[v])
            u = f[i][u];
        
        if (v == u) return v;
        for (int i = lim; i >= 0; i--) {
            if (f[i][u] == 0) continue;
            if (f[i][v] != f[i][u]) v = f[i][v], u = f[i][u];
        }
        
        return f[0][u];
    }

    void init (int sz, int rt, const vector <vector <pair <int, ll>>> &a) {
        e = a;
        f = vector (__lg(N) + 1, vector (N, 0));
        dep = vector (N, 0);
        n = sz, lim = __lg(sz);

        dep[rt] = 1; dfs (rt, 0);
        for (int i = 1; i <= lim; i++) for (int j = 1; j <= n; j++)
            f[i][j] = f[i - 1][f[i - 1][j]];
    }
};
