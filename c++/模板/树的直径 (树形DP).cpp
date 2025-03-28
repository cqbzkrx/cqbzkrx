vector dp(n + 1, pair(pair(0, 0ll), pair(0, 0ll)));
auto dfs2 = [&](auto &&self, int v, int fa) -> pair<int, ll> {
    pair<int, ll> maxfi = { v, 0ll }, maxse = { v, 0ll };
    for (auto &[u, w] : e[v])
        if (u != fa) {
            auto tmp = self(self, u, v);
            tmp.y += w;
            if (tmp.y > maxfi.y)
                swap(tmp, maxfi);
            if (tmp.y > maxse.y)
                swap(tmp, maxse);
        }

    dp[v] = make_pair(maxfi, maxse);
    return maxfi;
};

dfs2(dfs2, 1, 0);
ll maxi = 0, maxj = 0, maxn = 0;
for (int i = 1; i <= n; i++)
    if (maxn < dp[i].x.y + dp[i].y.y) {
        maxn = dp[i].x.y + dp[i].y.y;
        maxi = dp[i].x.x, maxj = dp[i].y.x;
    }
cout << maxn << '\n';

vector f(n + 1, 0);  // 输出路径
vector s(n + 1, 0ll);
auto dfs = [&](auto &&self, int v, int fa) -> void {
    f[v] = fa;
    for (auto &[u, w] : e[v])
        if (u != fa) {
            s[u] = s[v] + w;
            self(self, u, v);
        }
};

dfs(dfs, maxi, 0);
vector ans(0, 0);
auto v = maxj;
while (v != 0) {
    ans.push_back(v);
    v = f[v];
}
for (auto &v : ans) cout << v << ' ';
