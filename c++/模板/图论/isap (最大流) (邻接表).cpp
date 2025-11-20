namespace isap {
    vector <vector <ll>> e;
    vector <int> dis, gap;
    int n, s, t;

    ll dfs (int u, ll flow) {
        ll sum = 0; int minn = n - 1;
        if (u == t) return flow;
        for (int v = 1; v <= n; v++) if (e[u][v] > 0) {
            if (dis[u] == dis[v] + 1) {
                auto res = dfs (v, min (flow - sum, e[u][v]));
                e[u][v] -= res;
                e[v][u] += res;
                sum += res;
                if (dis[s] >= n) return sum;
                if (sum == flow) break;
            }
            cmin (minn, dis[v]);
        }

        if (sum == 0) {
            gap[dis[u]]--;
            if (gap[dis[u]] == 0) dis[s] = n;
            dis[u] = minn + 1;
            gap[dis[u]]++;
        }
        return sum;
    }

    ll isap () {
        dis.assign (n + 1, 0);
        gap.assign (n + 1, 0); gap[0] = n;
        ll ans = 0;
        while (dis[s] < n) ans += dfs (s, inf);
        return ans;
    }
}
