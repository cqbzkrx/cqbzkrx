namespace sgt {
    static constexpr ll INVALID = -INF;

    template <typename T>
    struct Node {
        T maxn, maxx, sum;
        int cnt;
        Node () : cnt (0), maxn (INVALID), sum (0), maxx (INVALID) {}
        Node (T x) : cnt (1), maxn (x), sum (x), maxx (INVALID) {}
        Node operator + (const Node &rhs) const {
            Node ret;
            ret.sum = sum + rhs.sum;
            ret.maxn = max (maxn, rhs.maxn);
            if (maxn == rhs.maxn) {
                ret.cnt = cnt + rhs.cnt;
                ret.maxx = max (maxx, rhs.maxx);
            }
            else if (maxn > rhs.maxn) {
                ret.cnt = cnt;
                ret.maxx = max (maxx, rhs.maxn);
            }
            else {
                ret.cnt = rhs.cnt;
                ret.maxx = max (maxn, rhs.maxx);
            }
            return ret;
        }
    };
    
    template <typename T, class info = Node <T>>
    class segtree_beats {
    public:
        static constexpr int rt = 1;
        vector <info> t;
        int n;

        segtree_beats (int n, T x = INVALID) {init (vector <T> (n, x));}
        segtree_beats (const vector <T> &a) {init (a);}

        void init (const vector <T> &a) {
            n = a.size ();
            t.resize (n << 2);

            auto dfs = [&](auto &&self, int p, int cl, int cr) -> void {
                if (cl == cr) {t[p] = info (a[cl]); return ;}
                auto lc = p << 1, rc = lc | 1, mid = (cl + cr) >> 1;
                self (self, lc, cl, mid);
                self (self, rc, mid + 1, cr);
                t[p] = t[lc] + t[rc];
            };
            
            dfs (dfs, rt, 0, n - 1);
        }

        inline void get (info &s, T x) {
            s.sum -= s.cnt * (s.maxn - x);
            s.maxn = x;
        }

        inline void push_down (int p, int cl, int cr) {
            if (cl == cr) return ;
            auto lc = p << 1, rc = lc | 1, mid = (cl + cr) >> 1;
            if (t[lc].maxn > t[p].maxn) get (t[lc], t[p].maxn);
            if (t[rc].maxn > t[p].maxn) get (t[rc], t[p].maxn); 
        }

        void modify (int l, int r, T x) {modify (l, r, x, rt, 0, n - 1);}
        void modify (int l, int r, T x, int p, int cl, int cr) {   // a[i] = min (a[i], x);
            if (cl > r || cr < l) return ;
            if (x >= t[p].maxn) return ;
            if (cl >= l && cr <= r && t[p].maxx < x) {get (t[p], x); return ;}
            push_down (p, cl, cr);
            auto lc = p << 1, rc = lc | 1, mid = (cl + cr) >> 1;
            modify (l, r, x, lc, cl, mid);
            modify (l, r, x, rc, mid + 1, cr);
            t[p] = t[lc] + t[rc];
        }

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
