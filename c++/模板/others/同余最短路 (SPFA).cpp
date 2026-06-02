// https://www.luogu.com.cn/problem/P2371
// https://www.luogu.com.cn/record/280390345

void solve () {
    int n; ll l, r; cin >> n >> l >> r;
    vector a (n, 0);
    for (auto &v : a) cin >> v;
    sort (all(a));
    
    if (a == vector (n, 0)) {cout << 0 << '\n'; return ;}
    int m = *upper_bound (all(a), 0);

    vector e (m, vector (0, pair (0, 0ll)));
    for (int i = 0; i < m; i++) for (auto &v : a) if (v != m)
        e[i].emplace_back ((i + v) % m, v);

    auto spfa = [&](int s, int n) -> vector <ll> {
        vector dis (n + 1, INF); dis[s] = 0;
        vector vis (n + 1, 0);
        queue <int> q; q.push (s);
        while (q.size ()) {
            auto u = q.front (); q.pop ();
            vis[u] = 0;
            for (auto [v, w] : e[u]) {
                if (dis[v] > dis[u] + w) {
                    dis[v] = dis[u] + w;
                    if (!vis[v]) vis[v] = 1, q.push (v);
                }
            }
        }
        return dis;
    };

    auto dis = spfa (0, m);

    auto qry = [&](ll x) -> ll {  // [0, x]
        ll ans = 0;
        for (int i = 0; i < m; i++) if (dis[i] <= x)
            ans += (x - dis[i]) / m + 1;
        return ans;
    };

    cout << qry (r) - qry (l - 1) << '\n';
}
