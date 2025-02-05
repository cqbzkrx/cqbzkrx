template <typename T>
class st {
    protected:

    static constexpr int N = 1e5 + 7;
    T f[__lg(N) + 1][N];
    int n, lim;

    public:

    void init (const vector <T> &a) {
        n = a.size(), lim = __lg(n) + 1;
        for (int i = 0; i < n; i++) f[0][i] = a[i];
        for (int i = 1; i < lim; i++) for (int j = 0; j < n; j++) {
            if (j + (1 << i) > n) break;
            f[i][j] = max (f[i - 1][j], f[i - 1][j + (1 << (i - 1))]);
        }
    }

    st () : n(0), lim(0) {}
    st (const vector <T> &a) {init (a);}

    T qry (int l, int r) {
        int lg = __lg (r - l + 1);
        return max(f[lg][l], f[lg][r - (1 << lg) + 1]);
    }
};
