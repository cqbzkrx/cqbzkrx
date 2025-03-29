struct Node {
    int v, u; ll w;
    Node () : v (0), u (0), w (0) {}
    Node (int _v, int _u, ll _w) : v (_v), u (_u), w (_w) {}

    bool operator < (const Node &b) const {
        return w < b.w;
    }
};
vector e (0, Node ());
sort (all(e));

auto kruskal = [&](const vector <Node> &e, DSU dsu) -> ll {
    ll ans = 0;
    int s = n - 1;
    for (auto [v, u, w] : e) if (dsu.merge (v, u)) {
        ans += w, s--;
        if (s == 0) break;
    }

    return ans;
};
