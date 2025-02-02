class DSU {
    public:
    
    vector <int> fa, siz;
    vector <vector <int>> e;

    DSU () : fa(vector (0, 0)), siz(vector (0, 0)), e(vector (0, vector (0, 0))) {}
    DSU (int n) {init (n);}

    int find (int x) {
        return fa[x] == x ? x : fa[x] = find(fa[x]);
    }

    bool merge (int v, int u) {
        auto fv = find(v), fu = find(u);
        if (fv == fu) return 0;
        if (siz[fv] > siz[fu]) swap (fv, fu);

        fa[fv] = fu, siz[fu] += siz[fv];
        // for (auto &x : e[fv]) e[fu].push_back(x);
        return 1;
    }

    protected:

    void init (int n) {
        fa.clear(), fa.resize (n + 1);
        iota (all(fa), 0);
        siz.clear(), siz.resize(n + 1);
        fill (all(siz), 1);

        // e.clear(), e.resize(n + 1);
        // for (int i = 1; i <= n; i++) e[i].clear(), e[i].push_back(i);
    }
};