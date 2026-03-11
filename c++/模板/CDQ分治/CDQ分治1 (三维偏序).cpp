// https://www.luogu.com.cn/problem/P3810
// https://www.luogu.com.cn/record/265152141

template <typename T = ll>
class BIT {
public:
    int lowbit (int i) {return (i & -i);}

    vector <T> t;
    
    BIT (int sz = 0) : t (sz + 10) {}
    BIT (const vector <T> &a) : BIT ((int) a.size ()) {
        for (int i = 0; i < a.size (); i++) modify (i, a[i]);
    }

    void modify (int x, T v) {
        x++;
        while (x < t.size ()) {
            t[x] += v;
            x += lowbit(x);
        }
    }

    T qry (int x) {
        x++;
        T ans = 0;
        while (x > 0) {
            ans += t[x];
            x -= lowbit(x);
        }
        return ans + t[0];
    }
    
    T qry (int l, int r) {
        return qry (r) - qry (l - 1);
    }
};

void solve () {
    int n, k; cin >> n >> k;
    vector a (n, tuple (0, 0, 0, 0));
    map <tuple <int, int, int>, int> mp;
    
    vector ans (n, 0);
    for (int i = n - 1; i >= 0; i--) {
        auto &[v, u, w, id] = a[i];
        cin >> v >> u >> w;
        id = i;
        ans[i] += mp[{v, u, w}]++;
    }

    sort (all(a), [&](auto &lhs, auto &rhs) {
        auto [v, u, w, id] = lhs;
        auto [v2, u2, w2, id2] = rhs;
        if (v != v2) return v < v2;
        if (u != u2) return u < u2;
        if (w != w2) return w < w2;
        return id < id2;
    });

    BIT <int> bit (k + 1);
    auto cdq = [&](auto &&self, int l, int r) -> void {
        if (l >= r) return ;
        int mid = (l + r) >> 1;

        self (self, l, mid);
        self (self, mid + 1, r);

        int p1 = l, p2 = mid + 1;
        vector s (0, tuple (0, 0, 0, 0)); s.reserve (r - l + 1);
        while (p1 <= mid && p2 <= r) {
            if (get <1> (a[p1]) <= get <1> (a[p2])) {
                s.push_back (a[p1]);
                bit.modify (get <2> (a[p1]), 1);
                p1++;
            }
            else {
                s.push_back (a[p2]);
                ans[get <3> (a[p2])] += bit.qry (1, get <2> (a[p2]));
                p2++;
            }
        }

        while (p1 <= mid) {
            s.push_back (a[p1]);
            bit.modify (get <2> (a[p1]), 1);
            p1++;
        }

        while (p2 <= r) {
            s.push_back (a[p2]);
            ans[get <3> (a[p2])] += bit.qry (1, get <2> (a[p2]));
            p2++;
        }

        for (int i = l; i <= mid; i++) bit.modify (get <2> (a[i]), -1);
        for (int i = l; i <= r; i++) a[i] = s[i - l];
    };

    cdq (cdq, 0, n - 1);

    vector res (n, 0);
    for (int i = 0; i < n; i++) res[ans[i]]++;

    for (int i = 0; i < n; i++) cout << res[i] << '\n';
}
