template <typename T>
class sgt_lazy {
    protected:

    int n;
    static constexpr int rt = 1;
    static constexpr T INVALID = -INF;
    
    struct Node {
        T ans, lazy;

        Node () : ans(0), lazy(INVALID) {}
        Node (T x, T inv = INVALID) {ans = x, lazy = inv;}
        Node operator + (const Node &a) const {return Node (a.ans + ans);}
    };
    vector<Node> t;

    void build (const vector <T> &a, int p, int cl, int cr) {
        if (cl == cr) {t[p] = Node (a[cl]); return ;}
        auto lc = p << 1, rc = lc | 1, mid = (cl + cr) >> 1;
        build (a, lc, cl, mid); build (a, rc, mid + 1, cr);
        t[p] = t[lc] + t[rc];
    }

    void init(const vector<T>& a) {
        n = a.size();
        t.resize(n << 2);
        build(a, rt, 0, n - 1);
    }

    void merge (Node &s, const T &x, int len = 1) {
        s.lazy = (s.lazy == INVALID ? x : s.lazy + x);
        s.ans += len * x;
    }

    void push_down (int p, int cl, int cr) {
        if (cl == cr || t[p].lazy == INVALID) return ;
        auto lazy = t[p].lazy; t[p].lazy = INVALID;

        auto lc = p << 1, rc = lc | 1, mid = (cl + cr) >> 1;
        merge (t[lc], lazy, mid - cl + 1);
        merge (t[rc], lazy, cr - mid);
    }

    void modify (int l, int r, T x, int p, int cl, int cr) {
        if (cl > r || cr < l) return ;
        if (cl >= l && cr <= r) {
            merge (t[p], x, cr - cl + 1);
            return ;
        }
        push_down (p, cl, cr);
        auto lc = p << 1, rc = lc | 1, mid = (cl + cr) >> 1;
        modify (l, r, x, lc, cl, mid);
        modify (l, r, x, rc, mid + 1, cr);
        t[p] = t[lc] + t[rc];
    }

    Node qry (int l, int r, int p, int cl, int cr) {
        if (cl > r || cr < l) return Node (0);
        if (cl >= l && cr <= r) return t[p];
        push_down (p, cl, cr);
        auto lc = p << 1, rc = lc | 1, mid = (cl + cr) >> 1;
        return qry (l, r, lc, cl, mid) + qry (l, r, rc, mid + 1, cr);
    }

    public:

    sgt_lazy () : n(0) {}
    sgt_lazy (const vector <T> &a) {init (a);}

    void modify(int l, int r, T x) {modify(l, r, x, rt, 0, n - 1);}
    Node qry(int l, int r) {return qry(l, r, rt, 0, n - 1);}
};