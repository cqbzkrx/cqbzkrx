struct Node {
    int x, op, id;
    ll val;
    Node () : x (0), op (0), id (0), val (0) {}
    Node (int _x, int _op, int _id, ll _val) : x (_x), op (_op), id (_id), val (_val) {}
    bool operator < (const Node &rhs) const {
        if (x != rhs.x) return x < rhs.x;
        return op < rhs.op;
    };
};

void solve () {
    int n, q; cin >> n >> q;
    vector a (0, Node ()); a.reserve (n + q);
    for (int i = 0; i < n; i++) {
        ll x; cin >> x;
        a.emplace_back (i, 0, -1, x);
    }

    int num = 0;
    for (int i = 0; i < q; i++) {
        int op; cin >> op;
        if (op == 1) {
            int v; ll w; cin >> v >> w; v--;
            a.emplace_back (v, 0, -1, w);
        }
        else {
            int l, r; cin >> l >> r; l--, r--;
            if (l) a.emplace_back (l - 1, 1, num, -1);
            a.emplace_back (r, 1, num, 1);
            num++;
        }
    }

    vector ans (num, 0ll);
    auto dfs = [&](auto &&self, int l, int r) -> void {
        if (l >= r) return ;
        int mid = (l + r) >> 1;

        self (self, l, mid);
        self (self, mid + 1, r);

        int p1 = l, p2 = mid + 1;
        ll sum = 0;
        vector s (0, Node ());
        while (p1 <= mid && p2 <= r) {
            if (a[p1] < a[p2]) {
                if (a[p1].op == 0) sum += a[p1].val;
                s.push_back (a[p1]);
                p1++;
            }
            else {
                if (a[p2].op == 1) ans[a[p2].id] += a[p2].val * sum;
                s.push_back (a[p2]);
                p2++;
            }
        }

        while (p1 <= mid) {
            if (a[p1].op == 0) sum += a[p1].val;
            s.push_back (a[p1]);
            p1++;
        }

        while (p2 <= r) {
            if (a[p2].op == 1) ans[a[p2].id] += a[p2].val * sum;
            s.push_back (a[p2]);
            p2++;
        }

        for (int i = l; i <= r; i++) a[i] = s[i - l];
    };

    int m = a.size ();
    dfs (dfs, 0, m - 1);

    for (auto v : ans) cout << v << '\n';
}
