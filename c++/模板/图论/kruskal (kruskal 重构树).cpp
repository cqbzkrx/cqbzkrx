class DSU {
public:
    vector <int> fa, siz, a;
    int num;
    DSU (int n = 0) {init (n);}

    int find (int x) {
        return fa[x] == x ? x : fa[x] = find (fa[x]);
    }

    bool same (int v, int u) {
        auto fv = find (v), fu = find (u);
        return fv == fu;
    }

    int merge (int v, int u) {
        auto fv = find (v), fu = find (u);
        if (fv == fu) return 0;
        if (siz[fv] > siz[fu]) swap (fv, fu);
        fa[fv] = fu, siz[fu] += siz[fv];
        fa[++num] = fu; 
        return a[fu] = num;
    }

    void init (int n) {
        num = n;
        fa.resize (n << 1); iota (all(fa), 0);
        siz.assign (n << 1, 1);
        a.resize (n << 1); iota (all(a), 0);
    }
};

vector eq (m, tuple (0, 0, 0ll));
sort (all(eq), [&](auto &lhs, auto &rhs) {return get <2> (lhs) < get <2> (rhs);});

DSU dsu (n);
vector s ((n << 1), INF);
// vector e ((n << 1), vector (0, 0));
vector lc (n << 1, -1), rc (n << 1, -1);
for (auto &[v, u, w] : eq) {
    if (dsu.same (v, u)) continue;
    
    auto fv = dsu.a[dsu.find (v)], fu = dsu.a[dsu.find (u)];
    auto fa = dsu.merge (v, u);
    // e[fa].push_back (fv); e[fv].push_back (fa);
    // e[fa].push_back (fu); e[fu].push_back (fa);
    lc[fa] = fv, rc[fa] = fu;
    s[fa] = w;
}
