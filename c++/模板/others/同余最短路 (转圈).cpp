void solve () {
    int n; ll l, r; cin >> n >> l >> r;
    vector a (n, 0);
    for (auto &v : a) cin >> v;
    sort (all(a));
    if (a == vector (n, 0)) {cout << 0 << '\n'; return ;}
    int m = *upper_bound (all(a), 0);

    auto get_dis = [&](int m) -> vector <ll> {
        vector dis (m, INF); dis[0] = 0;
        for (auto v : a) if (v % m != 0) {
            vector vis (m, 0);
            for (int i = 0; i < m; i++) if (!vis[i]) {
                int rt = i, p = i;
                while (!vis[p]) {
                    vis[p] = 1;
                    if (dis[p] < dis[rt]) rt = p;
                    p = (p + v) % m;
                }

                ll w = (dis[rt] == INF ? INF : dis[rt] + v);
                p = (rt + v) % m;
                while (p != rt) {
                    cmin (dis[p], w);
                    w = (dis[p] == INF ? INF : dis[p] + v);
                    p = (p + v) % m;
                }
            }
        }

        return dis;
    };

    auto dis = get_dis (m);

    auto qry = [&](ll x) -> ll {  // [0, x]
        ll ans = 0;
        for (int i = 0; i < m; i++) if (dis[i] <= x)
            ans += (x - dis[i]) / m + 1;
        return ans;
    };

    cout << qry (r) - qry (l - 1) << '\n';
}
