namespace zkw_segment_tree {
    static constexpr ll INVALID = 0;

    template <class T>
    struct Node {
        T sum, lazy;
        Node (T _sum = 0, T _lazy = INVALID) : sum (_sum), lazy (_lazy) {}

        Node operator += (const Node &rhs) & {
            sum += rhs.sum;
            return *this;
        }

        Node operator + (const Node &rhs) const {
            Node lhs = *this;
            lhs += rhs;
            return lhs;
        }
    };

    template <class T, class info = Node <T>>
    class segtree {
    public:
        int n, m;
        vector <info> t;

        segtree (int _n = 0) {build (vector <T> (_n, 0));}
        segtree (const vector <T> &a) {build (a);}

        void build (const vector <T> &a) {
            n = a.size ();
            t.resize (n << 2);
            for (m = 1; m <= n; m <<= 1);

            for (int i = 1; i <= n; i++) t[i + m] = info (a[i - 1]);
            for (int p = m - 1; p >= 1; p--) {
                auto lc = p << 1, rc = lc | 1;
                t[p] = t[lc] + t[rc];
            }
        }

        void modify (int l, int r, T v) {
            l++, r++;
            int lc = 0, rc = 0, len = 1;
            for (l += m - 1, r += m + 1; l ^ r ^ 1; l >>= 1, r >>= 1, len <<= 1) {
                if (l & 1 ^ 1) t[l ^ 1].lazy += v, lc += len;
                if (r & 1) t[r ^ 1].lazy += v, rc += len;
                t[l >> 1].sum += v * lc, t[r >> 1].sum += v * rc;
            }
            for (lc += rc; l > 1; l >>= 1) t[l >> 1].sum += v * lc;
        }

        info qry (int l, int r) {
            l++, r++;
            info ans;
            int lc = 0, rc = 0, len = 1;
            for (l += m - 1, r += m + 1; l ^ r ^ 1; l >>= 1, r >>= 1, len <<= 1) {
                if (l & 1 ^ 1) ans += info (t[l ^ 1].sum + t[l ^ 1].lazy * len), lc += len;
                if (r & 1) ans += info (t[r ^ 1].sum + t[r ^ 1].lazy * len), rc += len;
                ans += info (t[l >> 1].lazy * lc + t[r >> 1].lazy * rc);
            }
            for (lc += rc, l >>= 1; l; l >>= 1) ans += info (t[l].lazy * lc);
            return ans;
        }

        void modify (int l, T v) {modify (l, l, v);}
        info qry (int l) {return qry (l, l);}
    };
}
