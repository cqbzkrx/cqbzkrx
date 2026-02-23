// https://www.luogu.com.cn/problem/P2619
// https://www.luogu.com.cn/record/263587041

const int M = 100 + 7;

void solve () {
    int n, m, k; cin >> n >> m >> k;
    vector e (0, tuple (0, 0, 0)), e2 (0, tuple (0, 0, 0));
    for (int i = 0; i < m; i++) {
        int x, y, z, w; cin >> x >> y >> z >> w;
        if (!w) e.emplace_back (x, y, z);
        else e2.emplace_back (x, y, z);
    }

    sort (all(e), [&](auto &lhs, auto &rhs) {return get <2> (lhs) < get <2> (rhs);});
    sort (all(e2), [&](auto &lhs, auto &rhs) {return get <2> (lhs) < get <2> (rhs);});

    int len = e.size (), len2 = e2.size ();
    auto check = [&](int mid) -> pair <int, bool> {
        int sum = 0, cnt = 0, p1 = 0, p2 = 0;
        DSU dsu (n);
        for (p1 = 0, p2 = 0; p1 < len && p2 < len2; ) {
            auto [x, y, z] = e[p1];
            auto [x2, y2, z2] = e2[p2];
            if (z + mid <= z2) {
                p1++;
                if (!dsu.merge (x, y)) continue;
                cnt++; sum += z + mid;
            }
            else {
                p2++;
                if (!dsu.merge (x2, y2)) continue;
                sum += z2;
            }
        }

        while (p1 < len) {
            auto [x, y, z] = e[p1]; p1++;
            if (!dsu.merge (x, y)) continue;
            cnt++; sum += z + mid;
        }

        while (p2 < len2) {
            auto [x2, y2, z2] = e2[p2]; p2++;
            if (!dsu.merge (x2, y2)) continue;
            sum += z2;
        }

        return {sum - k * mid, cnt >= k};
    };

    int l = -M, r = M, ans = 0;
    while (l <= r) {
        int mid = (l + r) >> 1;
        auto [res, flag] = check (mid);
        if (flag) l = mid + 1, ans = res;
        else r = mid - 1;
    }

    cout << ans << '\n';
}
