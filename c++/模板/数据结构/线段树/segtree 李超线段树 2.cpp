namespace sgt {
    static constexpr ll INVALID = INF;
    int num = 0;

    struct Node {
        ll k, b;
        int id;
        Node () : k (0), b (INVALID), id (0) {}
        Node (ll _k, ll _b) : k (_k), b (_b), id (++num) {}
        inline ll y (int x) const {return k * x + b;}
    };

    inline bool cmp (const Node &lhs, const Node &rhs, int x) {
        if (lhs.y (x) == rhs.y (x)) return lhs.id < rhs.id;
        return lhs.y (x) < rhs.y (x);
    }

    class segtree {
    public:
        static constexpr int rt = 1;
        vector <Node> t;
        int n;

        segtree (int n) {
            this -> n = n;
            t.resize (n + 1 << 2);
        }

        void modify (int l, int r, const Node &val) {modify (l, r, val, rt, 0, n - 1);}
        void modify (int l, int r, const Node &val, int p, int cl, int cr) {
            if (cl > r || cr < l) return ;
            auto lc = p << 1, rc = lc | 1, mid = (cl + cr) >> 1;
            if (cl >= l && cr <= r) {
                Node v = val;
                if (cmp (v, t[p], mid)) swap (v, t[p]);
                if (cl == cr) return ;
                if (cmp (v, t[p], cl)) modify (l, r, v, lc, cl, mid);
                if (cmp (v, t[p], cr)) modify (l, r, v, rc, mid + 1, cr);
                return ;
            }

            modify (l, r, val, lc, cl, mid);
            modify (l, r, val, rc, mid + 1, cr);
        }

        Node qry (int x) {return qry (x, rt, 0, n - 1);}
        Node qry (int x, int p, int cl, int cr) {
            if (cl > x || cr < x) return Node ();
            if (cl == cr) return t[p];
            auto lc = p << 1, rc = lc | 1, mid = (cl + cr) >> 1;

            Node ans;
            if (x <= mid) ans = qry (x, lc, cl, mid);
            else ans = qry (x, rc, mid + 1, cr);

            if (cmp (ans, t[p], x)) return ans;
            return t[p];
        }
    };
}
