vector siz(n + 1, 0), ans(0, 0);
int minn = inf;
auto dfs = [&](auto &&self, int v, int fa) -> int {
    siz[v] = 1;
    int maxn = 0;
    for (auto &u : e[v]) if (u != fa) {
        auto w = self (self, u, v);
        maxn = max(maxn, w);
        siz[v] += w;
    }

    int s = max(n - siz[v], maxn);
    if (s < minn) ans.clear(), ans.push_back(v), minn = s;
    else if (s == minn) ans.push_back(v);

    return siz[v];
};

dfs (dfs, 1, 0);

cout << ans.size() << '\n'; //个数
sort(all(ans));
for (auto &v : ans) cout << v << '\n';
