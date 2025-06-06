template <typename T = ll>
class HPD {
public:
    int cnt, n;
    vector <int> son, siz, f, top, dep, dfn, out;
    vector <vector <int>> e;
    vector <T> s;
    // segment_tree :: segtree_lazy <T> sgt;
    BIT :: BIT <T> bit;
    
    HPD () : n(0), cnt(0) {}
    HPD (int sz, int rt, const vector <vector <int>> &a, const vector <T> &c) : n(sz), e(a) {init (sz, rt, c);}

    void dfs1 (int v, int fa) {
        f[v] = fa;
        dep[v] = dep[fa] + 1;
        siz[v] = 1, son[v] = -1;
        
        int maxn = 0;
        for (auto &u : e[v]) if (u != fa) {
            dfs1 (u, v);
            siz[v] += siz[u];

            if (siz[u] > maxn) maxn = siz[u], son[v] = u;
        }
    }

    void dfs2 (int v, int head) {
        top[v] = head;
        dfn[v] = cnt++;
        if (son[v] != -1) dfs2 (son[v], head);
        for (auto &u : e[v]) if (u != son[v] && u != f[v])
            dfs2 (u, u);
        out[v] = cnt;
    }

    void init (int sz, int rt, const vector <T> &c) {
        cnt = 0;
        son = siz = f = top = dep = dfn = out = vector <int> (n + 1, 0);
        s.resize(n);

        dep[rt] = 1;
        dfs1 (rt, 0);
        dfs2 (rt, rt);

        for (int i = 1; i <= n; i++) s[dfn[i]] = c[i];
        bit = BIT :: BIT <T> (s);
    }

    int lca (int v, int u) {
        while (top[v] != top[u]) {
            if (dep[top[v]] < dep[top[u]]) u = f[top[u]];
            else v = f[top[v]];
        }
        return (dep[u] > dep[v] ? v : u);
    }

    T qry (int v, int u) {
        T ans = 0;
        while (top[v] != top[u]) {
            // if (dep[top[v]] < dep[top[u]]) ans += sgt.qry (dfn[top[u]], dfn[u]).ans, u = f[top[u]];
            // else ans += sgt.qry (dfn[top[v]], dfn[v]).ans, v = f[top[v]];
            if (dep[top[v]] < dep[top[u]]) ans += bit.qry (dfn[top[u]], dfn[u]), u = f[top[u]];
            else ans += bit.qry (dfn[top[v]], dfn[v]), v = f[top[v]];
        }
        
        if (dep[v] > dep[u]) swap (v, u);
        // ans += sgt.qry (dfn[v], dfn[u]).ans;
        ans += bit.qry (dfn[v], dfn[u]);
        return ans;
    }

    T qry2 (int v) {
        // return sgt.qry (dfn[v], out[v] - 1).ans;
        return bit.qry (dfn[v], out[v] - 1);
    }

    void modify (int v, int u, T x) {
        while (top[v] != top[u]) {
            // if (dep[top[v]] < dep[top[u]]) sgt.modify (dfn[top[u]], dfn[u], x), u = f[top[u]];
            // else sgt.modify (dfn[top[v]], dfn[v], x), v = f[top[v]];
            if (dep[top[v]] < dep[top[u]]) bit.modify (dfn[top[u]], dfn[u], x), u = f[top[u]];
            else bit.modify (dfn[top[v]], dfn[v], x), v = f[top[v]];
        }
        
        if (dep[v] > dep[u]) swap (v, u);
        // sgt.modify (dfn[v], dfn[u], x);
        bit.modify (dfn[v], dfn[u], x);
    }

    void modify2 (int v, T x) {
        // sgt.modify (dfn[v], out[v] - 1, x);
        bit.modify (dfn[v], out[v] - 1, x);
    }
};
