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
