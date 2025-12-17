void solve () {
    int n, q, s; cin >> n >> q >> s;
    vector e (0, vector (0, pair (0, 0ll))); e.reserve (n << 3);
    vector t (0, pair (-1, -1));
    vector id (n + 1, -1);
    int num = 0;

    auto insert = [&]() -> int {
        e.emplace_back (vector (0, pair (0, 0ll)));
        t.emplace_back (pair (-1, -1));
        return num++;
    };

    auto build = [&](auto &&self, int cl, int cr, int op) -> int {
        if (cl == cr) {
            if (id[cl] == -1) id[cl] = insert ();
            return id[cl];
        }
        int p = insert ();
        auto mid = (cl + cr) >> 1;
        t[p].x = self (self, cl, mid, op);
        t[p].y = self (self, mid + 1, cr, op);
        if (op == 0) {
            e[p].emplace_back (t[p].x, 0);
            e[p].emplace_back (t[p].y, 0);
        }
        else {
            e[t[p].x].emplace_back (p, 0);
            e[t[p].y].emplace_back (p, 0);
        }
        return p;
    };

    int rt1 = build (build, 1, n, 0);    // in
    int rt2 = build (build, 1, n, 1);    // out

    // cerr << num << '\n';
    // for (int i = 1; i <= n; i++) cerr << id[i] << " \n"[i == n];
    // for (int i = 0; i < num; i++) cerr << e[i] << '\n';

    auto modify = [&](int v, int u, ll w) -> void {e[id[v]].emplace_back (id[u], w);};    // v -> u (w)

    auto modify2 = [&](auto &&self, int v, int l, int r, ll w, int p, int cl, int cr) -> void {    // v -> [l, r] (w)
        if (cl > r || cr < l) return ;
        if (cl >= l && cr <= r) {e[id[v]].emplace_back (p, w); return ;}
        auto lc = t[p].x, rc = t[p].y, mid = (cl + cr) >> 1;
        self (self, v, l, r, w, lc, cl, mid);
        self (self, v, l, r, w, rc, mid + 1, cr);
    };

    auto modify3 = [&](auto &&self, int l, int r, int u, ll w, int p, int cl, int cr) -> void {    // [l, r] -> u (w)
        if (cl > r || cr < l) return ;
        if (cl >= l && cr <= r) {e[p].emplace_back (id[u], w); return ;}
        auto lc = t[p].x, rc = t[p].y, mid = (cl + cr) >> 1;
        self (self, l, r, u, w, lc, cl, mid);
        self (self, l, r, u, w, rc, mid + 1, cr);
    };

    for (int i = 0; i < q; i++) {
        int op; cin >> op;
        if (op == 1) {    // v -> u (w)
            int v, u; ll w; cin >> v >> u >> w;
            modify (v, u, w);
        }
        else if (op == 2) {    // v -> [l, r] (w)
            int v, l, r; ll w; cin >> v >> l >> r >> w;
            modify2 (modify2, v, l, r, w, rt1, 1, n);
        }
        else {    // [l, r] -> u (w)
            int l, r, u; ll w; cin >> u >> l >> r >> w;
            modify3 (modify3, l, r, u, w, rt2, 1, n);
        }

        // cerr << "---------------------------------\n";
        // for (int i = 0; i < num; i++) cerr << e[i] << '\n';
        // cerr << "---------------------------------\n";
    }

    auto dij = [&](int s) -> vector <ll> {
        vector dis (num, INF); dis[s] = 0;
        vector vis (num, 0);
        using T = pair <ll, int>;
        priority_queue <T, vector <T>, greater <T>> q; q.emplace (0ll, s);
        while (q.size ()) {
            auto [_w, u] = q.top (); q.pop ();
            if (vis[u]) continue; vis[u] = 1;
            for (auto [v, w] : e[u]) if (dis[v] > dis[u] + w)
                dis[v] = dis[u] + w, q.emplace (dis[v], v);
        }
        return dis;
    };

    auto dis = dij (id[s]);
    for (int i = 1; i <= n; i++) cout << (dis[id[i]] == INF ? -1 : dis[id[i]]) << ' ';
    cout << '\n';
}
