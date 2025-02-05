class LCA_tarjan {
    class DSU_LCA_tarjan {
        public:

        vector <int> fa;

        void init (int n) {
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

        DSU_LCA_tarjan () : fa(vector (0, 0)) {}
        DSU_LCA_tarjan (int n) {init (n);}
    };

    public:

    vector <vector <int>> e;
    vector <vector <pair <int, int>>> eq;
    vector <int> vis, ans;
    int n, q;
    DSU_LCA_tarjan dsu;
    
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
        dsu.init (sz);
        vis.resize(sz + 1);
        ans.resize(k);
        eq.resize(sz + 1);
        e.resize(sz + 1);
    }
};
