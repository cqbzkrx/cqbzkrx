namespace segment_tree {
    static constexpr ll INVALID = -INF;

    template <typename T = ll>
    struct Node {
        int lc, rc, key;
        T sum, lazy;
        Node (int _key = 0, T _sum = 0, int _lc = -1, int _rc = -1, T _lazy = INVALID) : sum (_sum), lc (_lc), rc (_rc), key (_key), lazy (_lazy) {}
        
        Node operator + (const Node &b) const {
            Node ret;
            ret.sum = b.sum + sum;
            ret.lc = key, ret.rc = b.key;
            return ret;
        }
    };

    template <typename T = ll, class info = Node <T>>
    class segtree_lazy {
    public:
        static constexpr int rt = 0;

        vector <info> t;
        int n, cnt;

        segtree_lazy (int _n = 0) : n (_n), cnt (0), t (vector (1, info (0))) {}
        segtree_lazy (const vector <T> &a) : cnt (0), n (a.size ()), t (vector (1, info (0))) {build (a, rt, 0, n - 1);}

        void build (const vector <T> &a, int p, int cl, int cr) {
            if (cl == cr) {t[p].sum = a[cl]; return ;}
            if (t[p].lc == -1) t.push_back (info (++cnt)), t[p].lc = cnt;
            if (t[p].rc == -1) t.push_back (info (++cnt)), t[p].rc = cnt;
            auto lc = t[p].lc, rc = t[p].rc, mid = (cl + cr) >> 1;
            build (a, lc, cl, mid), build (a, rc, mid + 1, cr);
            merge (t[p], t[lc], t[rc]);
        }

        void merge (info &s, const info &a, const info &b) {
            Node ret = a + b;
            ret.key = s.key;
            s = ret;
        }

        void downdate (info &s, T x, int len = 1) {
            s.sum += x * len;
            s.lazy = (s.lazy == INVALID ? 0 : s.lazy) + x;
        }

        void push_down (int p, int cl, int cr) {
            if (cl == cr) return ;
            auto lazy = t[p].lazy; t[p].lazy = INVALID;

            if (t[p].lc == -1) t.push_back (info (++cnt)), t[p].lc = cnt;
            if (t[p].rc == -1) t.push_back (info (++cnt)), t[p].rc = cnt;
            auto lc = t[p].lc, rc = t[p].rc, mid = (cl + cr) >> 1;

            if (lazy == INVALID) return ;
            downdate (t[lc], lazy, mid - cl + 1);
            downdate (t[rc], lazy, cr - mid);
        }

        void modify (int l, int r, T x, int p, int cl, int cr) {
            if (cl > r || cr < l) return ;
            if (cl >= l && cr <= r) {downdate (t[p], x, cr - cl + 1); return ;}
            push_down (p, cl, cr);
            auto lc = t[p].lc, rc = t[p].rc, mid = (cl + cr) >> 1;
            modify (l, r, x, lc, cl, mid);
            modify (l, r, x, rc, mid + 1, cr);
            merge (t[p], t[lc], t[rc]);
        }

        info qry (int l, int r, int p, int cl, int cr) {
            if (cl > r || cr < l) return info ();
            if (cl >= l && cr <= r) return t[p];
            push_down (p, cl, cr);
            auto lc = t[p].lc, rc = t[p].rc, mid = (cl + cr) >> 1;
            return qry (l, r, lc, cl, mid) + qry (l, r, rc, mid + 1, cr);
        }

        void modify (int l, int r, T x) {modify (l, r, x, rt, 0, n - 1);}
        info qry (int l, int r) {return qry (l, r, rt, 0, n - 1);}
    };
}
