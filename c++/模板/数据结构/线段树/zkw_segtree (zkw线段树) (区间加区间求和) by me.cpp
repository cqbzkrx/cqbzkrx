namespace zkw_sgt {
    template <typename T>
    struct Node {
        T sum, add;
        Node () : sum (0), add (0) {}
        Node (T x, T _add = 0) : sum (x), add (_add) {}
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
            for (int p = m - 1; p >= 0; p--) t[p].sum = t[p << 1].sum + t[p << 1 | 1].sum;
        }

        void modify (int p, T x) {
            p = p + m + 1;
            for (; p > 1; p >>= 1) t[p].sum += x;
        }

        void modify (int l, int r, T x) {
            T lc = 0, rc = 0, len = 1;
            l = l + m, r = r + m + 2;
            for (; l ^ r ^ 1; l >>= 1, r >>= 1, len <<= 1) {
                if (l & 1 ^ 1) t[l ^ 1].add += x, lc += len;
                if (r & 1) t[r ^ 1].add += x, rc += len;
                t[l >> 1].sum += x * lc;
                t[r >> 1].sum += x * rc;
            }

            lc += rc;
            for (; l > 1; l >>= 1) t[l >> 1].sum += x * lc;
        }

        T qry (int p) {return qry (p, p);}
        T qry (int l, int r) {
            T ans = 0, lc = 0, rc = 0, len = 1;
            l = l + m, r = r + m + 2;
            for (; l ^ r ^ 1; l >>= 1, r >>= 1, len <<= 1) {
                if (l & 1 ^ 1) ans += t[l ^ 1].sum + len * t[l ^ 1].add, lc += len;
                if (r & 1) ans += t[r ^ 1].sum + len * t[r ^ 1].add, rc += len;
                ans += t[l >> 1].add * lc;
                ans += t[r >> 1].add * rc;
            }

            lc += rc;
            for (; l > 1; l >>= 1) ans += t[l >> 1].add * lc;
            return ans;
        }
    };
}
