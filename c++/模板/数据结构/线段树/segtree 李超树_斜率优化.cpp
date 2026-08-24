namespace sgt {
    static constexpr ll INVALID = INF;

    struct Node {
        ll k, b;
        Node () : k (0), b (INVALID) {}
        Node (ll _k, ll _b) : k (_k), b (_b) {}
        inline ll y (ll x) {return k * x + b;}
    };

    bool cmp (ll lhs, ll rhs) {
        return lhs <= rhs;
    }

    class segtree {
    public:
        static constexpr int rt = 1;
        vector <Node> t;
        int n;

        segtree (int n) {init (n);}

        void init (int n) {
            this -> n = n;
            t.resize (n << 2);
        }

        void modify (const Node &val) {modify (val, rt, 0, n - 1);}
        void modify (Node val, int p, int cl, int cr) {
            auto lc = p << 1, rc = lc | 1, mid = (cl + cr) >> 1;
            if (!cmp (t[p].y (mid), val.y (mid))) swap (t[p], val);
            if (!cmp (t[p].y (cl), val.y (cl))) modify (val, lc, cl, mid);
            if (!cmp (t[p].y (cr), val.y (cr))) modify (val, rc, mid + 1, cr);
        }

        ll qry (ll x) {return qry (x, rt, 0, n - 1);}
        ll qry (ll x, int p, int cl, int cr) {
            if (cl == cr) return t[p].y (x);
            auto lc = p << 1, rc = lc | 1, mid = (cl + cr) >> 1;

            ll ans = t[p].y (x);
            if (x <= mid) {
                ll res = qry (x, lc, cl, mid);
                return (cmp (ans, res) ? ans : res);
            }
            else {
                ll res = qry (x, rc, mid + 1, cr);
                return (cmp (ans, res) ? ans : res);
            }
        }
    };
}
