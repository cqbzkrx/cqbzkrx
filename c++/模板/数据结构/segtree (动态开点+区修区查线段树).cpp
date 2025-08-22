namespace segment_tree {
    static constexpr ll INVALID = -1;

    template <typename T = ll>
    struct Node {
        int l, r;
        T val, lazy;
        Node (T _val = 0, int _l = -1, int _r = -1, T _lazy = INVALID) : 
            val (_val), l (_l), r (_r), lazy (_lazy) {}
    };

    template <typename T = ll, class info = Node <T>>
    class segtree {
    public:
        static constexpr int rt = 0;

        vector <info> t;
        int n, cnt;

        segtree (int _n = 0) : cnt (0) {init (_n);}
        segtree (const vector <T> &a) : cnt (0) {init (a);}

        void init (int _n = 0) {
            n = _n;
            t.push_back (info ());
        }

        void init (const vector <T> &a) {
            n = a.size ();
            t.reserve (n + 1 << 2);
            t.push_back (info ());
            build (a, rt, 0, n - 1);
        }

        int insert () {
            cnt++;
            t.push_back (info ());
            return cnt;
        }

        void build (const vector <T> &a, int p, int cl, int cr) {
            if (cl == cr) {t[p].val = a[cl]; return ;}
            if (t[p].l == -1) t[p].l = insert ();
            if (t[p].r == -1) t[p].r = insert ();
            auto lc = t[p].l, rc = t[p].r, mid = (cl + cr) >> 1;
            build (a, lc, cl, mid), build (a, rc, mid + 1, cr);
            merge (p, lc, rc);
        }

        void merge (int p, int lc, int rc) {
            t[p].val = t[lc].val + t[rc].val;
        }

        info merge (const info &a, const info &b) {
            info res;
            res.val = a.val + b.val;
            return res;
        }

        void get (info &s, T x, int len = 1) {
            s.val += x * len;
            s.lazy = (s.lazy == INVALID ? 0 : s.lazy) + x;
        }

        void push_down (int p, int cl, int cr) {
            if (cl == cr) return ;
            auto lazy = t[p].lazy; t[p].lazy = INVALID;

            if (t[p].l == -1) t[p].l = insert ();
            if (t[p].r == -1) t[p].r = insert ();
            auto lc = t[p].l, rc = t[p].r, mid = (cl + cr) >> 1;

            if (lazy == INVALID) return ;
            get (t[lc], lazy, mid - cl + 1);
            get (t[rc], lazy, cr - mid);
        }

        void modify (int l, int r, T x, int p, int cl, int cr) {
            if (cl > r || cr < l) return ;
            if (cl >= l && cr <= r) {get (t[p], x, cr - cl + 1); return ;}
            push_down (p, cl, cr);
            auto lc = t[p].l, rc = t[p].r, mid = (cl + cr) >> 1;
            modify (l, r, x, lc, cl, mid);
            modify (l, r, x, rc, mid + 1, cr);
            merge (p, lc, rc);
        }

        info qry (int l, int r, int p, int cl, int cr) {
            if (cl > r || cr < l) return info ();
            if (cl >= l && cr <= r) return t[p];
            push_down (p, cl, cr);
            auto lc = t[p].l, rc = t[p].r, mid = (cl + cr) >> 1;
            return merge (qry (l, r, lc, cl, mid), qry (l, r, rc, mid + 1, cr));
        }

        void modify (int l, int r, T x) {modify (l, r, x, rt, 0, n - 1);}
        void modify (int i, T x) {modify (i, i, x, rt, 0, n - 1);}
        info qry (int l, int r) {return qry (l, r, rt, 0, n - 1);}
        info qry (int i) {return qry (i, i, rt, 0, n - 1);}
    };
}
