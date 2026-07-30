// https://codeforces.com/contest/1476/problem/G
// https://codeforces.com/contest/1476/submission/384854144

int B, B2;

void solve () {
    int n, m; cin >> n >> m;
    vector a (n, 0);
    for (auto &v : a) cin >> v;

    B = max <int> (1, pow (n, 2.0 / 3));

    struct Node {
        int l, r, k, tim, id;
        Node () : l (0), r (0), k (0), tim (0), id (0) {}
        Node (int v, int u, int w, int time, int idx) : l (v), r (u), k (w), tim (time), id (idx) {}
        bool operator < (const Node &rhs) const {
            if (l / B != rhs.l / B) return l / B < rhs.l / B;
            if (r / B != rhs.r / B) return (l / B & 1) ? r / B < rhs.r / B : r / B > rhs.r / B;
            return ((l / B & 1) ^ (r / B & 1)) ? tim < rhs.tim : tim > rhs.tim;
        }
    };

    struct Node2 {
        int p, x, tim, lst;
        Node2 () : p (0), x (0), tim (0), lst (0) {}
        Node2 (int v, int u, int time, int last) : p (v), x (u), tim (time), lst (last) {}
    };

    vector <Node> q (0, Node ());
    vector <Node2> q2 (1, Node2 ());
    int tim = 0, qcnt = 0;
    for (int i = 0; i < m; i++) {
        int op; cin >> op;
        if (op == 1) {
            int l, r, k; cin >> l >> r >> k; l--, r--;
            q.emplace_back (l, r, k, tim, qcnt++);
        }
        else {
            int p, x; cin >> p >> x; p--;
            q2.emplace_back (p, x, ++tim, a[p]), a[p] = x;
        }
    }

    sort (all(q));

    B2 = max <int> (1, pow (n, 1.0 / 3));
    vector cnt (N, 0), cnt2 (n + 1, 0), c (n + 1, 0);

    auto qry = [&](int k) -> int {
        if (k == 0) return 0;
        vector t (0, pair (0, 0));
        for (int i = 0; i <= n / B2; i++) if (c[i])
            for (int j = B2 * i; j <= min (n, B2 * (i + 1) - 1); j++) if (cnt2[j])
                t.emplace_back (cnt2[j], j);

        int ans = inf;
        ll sum = 0;
        for (int p1 = 0, p2 = 0; p2 < t.size (); p2++) {
            sum += t[p2].x;
            while (p1 < p2 && sum - t[p1].x >= k) sum -= t[p1].x, p1++;
            if (sum >= k) cmin (ans, t[p2].y - t[p1].y);
        }

        return ans == inf ? -1 : ans;
    };

    auto add = [&](int p) -> void {
        if (cnt[a[p]]) cnt2[cnt[a[p]]]--, c[cnt[a[p]] / B2]--;
        cnt[a[p]]++;
        cnt2[cnt[a[p]]]++, c[cnt[a[p]] / B2]++;
    };

    auto del = [&](int p) -> void {
        cnt2[cnt[a[p]]]--, c[cnt[a[p]] / B2]--;
        cnt[a[p]]--;
        if (cnt[a[p]]) cnt2[cnt[a[p]]]++, c[cnt[a[p]] / B2]++;
    };

    int L = 1, R = 0;
    vector ans (qcnt, 0);
    for (int i = 0; i < qcnt; i++) {
        while (L > q[i].l) add (--L);
        while (R < q[i].r) add (++R);
        while (L < q[i].l) del (L++);
        while (R > q[i].r) del (R--);
        while (tim < q[i].tim) {
            tim++;
            if (q2[tim].p >= L && q2[tim].p <= R) del (q2[tim].p);
            a[q2[tim].p] = q2[tim].x;
            if (q2[tim].p >= L && q2[tim].p <= R) add (q2[tim].p);
        }
        while (tim > q[i].tim) {
            if (q2[tim].p >= L && q2[tim].p <= R) del (q2[tim].p);
            a[q2[tim].p] = q2[tim].lst;
            if (q2[tim].p >= L && q2[tim].p <= R) add (q2[tim].p);
            tim--;
        }

        ans[q[i].id] = qry (q[i].k);
    }

    for (auto v : ans) cout << v << '\n';
}
