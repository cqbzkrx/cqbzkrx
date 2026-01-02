template <typename T, class info = sgt :: Node <T>>
class HPD {
public:
    vector <vector <int>> e;
    vector <int> f, dep, dfn, son, top, out;
    vector <T> s;
    sgt :: segtree <T> sgt;
    int n, num;
    HPD () {}
    HPD (int n, int rt, const vector <vector <int>> &e) {init (n, rt, e, vector <T> (n + 1, 0));}
    HPD (int n, int rt, const vector <vector <int>> &e, T x) {init (n, rt, e, vector <T> (n + 1, x));}
    HPD (int n, int rt, const vector <vector <int>> &e, const vector <T> &c) {init (n, rt, e, c);}
    void init (int n, int rt, const vector <vector <int>> &e, const vector <T> &c) {
        this -> e = e;
        this -> n = n; num = 0;
        top.assign (n + 1, 0);
        dep.assign (n + 1, 0);
        f.assign (n + 1, 0);
        dfn.assign (n + 1, 0);
        son.assign (n + 1, -1);
        out.assign (n + 1, 0);

        auto dfs = [&](auto &&self, int u, int fa) -> int {
            dep[u] = dep[fa] + 1; f[u] = fa;
            int maxn = 0, siz = 1;
            for (auto v : e[u]) if (v != fa) {
                auto csiz = self (self, v, u);
                if (csiz > maxn) maxn = csiz, son[u] = v;
                siz += csiz;
            }
            return siz;
        };

        auto dfs2 = [&](auto &&self, int u, int head) -> void {
            dfn[u] = num++; top[u] = head;
            if (son[u] != -1) self (self, son[u], head);
            for (auto v : e[u]) if (v != f[u] && v != son[u])
                self (self, v, v);
            out[u] = num - 1;
        };

        dfs (dfs, rt, 0);
        dfs2 (dfs2, rt, rt);

        s.resize (n);
        for (int i = 1; i <= n; i++) s[dfn[i]] = c[i];
        sgt.init (s);
    }

    int lca (int v, int u) {
        while (top[v] != top[u]) {
            if (dep[top[v]] > dep[top[u]]) swap (v, u);
            u = f[top[u]];
        }
        return (dep[u] > dep[v] ? v : u);
    }

    void modify (int v, int u, T x) {
        while (top[v] != top[u]) {
            if (dep[top[v]] > dep[top[u]]) swap (v, u);
            sgt.modify (dfn[top[u]], dfn[u], x);
            u = f[top[u]];
        }
        if (dep[v] > dep[u]) swap (v, u);
        sgt.modify (dfn[v], dfn[u], x);
    }

    info qry (int v, int u) {
        info ans;
        while (top[v] != top[u]) {
            if (dep[top[v]] > dep[top[u]]) swap (v, u);
            ans = ans + sgt.qry (dfn[top[u]], dfn[u]);
            u = f[top[u]];
        }
        if (dep[v] > dep[u]) swap (v, u);
        ans = ans + sgt.qry (dfn[v], dfn[u]);
        return ans;
    }

    void modify2 (int v, T x) {sgt.modify (dfn[v], out[v], x);}
    info qry2 (int v) {return sgt.qry (dfn[v], out[v]);}
};
