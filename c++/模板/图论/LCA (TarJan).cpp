class LCA_tarjan {
public:
    vector <vector <int>> e;
    vector <vector <pair <int, int>>> eq;
    vector <int> vis, ans;
    int n, q;
    DSU dsu;
    
    LCA_tarjan () : n(0), q(0) {}
    LCA_tarjan (int sz, int k) {init (sz, k);}

    void dfs (int v, int fa) {
        for (auto &u : e[v]) if (u != fa) {
            dfs (u, v);
            dsu.merge (u, v);
        }

        vis[v] = 1;

        for (auto &[u, idx] : eq[v]) if (vis[u])
            ans[idx] = dsu.find (u);
    }

    void init (int sz, int k) {
        n = sz, q = k;
        dsu.init (n);
        vis.resize(sz + 1);
        ans.resize(k);
        eq.resize(sz + 1);
        e.resize(sz + 1);
    }
};
