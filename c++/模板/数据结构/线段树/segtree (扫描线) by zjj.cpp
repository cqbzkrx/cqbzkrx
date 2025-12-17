namespace sgt {
constexpr int maxn = 2e5 + 100;

int n;

vector pool(0, 0);

struct Node {
    // cnt => lazy_tag
    // len => 当前节点对应区间非0元素的个数
    int cnt, len;
} t[maxn << 2];

void merge(Node& rt, Node& a, Node& b, int cl, int cr) {
    // 该点cnt为0，则根据子节点而定
    if (!rt.cnt) rt.len = a.len + b.len;
    // cnt不为0，则全部都是非0元素
    // 线段树上某个点cl，代表实际上线段区间 [pool[cl], pool[cl + 1])
    else rt.len = pool[cr + 1] - pool[cl];
}

// 没啥好说的
void modify(int l, int r, int x, int p = 1, int cl = 0, int cr = n - 1) {
    if (l > cr || r < cl) return;
    if (cl == cr) {
        t[p].cnt += x; t[p].len = (t[p].cnt != 0) * (pool[cr + 1] - pool[cl]);
        return;
    }
    auto lc = p << 1, rc = lc | 1, mid = (cl + cr) >> 1;
    if (cl >= l && cr <= r) {
        t[p].cnt += x;
        merge(t[p], t[lc], t[rc], cl, cr);
        return;
    }

    modify(l, r, x, lc, cl, mid); modify(l, r, x, rc, mid + 1, cr);
    merge(t[p], t[lc], t[rc], cl, cr);
}

int get() {
    return t[1].len;
}

}

void solve() {
    int n; cin >> n;

    // y坐标，x起点，x终点，类型（上边 or 下边）
    vector sg(0, tuple(0, 0, 0, 0));
    // 事先丢个inf进去
    vector pool(1, inf);

    for (int i = 0; i < n; i++) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        pool.push_back(x1); pool.push_back(x2);

        // 下边权值为1，因为是区间 +1
        sg.emplace_back(y1, x1, x2, 1);
        // 上边权值为-1，因为是区间 -1
        sg.emplace_back(y2, x1, x2, -1);
    }

    sort(all(pool)); pool.erase(unique(all(pool)), pool.end());
    sort(all(sg));

    for (auto& [y, bg, ed, v]: sg) {
        bg = lower_bound(all(pool), bg) - pool.begin();
        ed = lower_bound(all(pool), ed) - pool.begin();
    }

    sgt::n = pool.size();
    // O(1)转移pool里面的元素到sgt::pool, pool需要重新初始化才能使用
    sgt::pool = move(pool);

    ll lst = 0, ans = 0;
    for (auto& [y, bg, ed, v]: sg) {
        // 从上次的 y 到现在，小矩形的长都是L
        auto L = sgt::get();
        // Δy = y - lst
        ans += (y - lst) * L;
        // 添加变化
        sgt::modify(bg, ed - 1, v);
        lst = y;
    }

    cout << ans << endl;
}
