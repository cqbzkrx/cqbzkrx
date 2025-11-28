namespace ST {
    const ll INVALID = -INF;

    template <typename T>
    struct Node {
        T val;
        Node () : val (INVALID) {}
        Node (T x) : val (x) {}
        Node operator + (const Node &rhs) const {
            Node ret;
            ret.val = max (val, rhs.val);
            return ret;
        }
    };

    template <typename T, class info = Node <T>>
    class ST {
    public:
        vector <vector <info>> f;
        ST () {}
        ST (const vector <T> &a) {init (a);}
        void init (const vector <T> &a) {
            int n = a.size (), lim = __lg (n) + 1;
            f.assign (lim, vector <info> (n, info ()));
            for (int i = 0; i < n; i++) f[0][i] = info (a[i]);
            for (int i = 1; i < lim; i++) for (int j = 0; j < n; j++) {
                if (j + (1 << i) > n) break;
                f[i][j] = f[i - 1][j] + f[i - 1][j + (1 << (i - 1))];
            }
        }

        info qry (int l, int r) {
            int lg = __lg (r - l + 1);
            return f[lg][l] + f[lg][r - (1 << lg) + 1];
        }
    };
}
