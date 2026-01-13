namespace sgt {
    template <typename T>
    struct Node {
        T val;
        Node (T x = 0) : val (x) {}
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

        segtree () {}
        segtree (int n, T x = 0) {init (vector <T> (n, x));}
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

        void get (info &s, T x) {
            s.val += x;
        }
        
        void modify (int i, T x) {modify (i, x, rt, 0, n - 1);}
        void modify (int i, T x, int p, int cl, int cr) {
            if (cl > i || cr < i) return ;
            if (cl == cr) {get (t[p], x); return ;}
            auto lc = p << 1, rc = lc | 1, mid = (cl + cr) >> 1;
            modify (i, x, lc, cl, mid); modify (i, x, rc, mid + 1, cr);
            t[p] = t[lc] + t[rc];
        }

        info qry (int i) {return qry (i, i, rt, 0, n - 1);}
        info qry (int l, int r) {return qry (l, r, rt, 0, n - 1);}
        info qry (int l, int r, int p, int cl, int cr) {
            if (cl > r || cr < l) return info ();
            if (cl >= l && cr <= r) return t[p];
            auto lc = p << 1, rc = lc | 1, mid = (cl + cr) >> 1;
            return qry (l, r, lc, cl, mid) + qry (l, r, rc, mid + 1, cr);
        }
    };
}
