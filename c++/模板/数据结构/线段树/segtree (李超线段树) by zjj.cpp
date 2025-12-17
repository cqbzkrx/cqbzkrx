namespace sgt {
int n;

// y = (kz * x + b) / km
struct Line {
    ll km, kz, b;
    int id;

    Line() : km(1), kz(0), b(0), id(0) {}

    pair<ll, ll> get(int x) const {
        return {x * kz + b, km};
    }
};

struct Node {
    Line l;
    int tag;
} t[N << 2];

void build(int p = 1, int cl = 0, int cr = N) {
    if (cl == cr) {t[p].l.km = 1; return;}
    auto lc = p << 1, rc = lc | 1, mid = (cl + cr) >> 1;
    
}

// 1 => b, 0 => a
int cmp(const Line& a, const Line& b, int x) {
    auto [za, ma] = a.get(x);
    auto [zb, mb] = b.get(x);
    if (za * mb == zb * ma) return b.id < a.id;
    return za * mb < zb * ma;
}

void modify(int l, int r, const Line& L, int p = 1, int cl = 0, int cr = N) {
    if (l > cr || r < cl) return;

    auto lc = p << 1, rc = lc | 1, mid = (cl + cr) >> 1;

    if (l <= cl && cr <= r) {
        if (!t[p].tag) { t[p].l = L; t[p].tag = 1; return; }
        auto nL = L;
        if (cmp(t[p].l, nL, mid)) swap(nL, t[p].l);
        if (cmp(t[p].l, nL, cl)) modify(l, r, nL, lc, cl, mid);
        if (cmp(t[p].l, nL, cr)) modify(l, r, nL, rc, mid + 1, cr);
        return;
    }
    
    modify(l, r, L, lc, cl, mid); modify(l, r, L, rc, mid + 1, cr);
}

Line qry(int x, int p = 1, int cl = 0, int cr = N) {
    if (cl > x || cr < x) return Line();
    if (cl == cr) return t[p].l;

    auto lc = p << 1, rc = lc | 1, mid = (cl + cr) >> 1;
    Line sub;
    if (x <= mid) sub = qry(x, lc, cl, mid);
    else sub = qry(x, rc, mid + 1, cr);

    if (cmp(t[p].l, sub, x)) return sub;
    return t[p].l;
}

}
