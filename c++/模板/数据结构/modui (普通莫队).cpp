struct Node {int l, r, id;}
vector <Node> s(q);

sort (all(s), [&](auto a, auto b){
    if (a.l / sq != b.l / sq) return a.l < b.l;
    // if (!(a.l / sq) & 1) return a.r > b.r;
    return a.r < b.r;
});

int cur = 0;
vector <int> ans(q);

auto add = [&](int p) {
    // 加点
};

auto del = [&](int p) {
    // 删点
};

int L = 1, R = 0;
for (int i = 0; i < q; i++) {
    while (L < s[i].l) del(L++);
    while (L > s[i].l) add(--L);
    while (R < s[i].r) add(++R);
    while (R > s[i].r) del(R--);
    ans[s[i].id] = cur;
}
