class LCA {
public:
    int cnt, n;
    vector <int> son, siz, f, top, dep, rnk, dfn;
    vector <vector <int>> e;
    
    LCA () : cnt(0), n(0), son(vector (0, 0)), siz(vector (0, 0)), f(vector (0, 0)), top(vector (0, 0)), dep(vector (0, 0)),
            rnk(vector (0, 0)), dfn(vector (0, 0)), e(vector (0, vector (0, 0))) {}
    LCA (int sz, int rt, const vector <vector <int>> &a) {init (sz, rt, a);}

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
        dfn[v] = ++cnt;
        rnk[cnt] = v;
        if (son[v] == -1) return ;
        dfs2 (son[v], head);
        for (auto &u : e[v]) if (u != son[v] && u != f[v])
            dfs2 (u, u);
    }

    void init (int sz, int rt, const vector <vector <int>> &a) {
        n = sz, e = a, cnt = 0;
        son = siz = f = top = dep = rnk = dfn = vector (n + 1, 0);
        dfs1 (rt, 0);
        dfs2 (rt, rt);
    }

    int lca (int v, int u) {
        while (top[v] != top[u])
            if (dep[top[v]] < dep[top[u]]) u = f[top[u]];
            else v = f[top[v]];
        return (dep[u] > dep[v] ? v : u);
    }
};
