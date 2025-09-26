namespace ST {
    static constexpr ll INVALID = INF;

    template <class T>
    struct Node {
        T ans;
        Node () : ans (-INVALID) {}
        Node (T v) : ans (v) {}
        Node operator + (const Node &rhs) const {
            Node ret;
            ret.ans = max (rhs.ans, ans);   // max
            return ret;
        }
    };

    template <class T, class info = Node <T>>
    class ST {
    public:
        static constexpr int N = 2e5 + 7;
        vector <vector <info>> f;
        int n, lim;

        void init (const vector <T> &a) {
            n = a.size(), lim = __lg(n) + 1;
            for (int i = 0; i < n; i++) f[0][i] = info (a[i]);
            for (int i = 1; i < lim; i++) for (int j = 0; j < n; j++) {
                if (j + (1 << i) > n) break;
                f[i][j] = f[i - 1][j] + f[i - 1][j + (1 << (i - 1))];
            }
        }

        ST () : n(0), lim(0) {clear ();}
        ST (const vector <T> &a) {clear (); init (a);}

        info qry (int l, int r) {
            int lg = __lg (r - l + 1);
            return f[lg][l] + f[lg][r - (1 << lg) + 1];
        }

        void clear () {
            f = vector <vector <info>> (__lg (N) + 1, vector <info> (N));
        }
    };
}
