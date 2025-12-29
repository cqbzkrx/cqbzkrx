namespace ST {
    static constexpr int INVALID = inf;
    struct Node {
        int val, id;
        Node () : val (INVALID), id (-1) {}
        Node (int x, int idx) : val (x), id (idx) {}
        Node operator + (const Node &rhs) const {
            Node ret;
            if (val < rhs.val) ret.val = val, ret.id = id;
            else ret.val = rhs.val, ret.id = rhs.id;
            return ret;
        }
    };

    class ST {
    public:
        vector <vector <Node>> f;
        ST () {}
        ST (const vector <pair <int, int>> &a) {init (a);}
        void init (const vector <pair <int, int>> &a) {
            int n = a.size (), lim = __lg (n) + 1;
            f.assign (lim, vector <Node> (n, Node ()));
            for (int i = 0; i < n; i++) f[0][i] = Node (a[i].x, a[i].y);
            for (int i = 1; i < lim; i++) for (int j = 0; j < n; j++) {
                if (j + (1 << i) > n) break;
                f[i][j] = f[i - 1][j] + f[i - 1][j + (1 << (i - 1))];
            }
        }

        Node qry (int l, int r) {
            int lg = __lg (r - l + 1);
            return f[lg][l] + f[lg][r - (1 << lg) + 1];
        }
    };
}

class LCA {
public:
    vector <int> fst;
    ST :: ST st;
    int n, rt;

    LCA (const vector <vector <int>> &e, int n, int rt) {init (e, n, rt);}
    void init (const vector <vector <int>> &e, int n, int rt) {
        this -> n = n;
        this -> rt = rt;
        fst.assign (n + 1, 0);

        vector dep (n + 1, 0);
        auto dfs = [&](auto &&self, int u, int fa) -> void {
            dep[u] = dep[fa] + 1;
            for (auto v : e[u]) if (v != fa)
                self (self, v, u);
        };
        
        vector t (0, pair (0, 0)); t.reserve (n << 1);
        int num = 0;
        auto dfs2 = [&](auto &&self, int u, int fa) -> void {
            t.emplace_back (dep[u], u);
            fst[u] = num++;
            for (auto v : e[u]) if (v != fa) {
                self (self, v, u);
                t.emplace_back (dep[u], u);
                num++;
            }
        };

        dfs (dfs, rt, 0);
        dfs2 (dfs2, rt, 0);

        st.init (t);
    }

    int lca (int v, int u) {
        auto fv = fst[v], fu = fst[u];
        if (fv > fu) swap (fv, fu);
        return st.qry (fv, fu).id;
    }
};
