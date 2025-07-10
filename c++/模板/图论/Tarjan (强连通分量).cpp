vector dfn (n + 1, 0), low (n + 1, 0), vis (n + 1, 0), s (0, 0);
vector scc (n + 1, vector (0, 0));
int num = 0, id = 0;

auto tarjan = [&](auto &&self, int x) -> void {
    dfn[x] = low[x] = ++num;
    s.push_back (x); vis[x] = 1;
    for (auto &v : e[x]) {
        if (!dfn[v]) self, (self, v), low[x] = min (low[x], low[v]);
        else if (vis[v]) low[x] = min (low[x], dfn[v]);
    }

    if (low[x] == dfn[x]) {
        bool f = 0; id++;
        while (s.back () != x) {
            scc[id].push_back(s.back());
            vis[s.back ()] = 0;
            s.pop_back ();
            f = 1;
        }
        if (f == 0) id--;
        scc[id].push_back (s.back ());
        s.pop_back ();
    }
};
