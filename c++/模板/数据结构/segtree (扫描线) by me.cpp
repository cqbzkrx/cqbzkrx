namespace segment_tree {
    struct Node {
        int cnt, len;
        Node (int _cnt = 0, int _len = 0) : 
            cnt (_cnt), len (_len) {}

        Node operator + (const Node &rhs) const {
            Node ret;
            ret.len = len + rhs.len;
            return ret;
        }
    };

    template <class info = Node>
    class segtree {
    public:
        static constexpr int rt = 1;

        vector <int> pool;
        vector <info> t;
        int n;

        segtree (int _n = 0) : n (_n) {
            t.resize (_n << 2);
            pool.resize (_n + 1); iota (all(pool), 0);
        }

        segtree (const vector <int> &_pool) {
            pool = _pool;
            n = pool.size () - 1;
            t.resize (n << 2);
        }

        void get (int x, int p, int cl, int cr) {
            t[p].cnt += x;
            t[p].len = (t[p].cnt != 0) * (pool[cr + 1] - pool[cl]);
        }

        void merge (int p, int cl, int cr) {
            auto lc = p << 1, rc = lc | 1, mid = (cl + cr) >> 1;
            if (!t[p].cnt) t[p] = t[lc] + t[rc];
            else t[p].len = pool[cr + 1] - pool[cl];
        }
        
        void modify (int l, int r, int x, int p, int cl, int cr) {
            if (cl > r || cr < l) return ;
            if (cl == cr) {get (x, p, cl, cr); return ;}
            auto lc = p << 1, rc = lc | 1, mid = (cl + cr) >> 1;
            if (cl >= l && cr <= r) {
                t[p].cnt += x;
                merge (p, cl, cr);
                return ;
            }
            modify (l, r, x, lc, cl, mid); modify (l, r, x, rc, mid + 1, cr);
            merge (p, cl, cr);
        }

        void modify (int l, int r, int x) {modify (l, r, x, rt, 0, n - 1);}

        info qry () {return t[rt];}
    };
}

void solve () {
    int n; cin >> n;
    vector e (0, tuple (0, 0, 0, 0));
    vector pool (1, inf);

    for (int i = 0; i < n; i++) {
        int x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
        if (y1 > y2) swap (x1, x2), swap (y1, y2);
        pool.push_back (x1), pool.push_back (x2);
        e.emplace_back (y1, x1, x2, 1);
        e.emplace_back (y2, x1, x2, -1);
    }

    sort (all(pool)); pool.erase (unique (all(pool)), pool.end ());
    sort (all(e));

    for (auto &[y, x1, x2, op] : e) {
        x1 = lower_bound (all(pool), x1) - pool.begin ();
        x2 = lower_bound (all(pool), x2) - pool.begin ();
    }

    segment_tree :: segtree sgt (pool);

    ll lst = 0, ans = 0;
    for (auto &[y, x1, x2, op] : e) {
        auto v = sgt.qry ().len;
        ans += (y - lst) * v;
        sgt.modify (x1, x2 - 1, op);
        lst = y;
    }
    cout << ans << '\n';
}
