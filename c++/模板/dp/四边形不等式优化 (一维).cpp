// https://www.luogu.com.cn/problem/P1912
// https://www.luogu.com.cn/record/264009807
// 方程 dp[i] = min {dp[j] + qpow (abs (s[i] - s[j] + i - j - 1 - l), p)}   j -> 1 ~ i - 1
//      dp[i] -> 到i位置的答案

void solve () {
    ll MAXN = 1e18;

    int n, k; ll L; cin >> n >> L >> k;
    vector a (n + 1, string ());
    for (int i = 1; i <= n; i++) cin >> a[i];

    vector s (n + 1, 0ll);
    for (int i = 1; i <= n; i++) s[i] = s[i - 1] + a[i].size ();

    auto qpow = [&](ldb a, int b) -> ldb {
        ldb ans = 1;
        while (b) {
            if (b & 1) ans *= a;
            a *= a;
            b >>= 1;
        }
        return ans;
    };

    vector dp (n + 1, ldb (0));
    auto calc = [&](int p, int l) -> ldb {
        ldb w = llabs (s[l] - s[p] + l - p - 1 - L);
        return dp[p] + qpow (w, k);
    };

    auto check = [&](int p, int i, int mid) -> bool {
        return calc (i, mid) <= calc (p, mid);
    };

    vector lst (n + 1, 0);
    deque <tuple <int, int, int>> q;    // [l, r, p]
    q.emplace_back (1, n, 0);

    for (int i = 1; i <= n; i++) {
        while (q.size () && get <1> (q.front ()) < i) q.pop_front ();
        if (q.size ()) cmax (get <0> (q.front ()), i);

        lst[i] = get <2> (q.front ());
        dp[i] = calc (get <2> (q.front ()), i);

        // for (auto [l, r, p] : q) cerr << "(" << l << ", " << r << ", " << p << ") ";
        // cerr << '\n' << '\n';

        if (q.size ()) cmax (get <0> (q.back ()), i);
        while (q.size ()) {
            auto [l, r, p] = q.back ();
            if (calc (i, l) <= calc (p, l)) q.pop_back ();
            else break;
        }

        if (!q.size ()) q.emplace_back (i, n, i);
        else {
            auto [l, r, p] = q.back ();
            int ans = r + 1;
            while (l <= r) {
                int mid = (l + r) >> 1;
                // cerr << mid << ' ' << check (p, i, mid) << ' ' << calc (i, mid) << ' ' << calc (p, mid) << '\n';
                if (check (p, i, mid)) r = mid - 1, ans = mid;
                else l = mid + 1;
            }
            // cerr << '\n';

            if (ans <= n) {
                get <1> (q.back ()) = ans - 1;
                q.emplace_back (ans, n, i);
            }
        }

        // for (auto [l, r, p] : q) cerr << "(" << l << ", " << r << ", " << p << ") ";
        // cerr << '\n';
    }

    // for (int i = 1; i <= n; i++) cerr << dp[i] << " \n"[i == n];

    if (dp[n] > MAXN) {cout << "Too hard to arrange\n"; return ;}
    else cout << (ll) dp[n] << '\n';

    // for (int i = 1; i <= n; i++) cerr << lst[i] << " \n"[i == n];

    vector c (0, 0);
    int now = n;
    while (now) {
        c.push_back (now);
        now = lst[now];
    }
    c.push_back (0);

    reverse (all(c));
    // for (auto v : c) cerr << v << ' '; cerr << '\n';

    for (int i = 1; i < c.size (); i++) {
        for (int j = c[i - 1] + 1; j <= c[i]; j++) {
            cout << a[j];
            if (j != c[i]) cout << ' ';
        }
        cout << '\n';
    }
}
