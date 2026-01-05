namespace sgt {
    const int MAXN = 4e5 + 7;

    template <typename T>
    struct Node {
        int lc, rc;
        T val;
        Node () : val (0), lc (-1), rc (-1) {}
        Node (T x, int _lc = -1, int _rc = -1) : val (x), lc (_lc), rc (_rc) {}
        Node operator + (const Node &rhs) const {
            Node ret;
            ret.val = val + rhs.val;
            return ret;
        }
    };

    template <typename T, class info = Node <T>>
    class segtree {
    public:
        vector <int> rt;
        vector <info> t;
        int num, n;

        segtree (int n = 0) {init (vector <T> (n, 0));}
        segtree (const vector <T> &a) {init (a);}

        void init (const vector <T> &a) {
            n = a.size (); num = 0;
            t.reserve (MAXN << 2);
            rt.push_back (insert ());

            auto build = [&](auto &&self, int p, int cl, int cr) -> void {
                if (cl == cr) {t[p] = info (a[cl]); return ;}
                auto lc = insert (), rc = insert (), mid = (cl + cr) >> 1;
                self (self, lc, cl, mid); self (self, rc, mid + 1, cr);
                merge (p, lc, rc);
            };

            build (build, rt.back (), 0, n - 1);
        }

        int insert () {
            t.emplace_back ();
            return num++;
        }

        void get (info &s, const info &s2, T x) {
            s.val = s2.val + x;
        }
        
        void merge (int p, int lc, int rc) {
            if (lc == -1 && rc == -1) return ;
            else if (lc == -1) t[p] = t[rc];
            else if (rc == -1) t[p] = t[lc];
            else t[p] = t[lc] + t[rc];
            t[p].lc = lc, t[p].rc = rc;
        }

        void modify (int i, T x) {
            auto root = rt.back ();
            rt.push_back (insert ());
            modify (i, x, rt.back (), root, 0, n - 1);
        }

        void modify (int i, T x, int p, int p2, int cl, int cr) {
            if (cl > i || cr < i) {t[p] = t[p2]; return ;}
            if (cl == cr) {get (t[p], t[p2], x); return ;}
            auto mid = (cl + cr) >> 1;
            if (mid >= i) {
                t[p].rc = t[p2].rc;
                t[p].lc = insert ();
                modify (i, x, t[p].lc, t[p2].lc, cl, mid);
            }
            else {
                t[p].lc = t[p2].lc;
                t[p].rc = insert ();
                modify (i, x, t[p].rc, t[p2].rc, mid + 1, cr);
            }

            merge (p, t[p].lc, t[p].rc);
        }

        T qry_count (int l, int r, int x, int y) {
            if (l > r) return 0;
            l++, r++;
            return qry_count (x, y, rt[l - 1], rt[r], 0, n - 1);
        }

        T qry_count (int l, int r, int p, int p2, int cl, int cr) {
            if (cl > r || cr < l || p2 == -1) return 0;
            if (cl >= l && cr <= r) return t[p2].val - t[p].val;
            auto mid = (cl + cr) >> 1;
            return qry_count (l, r, t[p].lc, t[p2].lc, cl, mid) + qry_count (l, r, t[p].rc, t[p2].rc, mid + 1, cr);
        }

        T qry_min_kth (int l, int r, int k) {
            if (l > r) return -1;
            l++, r++;
            return qry_min_kth (k, rt[l - 1], rt[r], 0, n - 1);
        }

        T qry_min_kth (int k, int p, int p2, int cl, int cr) {
            if (cl == cr) return cl;
            auto mid = (cl + cr) >> 1, val = t[t[p2].lc].val - t[t[p].lc].val;
            if (val >= k) return qry_min_kth (k, t[p].lc, t[p2].lc, cl, mid);
            else return qry_min_kth (k - val, t[p].rc, t[p2].rc, mid + 1, cr);
        }

        T qry_max_kth (int l, int r, int k) {
            if (l > r) return -1;
            l++, r++;
            return qry_max_kth (k, rt[l - 1], rt[r], 0, n - 1);
        }

        T qry_max_kth (int k, int p, int p2, int cl, int cr) {
            if (cl == cr) return cl;
            auto mid = (cl + cr) >> 1, val = t[t[p2].rc].val - t[t[p].rc].val;
            if (val >= k) return qry_max_kth (k, t[p].rc, t[p2].rc, mid + 1, cr);
            else return qry_max_kth (k - val, t[p].lc, t[p2].lc, cl, mid);
        }
    };
}

void solve () {
    int n, q; cin >> n >> q;
    vector a (n, 0);
    for (auto &v : a) cin >> v;

    vector pool = a;
    sort (all(pool)); pool.erase (unique (all(pool)), pool.end ());
    for (auto &v : a) v = lower_bound (all(pool), v) - pool.begin ();

    sgt :: segtree <int> sgt (n);
    for (auto &v : a) sgt.modify (v, 1);

    while (q--) {
        int l, r, k; cin >> l >> r >> k;
        cout << pool[sgt.qry_min_kth (l - 1, r - 1, k)] << '\n';
    }
}
