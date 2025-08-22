void solve () {
    int n, m; cin >> n >> m;
    vector a (n, pair (0, 0));
    vector pool_x (1, inf), pool_y (1, inf);
    for (auto &[v, u] : a) {
        cin >> v >> u;
        pool_x.push_back (v);
        pool_y.push_back (u);
    }

    struct Q {int a, b, c, d;};
    vector <Q> s (m);
    for (auto &[a, b, c, d] : s) {        // (a, b) 左下角 ,   (c, d) 右下角
        cin >> a >> b >> c >> d;
        pool_x.push_back (a);
        pool_y.push_back (b);
        pool_x.push_back (c);
        pool_y.push_back (d);
    }

    sort (all(pool_x)); pool_x.erase (unique (all(pool_x)), pool_x.end ());
    sort (all(pool_y)); pool_y.erase (unique (all(pool_y)), pool_y.end ());

    struct Node {       // type = ( 0 : 加点   1 : 加权   2 : 减权 )
        int type, x, y, id;
        Node (int _type = 0, int _x = 0, int _y = 0, int _id = 0) : 
            type (_type), x (_x), y (_y), id (_id) {}
        bool operator < (const Node &rhs) const {
            if (x == rhs.x) return type < rhs.type;
            return x < rhs.x;
        }
    };

    vector <Node> t (0, Node ());

    for (auto &[v, u] : a) {
        v = lower_bound (all(pool_x), v) - pool_x.begin () + 1;
        u = lower_bound (all(pool_y), u) - pool_y.begin () + 1;
        t.emplace_back (0, v, u, -1);
    }

    for (int i = 0; i < m; i++) {
        auto &[a, b, c, d] = s[i];
        a = lower_bound (all(pool_x), a) - pool_x.begin () + 1;
        b = lower_bound (all(pool_y), b) - pool_y.begin () + 1;
        c = lower_bound (all(pool_x), c) - pool_x.begin () + 1;
        d = lower_bound (all(pool_y), d) - pool_y.begin () + 1;
        t.emplace_back (1, c, d, i);              // + sum (c, d)
        t.emplace_back (1, a - 1, b - 1, i);      // + sum (a - 1, b - 1)
        t.emplace_back (2, a - 1, d, i);          // - sum (a - 1, d)
        t.emplace_back (2, c, b - 1, i);          // - sum (c, b - 1)
    }

    sort (all(t));

    int len = pool_y.size ();
    zkw_segment_tree :: segtree <int> sgt (len + 1);

    vector ans (m, 0);
    for (auto &[type, x, y, id] : t) {
        if (type == 0) sgt.modify (y, 1);
        else if (type == 1) ans[id] += sgt.qry (0, y);
        else ans[id] -= sgt.qry (0, y);
    }

    for (auto v : ans) cout << v << '\n';
}
