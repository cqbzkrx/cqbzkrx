class tarjan {
    public:

    static const int N = 5e4 + 7;
    vector <int> dfn, low, vis;
    vector <vector <int>> e, scc;
    deque <int> s;
    int num , id;

    void Tarjan(int x) {
        dfn[x] = low[x] = ++num;
        s.push_back(x); vis[x] = 1;
        for (auto &v : e[x]) {
            if (!dfn[v]) {
                Tarjan(v);
                low[x] = min(low[x], low[v]);
            }
            else if (vis[v]) low[x] = min(low[x], dfn[v]);
        }

        if (low[x] == dfn[x]) {
            bool f = 0; id++;
            while (s.back() != x) {
                scc[id].push_back(s.back());
                vis[s.back()] = 0;
                s.pop_back();
                f = 1;
            }
            if (f == 0) id--;
            scc[id].push_back(s.back());
            s.pop_back();
        }
    }

    tarjan () : e(vector (N, vector (0, 0))), dfn(vector (N, 0)), low(vector (N, 0)),
                scc(vector (N, vector (0, 0))), vis(vector (N, 0)), num(0) {}
};
