struct lb {
    static constexpr int M = 63;
    array <ll, M> p;
    lb () {fill (all(p), 0ll);}

    ll & operator [] (int i) {return p[i];}
    const ll operator [] (int i) const {return p[i];}

    void insert (ll x) {
        for (int i = M - 1; i >= 0; i--) if (x & (1ll << i)) {
            if (p[i] == 0) {p[i] = x; break;}
            else x ^= p[i];
        }
    }

    lb operator += (const lb &rhs) & {
        for (int i = 0; i < M; i++) insert (rhs[i]);
        return *this;
    }

    friend lb operator + (lb lhs, const lb &rhs) {
        lhs += rhs;
        return lhs;
    }
};
