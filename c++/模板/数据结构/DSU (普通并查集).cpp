class DSU {
public:
    vector <int> fa, siz;
    // vector <vector <int>> son;

    DSU (int n = 0) {init (n);}

    int find (int x) {
        return fa[x] == x ? x : fa[x] = find(fa[x]);
    }

    bool same (int v, int u) {
        auto fv = find(v), fu = find(u);
        return fv == fu;
    }

    bool merge (int v, int u) {
        auto fv = find(v), fu = find(u);
        if (fv == fu) return 0;
        if (siz[fv] > siz[fu]) swap (fv, fu);

        fa[fv] = fu, siz[fu] += siz[fv];
        // for (auto &x : son[fv]) son[fu].push_back(x);
        return 1;
    }

    void init (int n) {
        fa.clear(), fa.resize (n + 1);
        iota (all(fa), 0);
        siz.clear(), siz.resize(n + 1);
        fill (all(siz), 1);

        // son.clear(), son.resize(n + 1);
        // for (int i = 1; i <= n; i++) son[i].clear(), son[i].push_back(i);
    }
};
