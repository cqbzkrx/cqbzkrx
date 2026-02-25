// https://www.luogu.com.cn/problem/P1775
// https://www.luogu.com.cn/record/264011630

void solve () {
    int n; cin >> n;
    vector a (n + 1, 0ll);
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) a[i] += a[i - 1];

    vector dp (n + 1, vector (n + 1, INF));
    vector s (n + 1, vector (n + 1, 0));
    for (int i = 1; i <= n; i++) {
        dp[i][i] = 0;
        s[i][i] = i;
    }

    for (int len = 2; len <= n; len++) for (int i = 1; i + len - 1 <= n; i++) {
        int j = i + len - 1;
        for (int k = s[i][j - 1]; k <= min (j - 1, s[i + 1][j]); k++) if (dp[i][j] > dp[i][k] + dp[k + 1][j] + a[j] - a[i - 1]) {
            dp[i][j] = dp[i][k] + dp[k + 1][j] + a[j] - a[i - 1];
            s[i][j] = k;
        }
    }

    cout << dp[1][n] << '\n';
}
