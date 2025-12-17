class HPD {
public:
    vector <vector <int>> e;
    vector <int> f, dep, dfn, son, top;
    int n, num;
    HPD () {}
    HPD (int n, int rt, vector <vector <int>> &a) {init (n, rt, a);}
    void init (int n, int rt, vector <vector <int>> &a) {
        e = move (a);
        this -> n = n; num = 0;
        top.assign (n + 1, 0);
        dep.assign (n + 1, 0);
        f.assign (n + 1, 0);
        dfn.assign (n + 1, 0);
        son.assign (n + 1, -1);

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
        };

        dfs (dfs, rt, 0);
        dfs2 (dfs2, rt, rt);
    }

    int lca (int v, int u) {
        while (top[v] != top[u]) {
            if (dep[top[v]] > dep[top[u]]) swap (v, u);
            u = f[top[u]];
        }
        return (dep[u] > dep[v] ? v : u);
    }
};
