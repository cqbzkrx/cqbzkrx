// https://www.luogu.com.cn/problem/P2627
// https://www.luogu.com.cn/record/263577179
// dp[i] = max {dp[j − 1] − sum[j]} + sum[i]   j -> i - k ~ i

void solve () {
    int n, k; cin >> n >> k;
    vector a (n + 1, 0ll);
    for (int i = 1; i <= n; i++) cin >> a[i];

    vector s (n + 1, 0ll);
    for (int i = 1; i <= n; i++) s[i] = s[i - 1] + a[i];

    vector dp (n + 1, 0ll);
    deque <ll> q; q.push_back (0);
    for (int i = 1; i <= n; i++) {
        dp[i] = dp[i - 1];
        while (q.size () && q.front () < i - k) q.pop_front ();

        auto maxn = (q.size () ? q.front () : 0);
        // cerr << maxn << ' ';
        if (maxn) cmax (dp[i], dp[maxn - 1] - s[maxn] + s[i]);
        else cmax (dp[i], s[i]);

        while (q.size () && q.back () != 0 && dp[q.back () - 1] - s[q.back ()] < dp[i - 1] - s[i]) q.pop_back ();
            q.push_back (i);
    }

    cout << dp[n] << '\n';

    // cerr << '\n';
    // for (int i = 1; i <= n; i++) cerr << dp[i] << ' ';
    // cerr << '\n';
}
