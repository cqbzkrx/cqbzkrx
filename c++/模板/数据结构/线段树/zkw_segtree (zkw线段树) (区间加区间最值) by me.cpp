namespace zkw_sgt {
    template <typename T>
    struct Node {
        T minn;
        Node () : minn (0) {}
        Node (T x) : minn (x) {}
    };

    template <typename T, class info = Node <T>>
    class segtree {
    public:
        vector <info> t;
        int n, m;
        
        segtree () {}
        segtree (int n, T x = 0) {init (vector <T> (n, x));}
        segtree (const vector <T> &a) {init (a);}

        void init (const vector <T> &a) {
            n = a.size ();
            for (m = 1; m <= n + 1; m <<= 1);
            t.resize ((m << 1) + 1);
            for (int i = 0; i < n; i++) t[i + m + 1] = info (a[i]);
            for (int p = m - 1; p >= 0; p--) {
                t[p].minn = max (t[p << 1].minn, t[p << 1 | 1].minn);
                t[p << 1].minn -= t[p].minn, t[p << 1 | 1].minn -= t[p].minn;
            }
        }

        void add (int p, T x) {
            p = p + m + 1;
            t[p].minn += x;
            for (; p > 1; p >>= 1) {
                auto A = min (t[p].minn, t[p ^ 1].minn);
                t[p].minn -= A, t[p ^ 1].minn -= A, t[p >> 1].minn += A;
            }
        }

        void add (int l, int r, T x) {
            l = l + m, r = r + m + 2;
            for (; l ^ r ^ 1; l >>= 1, r >>= 1) {
                if (l & 1 ^ 1) t[l ^ 1].minn += x;
                if (r & 1) t[r ^ 1].minn += x;
                
                auto A = min (t[l].minn, t[l ^ 1].minn);
                t[l].minn -= A, t[l ^ 1].minn -= A, t[l >> 1].minn += A;

                A = min (t[r].minn, t[r ^ 1].minn);
                t[r].minn -= A, t[r ^ 1].minn -= A, t[r >> 1].minn += A;
            }

            for (; l > 1; l >>= 1) {
                auto A = min (t[l].minn, t[l ^ 1].minn);
                t[l].minn -= A, t[l ^ 1].minn -= A, t[l >> 1].minn += A;
            }
        }

        T qry_node (int p) {
            T ans = 0;
            p = p + m + 1;
            for (; p; p >>= 1) ans += t[p].minn;
            return ans;
        }

        T qry (int l, int r) {
            if (l == r) return qry_node (l);
            T L = 0, R = 0;
            l = l + m + 1, r = r + m + 1;
            for (; l ^ r ^ 1; l >>= 1, r >>= 1) {
                L += t[l].minn, R += t[r].minn;
                if (l & 1 ^ 1) cmin (L, t[l ^ 1].minn);
                if (r & 1) cmin (R, t[r ^ 1].minn);
            }

            L += t[l].minn, R += t[r].minn;
            T ans = min (L, R);
            for (; l > 1; l >>= 1) ans += t[l >> 1].minn;
            return ans;
        }
    };
}
