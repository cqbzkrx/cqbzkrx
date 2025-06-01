class DSU {
public:
    vector <int> fa, siz;
    vector <pair <int, int>> e;
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
        e.push_back ({fu, fv});

        fa[fv] = fu, siz[fu] += siz[fv];
        return 1;
    }

    void init (int n) {
        fa.clear(), fa.resize (n + 1);
        iota (all(fa), 0);
        siz.clear(), siz.resize(n + 1);
        fill (all(siz), 1);
    }

    int time () {
        return e.size();
    }

    void revert (int tm) {
        while ((int) e.size() > tm) {
            auto [x, y] = e.back();
            e.pop_back();
            fa[y] = y;
            siz[x] -= siz[y];
        }
    }

    void erase (int x) {
        revert (time () - x);
    }
};
