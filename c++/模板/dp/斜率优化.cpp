// https://vjudge.net/problem/HDU-3507

// dp[i] = min {dp[j] + (s[i] − s[j]) * (s[i] − s[j]) + M}   j -> 1 ~ i - 1
// => dp[j] + s[j] * s[j] = s[i] * 2 * s[j] + dp[i] − s[i] * s[i] − M
//    y -> dp[j] + s[j] * s[j]
//    k -> s[i]
//    x -> 2 * s[j]
//    b -> dp[i] − s[i] * s[i] − M

void solve () {
    int n; ll m; cin >> n >> m;
    vector a (n + 1, 0ll);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        if (a[i] == 0) i--, n--;
    }

    if (n == 0) {cout << m << '\n'; return ;}

    for (int i = 1; i <= n; i++) a[i] += a[i - 1];

    using T = pair <ll, ll>;
    auto check = [&](const T &x, const T &y, const T &z) -> bool {
        return (y.y - x.y) * (z.x - y.x) >= (y.x - x.x) * (z.y - y.y);
    };

    deque <T> q; q.emplace_back (0, 0);
    vector dp (n + 1, 0ll);
    for (int i = 1; i <= n; i++) {
        while (q.size () >= 2 && (q[1].y - q[0].y) <= a[i] * (q[1].x - q[0].x)) q.pop_front ();

        auto [v, u] = q.front ();
        dp[i] = u - a[i] * v + a[i] * a[i] + m;
        
        T nxt = {2 * a[i], dp[i] + a[i] * a[i]};
        while (q.size () >= 2 && check (*(q.end () - 2), *(q.end () - 1), nxt)) q.pop_back ();
        q.push_back (nxt);

        // cerr << q << '\n';
    }

    cout << dp[n] << '\n';

    // for (int i = 1; i <= n; i++) cerr << dp[i] << ' ';
    // cerr << '\n';
}
