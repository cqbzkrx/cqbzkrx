namespace sgt {
    static constexpr ll INVALID = -1;

    template <typename T>
    struct Node {
        T val, lazy;
        Node (T _val = 0) : val (_val), lazy (INVALID) {}
        Node operator + (const Node &rhs) const {
            Node ret;
            ret.val = val + rhs.val;
            return ret;
        }
    };

    template <typename T, class info = Node <T>>
    class segtree {
    public:
        static constexpr int rt = 1;
        vector <info> t;
        int n;

        segtree (int n = 0, T x = 0) {init (vector (n, x));}
        segtree (const vector <T> &a) {init (a);}
        void init (const vector <T> &a) {
            n = a.size ();
            t.resize (n << 2);

            auto build = [&](auto &&self, int p, int cl, int cr) -> void {
                if (cl == cr) {t[p] = info (a[cl]); return ;}
                auto lc = p << 1, rc = lc | 1, mid = (cl + cr) >> 1;
                self (self, lc, cl, mid); self (self, rc, mid + 1, cr);
                t[p] = t[lc] + t[rc];
            };
            build (build, rt, 0, n - 1);
        }

        void get (info &s, T x, int len = 1) {
            s.val = s.val + x * len;
            s.lazy = (s.lazy == INVALID ? 0 : s.lazy) + x;
        }

        void push_down (int p, int cl, int cr) {
            if (t[p].lazy == INVALID || cl == cr) return ;
            auto lc = p << 1, rc = lc | 1, mid = (cl + cr) >> 1;
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
            auto lc = p << 1, rc = lc | 1, mid = (cl + cr) >> 1;
            modify (l, r, x, lc, cl, mid);
            modify (l, r, x, rc, mid + 1, cr);
            t[p] = t[lc] + t[rc];
        }

        info qry (int i) {return qry (i, i, rt, 0, n - 1);}
        info qry (int l, int r) {return qry (l, r, rt, 0, n - 1);}
        info qry (int l, int r, int p, int cl, int cr) {
            if (cl > r || cr < l) return info ();
            if (cl >= l && cr <= r) return t[p];
            push_down (p, cl, cr);
            auto lc = p << 1, rc = lc | 1, mid = (cl + cr) >> 1;
            return qry (l, r, lc, cl, mid) + qry (l, r, rc, mid + 1, cr);
        }
    };
}
