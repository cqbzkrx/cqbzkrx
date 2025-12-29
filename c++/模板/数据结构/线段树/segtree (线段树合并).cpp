vnamespace sgt {
    const int MAXN = 2e5 + 7;
    using T = int;

    struct Node {
        int lc, rc;
        T val;
        Node () : val (0), lc (-1), rc (-1) {}
        Node (T x, int _lc = -1, int _rc = -1) : val (x), lc (_lc), rc (_rc) {}

        friend Node operator += (Node &lhs, const Node &rhs) {
            lhs.val += rhs.val;
            return lhs;
        }
    };

    vector <Node> t (0, Node ());
    int num = 0, n = 0;

    int insert () {
        t.emplace_back (Node ());
        return num++;
    }

    Node merge (const Node &lhs, const Node &rhs) {
        Node ret;
        ret.val = lhs.val + rhs.val;
        return ret;
    }

    void merge (int p, int lc, int rc) {
        if (lc == -1 && rc == -1) t[p] = Node ();
        else if (lc == -1) t[p] = t[rc];
        else if (rc == -1) t[p] = t[lc];
        else t[p] = merge (t[lc], t[rc]);
        t[p].lc = lc, t[p].rc = rc;
    }

    void get (Node &s, T x) {
        s.val += x;
    }
    
    void modify (int i, T x, int p, int cl, int cr) {
        if (cl > i || cr < i) return ;
        if (cl == cr) {get (t[p], x); return ;}
        if (t[p].lc == -1) t[p].lc = sgt :: insert ();
        if (t[p].rc == -1) t[p].rc = sgt :: insert ();
        auto lc = t[p].lc, rc = t[p].rc, mid = (cl + cr) >> 1;
        modify (i, x, lc, cl, mid); modify (i, x, rc, mid + 1, cr);
        merge (p, lc, rc);
    }

    Node qry (int l, int r, int p, int cl, int cr) {
        if (cl > r || cr < l || p == -1) return Node ();
        if (cl >= l && cr <= r) return t[p];
        auto lc = t[p].lc, rc = t[p].rc, mid = (cl + cr) >> 1;
        return merge (qry (l, r, lc, cl, mid), qry (l, r, rc, mid + 1, cr));
    }

    int qry2 (int p, int cl, int cr) {
        if (cl == cr) return cl;
        auto lc = t[p].lc, rc = t[p].rc, mid = (cl + cr) >> 1;
        int ans = 0;
        if (lc != -1 && (rc == -1 || t[lc].val >= t[rc].val)) ans = qry2 (lc, cl, mid);
        else if (rc != -1) ans = qry2 (rc, mid + 1, cr);
        return ans;
    }

    class segtree {
    public:
        int rt;
        segtree () : rt (sgt :: insert ()) {}
        segtree (const vector <T> &a) {init (a);}
        
        void init (const vector <T> &a) {
            rt = sgt :: insert ();

            auto build = [&](auto &&self, int p, int cl, int cr) -> void {
                if (cl == cr) {t[p] = Node (a[cl]); return ;}
                t[p].lc = sgt :: insert ();
                t[p].rc = sgt :: insert ();
                auto lc = t[p].lc, rc = t[p].rc, mid = (cl + cr) >> 1;
                self (self, lc, cl, mid); self (self, rc, mid + 1, cr);
                merge (p, lc, rc);
            };

            build (build, rt, 0, n - 1);
        }

        void modify (int i, T x) {sgt :: modify (i, x, rt, 0, n - 1);}
        Node qry (int i) {return qry (i, i);}
        Node qry (int l, int r) {return sgt :: qry (l, r, rt, 0, n - 1);}

        int qry2 () {return sgt :: qry2 (rt, 0, n - 1);}

        friend segtree operator += (segtree &lhs, const segtree &rhs) {
            auto dfs = [&](auto &&self, int p, int p2, int cl, int cr) -> int {
                if (p == -1) return p2;
                if (p2 == -1) return p;
                if (cl == cr) {t[p] += t[p2]; return p;}
                auto mid = (cl + cr) >> 1;
                t[p].lc = self (self, t[p].lc, t[p2].lc, cl, mid);
                t[p].rc = self (self, t[p].rc, t[p2].rc, mid + 1, cr);
                merge (p, t[p].lc, t[p].rc);
                return p;
            };

            lhs.rt = dfs (dfs, lhs.rt, rhs.rt, 0, n - 1);
            return lhs;
        }

        friend segtree operator + (segtree lhs, const segtree &rhs) {
            lhs += rhs;
            return lhs;
        }
    };
}
