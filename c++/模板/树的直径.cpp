// 一、两边DFS
vector s(n + 1, 0ll);
auto dfs = [&](auto &&self, int v, int fa) -> void {
    for (auto &[u, w] : e[v]) if (u != fa) {
        s[u] = s[v] + w;
        self (self, u, v);
    }
};

dfs (dfs, 1, 0);
ll maxn = 0; int maxi = 0;
for (int i = 1; i <= n; i++) if (maxn < s[i])
    maxn = s[i], maxi = i;

maxn = 0;
fill (all(s), 0);

vector ans(0, 0), f(n + 1, 0);
auto dfs2 = [&](auto &&self, int v, int fa) -> void {
    ll maxn = 0; f[v] = fa;
    for (auto &[u, w] : e[v]) if (u != fa) {
        s[u] = s[v] + w;
        self (self, u, v);
    }
};

dfs2 (dfs2, maxi, 0);
int maxj = 0;
for (int i = 1; i <= n; i++) if (maxn < s[i])
    maxn = s[i], maxj = i;
cout << maxn << '\n';

int fa = maxj;  // 输出路径
while (fa != maxi) {
    ans.push_back (fa);
    fa = f[fa];
}
ans.push_back (maxi);
reverse(all(ans));
for (auto &v : ans) cout << v << ' ';

// 二、树形DP
vector dp(n + 1, pair(pair(0, 0ll), pair(0, 0ll)));
auto dfs2 = [&](auto &&self, int v, int fa) -> pair<int, ll> {
    pair<int, ll> maxfi = { v, 0ll }, maxse = { v, 0ll };
    for (auto &[u, w] : e[v])
        if (u != fa) {
            auto tmp = self(self, u, v);
            tmp.second += w;
            if (tmp.second > maxfi.second)
                swap(tmp, maxfi);
            if (tmp.second > maxse.second)
                swap(tmp, maxse);
        }

    dp[v] = make_pair(maxfi, maxse);
    return maxfi;
};

dfs2(dfs2, 1, 0);
ll maxi = 0, maxj = 0, maxn = 0;
for (int i = 1; i <= n; i++)
    if (maxn < dp[i].first.second + dp[i].second.second) {
        maxn = dp[i].first.second + dp[i].second.second;
        maxi = dp[i].first.first, maxj = dp[i].second.first;
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
