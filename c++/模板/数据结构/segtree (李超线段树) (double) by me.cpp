namespace segment_tree {
    struct line {
        db k, b;
        int id;
        line (db _k = 0, db _b = 0, int _id = 0) : 
           k (_k), b (_b), id (_id) {}
        
        db get (int x) const {
            return k * x + b;
        }
    };

    int cmp (const line &a, const line &b, int x) {
        auto v = a.get (x);
        auto u = b.get (x);
        if (abs (v - u) <= eps) return b.id < a.id;
        return v < u;
    }

    line get (int &x1, int &y1, int &x2, int &y2, int id) {
        line ret; ret.id = id;
        if (x1 > x2) swap (x1, x2), swap (y1, y2);

        if (x1 == x2) ret.k = 0, ret.b = max (y1, y2);
        else {
            ret.k = (db) (y2 - y1) / (x2 - x1);
            ret.b = (db) y1 - (db) ret.k * x1;
        }

        return ret;
    }

    struct Node {
        line l;
        int lazy;
        Node (line _l = line (), int _lazy = 0) :
            l (_l), lazy (_lazy) {}
    };

    class segtree {
    public:
        static constexpr int rt = 1;

        int n;
        vector <Node> t;

        segtree (int _n = 0) : n (_n) {t.resize ((_n + 1) << 2);}
        segtree (int _n, const vector <tuple <int, int, line>> &a) : segtree (_n) {init (a);}

        void init (const vector <tuple <int, int, line>> &a) {
            for (auto &[l, r, s] : a) modify (l, r, s);
        };

        void modify (int l, int r, const line &x, int p, int cl, int cr) {
            if (cl > r || cr < l) return ;
            auto lc = p << 1, rc = lc | 1, mid = (cl + cr) >> 1;
            if (cl >= l && cr <= r) {
                if (!t[p].lazy) {
                    t[p].l = x; t[p].lazy = 1;
                    return ;
                }
                auto v = x;
                if (cmp (t[p].l, v, mid)) swap (v, t[p].l);
                if (cmp (t[p].l, v, cl)) modify (l, r, v, lc, cl, mid);
                if (cmp (t[p].l, v, cr)) modify (l, r, v, rc, mid + 1, cr);
                return ;
            }
            modify (l, r, x, lc, cl, mid); modify (l, r, x, rc, mid + 1, cr);
        }

        void modify (int l, int r, const line &x) {modify (l, r, x, rt, 0, n);}

        line qry (int x, int p, int cl, int cr) {
            if (cl > x || cr < x) return line ();
            if (cl == cr) return t[p].l;

            auto lc = p << 1, rc = lc | 1, mid = (cl + cr) >> 1;

            line ans;
            if (x <= mid) ans = qry (x, lc, cl, mid);
            else ans = qry (x, rc, mid + 1, cr);
            
            if (cmp (t[p].l, ans, x)) return ans;
            return t[p].l;
        }

        line qry (int x) {return qry (x, rt, 0, n);}
    };
};
