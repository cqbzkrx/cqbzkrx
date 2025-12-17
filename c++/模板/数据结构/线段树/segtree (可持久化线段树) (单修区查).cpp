namespace sgt {
    static constexpr int MAXN = 2e5;

    template <typename T>
    struct Node {
        int lc, rc;
        T val;
        Node () : lc (-1), rc (-1), val (0) {}
        Node (T x, int _lc = -1, int _rc = -1) : val (x), lc (_lc), rc (_rc) {}
        Node operator + (const Node &rhs) const {
            Node ret;
            ret.val = rhs.val + val;
            return ret;
        }
    };

    template <typename T, class info = Node <T>>
    class segtree {
    public:
        vector <info> t;
        vector <int> rt;
        int num, num2, n;

        segtree () {init (vector (0, T (0)));}
        segtree (int n, T x = 0) {init (vector (n, x));}
        segtree (vector <T> &a) {init (a);}

        void merge (int p, int lc, int rc) {
            t[p] = t[lc] + t[rc];
            t[p].lc = lc, t[p].rc = rc;
        }

        int insert () {
            t.push_back (info ());
            return ++num;
        }

        void init (const vector <T> &a) {
            n = a.size (); num = num2 = 0;
            t.reserve (MAXN << 1);
            t.push_back (info ());
            rt.push_back (0);

            auto build = [&](auto &&self, int p, int cl, int cr) -> void {
                if (cl == cr) {t[p] = info (a[cl]); return ;}
                if (t[p].lc == -1) t[p].lc = insert ();
                if (t[p].rc == -1) t[p].rc = insert ();
                auto lc = t[p].lc, rc = t[p].rc, mid = (cl + cr) >> 1;
                self (self, lc, cl, mid); self (self, rc, mid + 1, cr);
                merge (p, lc, rc);
            };
            build (build, rt[0], 0, n - 1);
        }
        
        void copy (int root) {rt.push_back (rt[root]); num2++;}

        void modify (int i, T x, int root) {
            rt.push_back (insert ()); num2++;
            modify (i, x, rt[num2], rt[root], 0, n - 1);
        }

        void modify (int i, T x, int p, int root, int cl, int cr) {
            if (cl == cr) {t[p] = info (x); return ;}
            auto mid = (cl + cr) >> 1;
            if (mid >= i) {
                t[p].lc = insert (), t[p].rc = t[root].rc;
                modify (i, x, t[p].lc, t[root].lc, cl, mid);
            }
            else {
                t[p].lc = t[root].lc, t[p].rc = insert ();
                modify (i, x, t[p].rc, t[root].rc, mid + 1, cr);
            }
            merge (p, t[p].lc, t[p].rc);
        }

        info qry (int i, int root) {return qry (i, i, root);}
        info qry (int l, int r, int root) {return qry (l, r, rt[root], 0, n - 1);}
        info qry (int l, int r, int p, int cl, int cr) {
            if (cl > r || cr < l) return info ();
            if (cl >= l && cr <= r) return t[p];
            auto lc = t[p].lc, rc = t[p].rc, mid = (cl + cr) >> 1;
            return qry (l, r, lc, cl, mid) + qry (l, r, rc, mid + 1, cr);
        }
    };
}
