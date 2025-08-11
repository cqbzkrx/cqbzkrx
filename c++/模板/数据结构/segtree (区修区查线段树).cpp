namespace segment_tree {
    static constexpr ll INVALID = -1;
    
    template <class T = ll>
    struct Node {
        T ans, lazy;
        Node (T _ans = 0, T _lazy = INVALID) : ans (_ans), lazy (_lazy) {}
    
        Node operator + (const Node &a) const {
            Node res;
            res.ans = a.ans + ans;
            return res;
        }
    };
    
    template <class T = ll, class info = Node <T>>
    class segtree {
    public:
        static constexpr int rt = 1;
        
        int n;
        vector <info> t;
    
        void build (const vector <T> &a, int p, int cl, int cr) {
            if (cl == cr) {t[p] = info (a[cl]); return ;}
            auto lc = p << 1, rc = lc | 1, mid = (cl + cr) >> 1;
            build (a, lc, cl, mid); build (a, rc, mid + 1, cr);
            t[p] = t[lc] + t[rc];
        }
    
        void modify (int l, int r, T x, int p, int cl, int cr) {
            if (cl > r || cr < l) return ;
            if (cl >= l && cr <= r) {get (t[p], x, cr - cl + 1); return ;}
            push_down (p, cl, cr);
            auto lc = p << 1, rc = lc | 1, mid = (cl + cr) >> 1;
            modify (l, r, x, lc, cl, mid);
            modify (l, r, x, rc, mid + 1, cr);
            t[p] = t[lc] + t[rc];
        }
    
        info qry (int l, int r, int p, int cl, int cr) {
            if (cl > r || cr < l) return info (0);
            if (cl >= l && cr <= r) return t[p];
            push_down (p, cl, cr);
            auto lc = p << 1, rc = lc | 1, mid = (cl + cr) >> 1;
            return qry (l, r, lc, cl, mid) + qry (l, r, rc, mid + 1, cr);
        }
    
        void get (info &s, T x, int len = 1) {
            s.ans += x * len;
            s.lazy = (s.lazy == INVALID ? x : s.lazy + x);
        }
    
        void push_down (int p, int cl, int cr) {
            if (cl == cr || t[p].lazy == INVALID) return ;
            auto lazy = t[p].lazy; t[p].lazy = INVALID;
    
            auto lc = p << 1, rc = lc | 1, mid = (cl + cr) >> 1;
            get (t[lc], lazy, mid - cl + 1);
            get (t[rc], lazy, cr - mid);
        }
        
        segtree (int _n = 0) : n (_n) {t.resize (_n << 2);}
        segtree (const vector <T> &a) {init (a);}
        void modify (int l, int r, T x) {modify (l, r, x, rt, 0, n - 1);}
        void modify (int i, T x) {modify (i, i, x, rt, 0, n - 1);}
        info qry (int l, int r) {return qry (l, r, rt, 0, n - 1);}
        info qry (int i) {return qry (i, i, rt, 0, n - 1);}
    
        void init (const vector <T> &a) {
            n = a.size();
            t.resize (n << 2);
            build (a, rt, 0, n - 1);
        }
    };
}
