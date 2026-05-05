void solve () {
    int n; cin >> n;
    vector a (n, vector (n + 1, db (0)));
    for (int i = 0; i < n; i++) for (int j = 0; j <= n; j++)
        cin >> a[i][j];

    auto gauss = [&](int n, vector <vector <db>> &a) -> void {
        for (int i = 0; i < n; i++) {
            int maxi = i;
            for (int j = 0; j < n; j++) {
                if (j < i && fabs (a[j][j]) > eps) continue;
                if (fabs (a[j][i]) > fabs (a[maxi][i])) maxi = j;
            }

            swap (a[i], a[maxi]);
            if (fabs (a[i][i]) < eps) continue;

            for (int j = 0; j < n; j++) {
                if (i == j) continue;
                db v = a[j][i] / a[i][i];
                for (int k = i; k <= n; k++) a[j][k] -= v * a[i][k];
            }
        }

        for (int i = 0; i < n; i++) {
            if (fabs (a[i][i]) < eps) continue;
            a[i][n] /= a[i][i];
            a[i][i] = 1.0;
        }
    };

    gauss (n, a);

    for (int i = 0; i < n; i++) if (fabs (a[i][i]) < eps && fabs (a[i][n]) > eps) { // 无解
        cout << -1 << '\n';
        return ;
    }

    vector ans (n, db (0));
    for (int i = 0; i < n; i++) {
        if (fabs (a[i][i]) < eps) {cout << 0 << '\n'; return ;}  // 无穷解

        for (int j = 0; j < n; j++) if (i != j && fabs (a[i][j]) > eps) {  // 无穷解
            cout << 0 << '\n';
            return ;
        }

        ans[i] = (fabs (a[i][n]) < eps ? 0 : a[i][n]);
    }

    for (int i = 0; i < n; i++) cout << "x" << i + 1 << "=" << ans[i] << '\n';
}
