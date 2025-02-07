vector s(n + 1, 0ll);
vector f(n + 1, 0);
auto dfs = [&](auto &&self, int v, int fa) -> void {
    f[v] = fa;
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
fill (all(s), 0ll);
fill (all(f), 0);

vector ans(0, 0);
dfs (dfs, maxi, 0);

int maxj = 0;
for (int i = 1; i <= n; i++) if (maxn < s[i])
    maxn = s[i], maxj = i;

int fa = maxj;
while (fa != maxi) {
    ans.push_back (fa);
    fa = f[fa];
}
ans.push_back (maxi);

ll minans = INF;
for (auto &v : ans) minans = min(minans, max(s[v] - s[maxi], s[maxj] - s[v]));

cout << minans << '\n';
