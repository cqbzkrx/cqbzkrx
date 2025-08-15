auto toposort = [&]() -> bool {
    queue <int> q;
    for (int i = 1; i <= n; i++) if (!in[i])
        q.push(i);
    int cnt = 0;
    while (q.size() != 0) {
        cnt++;
        auto t = q.back(); q.pop();
        ans.push_back(t);
        for (auto &v : e[t]) if (--in[v] == 0)
            q.push(v);
    }
    return cnt == n;
};
