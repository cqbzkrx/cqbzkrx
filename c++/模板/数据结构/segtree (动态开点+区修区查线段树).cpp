namespace sgt {
    static constexpr ll INVALID = -1;

    template <typename T>
    struct Node {
        T val, lazy;
        int lc, rc;
        Node (T _val = 0, int _lc = -1, int _rc = -1, T _lazy = INVALID) : val (_val), lc (_lc), rc (_rc), lazy (_lazy) {}
        Node operator + (const Node &rhs) const {
            Node ret;
            ret.val = val + rhs.val;
            return ret;
        }
    };

    template <typename T, class info = Node <T>>
    class segtree {
    public:
        static constexpr int rt = 0;
        vector <info> t;
        int n, num;

        segtree (int n = 0, T x = 0) {init (n, x);}
        void init (int n, T x) {
            this -> n = n;
            num = 0;
            t.assign (1, info (x * n, -1, -1, x));
        }

        int insert () {
            t.push_back (info ());
            return ++num;
        }

        void merge (int p, int lc, int rc) {
            t[p] = t[lc] + t[rc];
            t[p].lc = lc; t[p].rc = rc;
        }

        void get (info &s, T x, int len = 1) {
            s.val = s.val + x * len;
            s.lazy = (s.lazy == INVALID ? 0 : s.lazy) + x;
        }

        void push_down (int p, int cl, int cr) {
            if (t[p].lazy == INVALID || cl == cr) return ;
            if (t[p].lc == -1) t[p].lc = insert ();
            if (t[p].rc == -1) t[p].rc = insert ();
            auto lc = t[p].lc, rc = t[p].rc, mid = (cl + cr) >> 1;
            get (t[lc], t[p].lazy, mid - cl + 1);
            get (t[rc], t[p].lazy, cr - mid);
            t[p].lazy = INVALID;
        }

        void modify (int i, T x) {modify (i, i, x, rt, 0, n - 1);}
        void modify (int l, int r, T x) {modify (l, r, x, rt, 0, n - 1);}
        void modify (int l, int r, T x, int p, int cl, int cr) {
            if (cl > r || cr < l) return ;
            if (cl >= l && cr <= r) {get (t[p], x, cr - cl + 1); return ;}
            push_down (p, cl, cr);
            auto lc = t[p].lc, rc = t[p].rc, mid = (cl + cr) >> 1;
            modify (l, r, x, lc, cl, mid);
            modify (l, r, x, rc, mid + 1, cr);
            merge (p, lc, rc);
        }

        info qry (int i) {return qry (i, i, rt, 0, n - 1);}
        info qry (int l, int r) {return qry (l, r, rt, 0, n - 1);}
        info qry (int l, int r, int p, int cl, int cr) {
            if (cl > r || cr < l) return info ();
            if (cl >= l && cr <= r) return t[p];
            push_down (p, cl, cr);
            auto lc = t[p].lc, rc = t[p].rc, mid = (cl + cr) >> 1;
            return qry (l, r, lc, cl, mid) + qry (l, r, rc, mid + 1, cr);
        }
    };
}
