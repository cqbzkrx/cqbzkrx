template <typename T>
class sgt {
    static constexpr int rt = 1;
    int n;

    struct Node {
        T ans;

        Node () : ans(0) {}
        Node (T x) {ans = x;}

        Node operator + (const Node &a) const {
            return Node (a.ans + ans);
        }
    };
    vector <Node> t;

    void build (const vector <T> &a, int p, int cl, int cr) {
        if (cl == cr) {t[p] = Node (a[cl]); return ;}
        auto lc = p << 1, rc = lc | 1, mid = (cl + cr) >> 1;
        build (a, lc, cl, mid); build (a, rc, mid + 1, cr);
        t[p] = t[lc] + t[rc];
    }

    void init (const vector <T> &a) {
        n = a.size();
        t.resize(n << 2);
        build (a, rt, 0, n - 1);
    }

    void modify (int i, int x, int p, int cl, int cr) {
        if (cl > i || cr < i) return ;
        if (cl == cr) {t[p] = Node (x); return ;}
        auto lc = p << 1, rc = lc | 1, mid = (cl + cr) >> 1;
        modify (i, x, lc, cl, mid); modify (i, x, rc, mid + 1, cr);
        t[p] = t[lc] + t[rc];
    }

    Node qry (int l, int r, int p, int cl, int cr) {
        if (cl > r || cr < l) return Node (0);
        if (cl >= l && cr <= r) return t[p];
        auto lc = p << 1, rc = lc | 1, mid = (cl + cr) >> 1;
        return qry (l, r, lc, cl, mid) + qry (l, r, rc, mid + 1, cr);
    }

    public:

    sgt () : n(0) {}
    sgt (const vector <T> &a) {init (a);}
    void modify (int i, T x) {modify (i, x, rt, 0, n - 1);}
    Node qry (int l, int r) {return qry (l, r, rt, 0, n - 1);}
};
