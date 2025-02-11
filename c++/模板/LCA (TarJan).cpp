class LCA_tarjan {
    void init_dsu (int n) {
        fa.resize(n + 1);
        iota (all(fa), 0);
    }

    int find (int x) {
        return fa[x] == x ? x : fa[x] = find(fa[x]);
    }

    void merge (int v, int u) {
        auto fv = find(v), fu = find(u);
        if (fv == fu) return ;
        fa[fv] = fu;
    }

public:
    vector <vector <int>> e;
    vector <vector <pair <int, int>>> eq;
    vector <int> vis, ans, fa;
    int n, q;
    
    LCA_tarjan () : n(0), q(0) {}
    LCA_tarjan (int sz, int k) {init (sz, k);}

    void dfs (int v, int fa) {
        for (auto &u : e[v]) if (u != fa) {
            dfs (u, v);
            merge (u, v);
        }

        vis[v] = 1;

        for (auto &[u, idx] : eq[v]) if (vis[u])
            ans[idx] = find (u);
    }

    void init (int sz, int k) {
        n = sz, q = k;
        init_dsu (n);
        vis.resize(sz + 1);
        ans.resize(k);
        eq.resize(sz + 1);
        e.resize(sz + 1);
    }
};
