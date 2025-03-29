struct Node {int v, u; ll w; Node () : v (0), u (0), w (0) {}};

auto kruskal = [&](const vector <Node> &e, DSU dsu) -> ll {
    ll ans = 0;
    int s = n - 1;
    for (auto [v, u, w] : e) if (merge (v, u)) {
        ans += w, s--;
        if (s == 0) break;
    }

    return ans;
};
