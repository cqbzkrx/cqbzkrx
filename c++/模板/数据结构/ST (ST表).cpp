template <typename T>
class ST {
public:
    static constexpr int N = 2e5 + 7;
    T f[__lg(N) + 1][N];
    int n, lim;

    T merge (T a, T b) {
        return max (a, b);
    }

    void init (const vector <T> &a) {
        n = a.size(), lim = __lg(n) + 1;
        for (int i = 0; i < n; i++) f[0][i] = a[i];
        for (int i = 1; i < lim; i++) for (int j = 0; j < n; j++) {
            if (j + (1 << i) > n) break;
            f[i][j] = merge (f[i - 1][j], f[i - 1][j + (1 << (i - 1))]);
        }
    }

    ST () : n(0), lim(0) {}
    ST (const vector <T> &a) {init (a);}

    T qry (int l, int r) {
        int lg = __lg (r - l + 1);
        return merge (f[lg][l], f[lg][r - (1 << lg) + 1]);
    }
};

namespace ST {
    template <class T>
    struct Node {
        T maxn;
        Node (T _maxn = 0) : maxn (_maxn) {}
        Node operator + (const Node &rhs) const {
            Node ret;
            ret.maxn = max (rhs.maxn, maxn);
            return ret;
        }
    };

    template <class T, class info = Node <T>>
    class ST {
    public:
        static constexpr int N = 2e5 + 7;
        info f[__lg(N) + 1][N];
        int n, lim;

        void init (const vector <T> &a) {
            n = a.size(), lim = __lg(n) + 1;
            for (int i = 0; i < n; i++) f[0][i] = a[i];
            for (int i = 1; i < lim; i++) for (int j = 0; j < n; j++) {
                if (j + (1 << i) > n) break;
                f[i][j] = f[i - 1][j] + f[i - 1][j + (1 << (i - 1))];
            }
        }

        ST () : n(0), lim(0) {}
        ST (const vector <T> &a) {init (a);}

        T qry (int l, int r) {
            int lg = __lg (r - l + 1);
            return f[lg][l] + f[lg][r - (1 << lg) + 1];
        }
    };
}
