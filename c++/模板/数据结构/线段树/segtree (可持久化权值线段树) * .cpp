namespace sgt {
    const int MAXN = 2e5 + 7;

    template <typename T>
    struct Node {
        int lc, rc;
        T val;
        Node () : val (0), lc (-1), rc (-1) {}
        Node (T x, int _lc = -1, int _rc = -1) : val (x), lc (_lc), rc (_rc) {}
        Node operator + (const Node &rhs) const {
            Node ret;
            ret.val = val + rhs.val;
            return ret;
        }

        friend Node operator += (Node &lhs, const Node &rhs) {
            lhs = lhs + rhs;
            return lhs;
        }
    };

    template <typename T, class info = Node <T>>
    class segtree {
    public:
        vector <int> rt;
        vector <info> t;
        int n, num;

        segtree () : n (0), num (0) {}
        segtree (const vector <T> &a, int n) {
            num = 0;
            this -> n = n;
            t.reserve (MAXN << 2);
            rt.push_back (insert ());
            // for (auto v : rt) cerr << v << ' ';
            // cerr << '\n';
            for (int i = 1; i < (int) a.size (); i++) modify (a[i], a[i]);
        }

        int insert () {
            t.emplace_back ();
            return num++;
        }

        void modify (T i, T x) {
            auto root = rt.back ();
            rt.push_back (insert ());
            modify (i, x, rt.back (), root, 0, n - 1);
        }

        void merge (int p, int lc, int rc) {
            if (lc == -1 && rc == -1) return ;
            else if (lc == -1) t[p] = t[rc];
            else if (rc == -1) t[p] = t[lc];
            else t[p] = t[lc] + t[rc];
            t[p].lc = lc, t[p].rc = rc;
        }

        void modify (T i, T x, int p, int p2, T cl, T cr) {
            if (cl > i || cr < i) {t[p] = (p2 == -1 ? info () : t[p2]); return ;}
            if (cl == cr) {t[p].val = (p2 == -1 ? 0 : t[p2].val) + x; return ;}
            auto mid = (cl + cr) >> 1;
            if (mid >= i) {
                t[p].rc = (p2 == -1 ? -1 : t[p2].rc);
                t[p].lc = insert ();
                modify (i, x, t[p].lc, (p2 == -1 ? -1 : t[p2].lc), cl, mid);
            }
            else {
                t[p].lc = (p2 == -1 ? -1 : t[p2].lc);
                t[p].rc = insert ();
                modify (i, x, t[p].rc, (p2 == -1 ? -1 : t[p2].rc), mid + 1, cr);
            }

            merge (p, t[p].lc, t[p].rc);
        }

        T qry (T l, T r, T x, T y) {
            if (l > r) return 0;
            if (l == 0) return qry (x, y, rt[r], 0, n - 1).val;
            return qry (x, y, rt[r], 0, n - 1).val - qry (x, y, rt[l - 1], 0, n - 1).val;
        }
        info qry (T l, T r, int p, T cl, T cr) {
            if (cl > r || cr < l) return info ();
            if (cl >= l && cr <= r) return t[p];
            auto lc = t[p].lc, rc = t[p].rc, mid = (cl + cr) >> 1;
            info ans;
            if (lc != -1) ans += qry (l, r, lc, cl, mid);
            if (rc != -1) ans += qry (l, r, rc, mid + 1, cr);
            return ans;
        }
    };
}
