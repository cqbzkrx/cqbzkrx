// https://www.luogu.com.cn/problem/P10505
// https://www.luogu.com.cn/record/277915729

void solve (int n, int k) {
    vector a (n, db (0)), b (n, db (0));
    for (auto &v : a) cin >> v;
    for (auto &v : b) cin >> v;

    auto check = [&](db mid) -> bool {
        vector c (n, db (0));
        for (int i = 0; i < n; i++) c[i] = a[i] - b[i] * mid;
        sort (all(c), greater ());

        db sum = 0;
        for (int i = 0; i < n - k; i++) sum += c[i];
        return sum >= 0;
    };

    db l = 0, r = 1e9, ans = 0;
    while (r - l > eps) {
        db mid = (l + r) / 2;
        if (check (mid)) l = mid, ans = mid;
        else r = mid;
    }

    cout << int (100 * ans + 0.5) << '\n';
}
