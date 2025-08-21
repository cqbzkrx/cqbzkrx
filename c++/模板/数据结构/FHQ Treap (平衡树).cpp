namespace FHQ_Treap {
    constexpr int MAXN = 3e5 + 7;
    mt19937 rd (time(0));

    template <class T>
    struct Node {
        int lc, rc;
        T val;
        int rnd, siz;
        Node (T x, int _siz = 1) : lc (0), rc (0), val (x), rnd (rd ()), siz (_siz) {}
        Node () : lc (0), rc (0), val (0), rnd (0), siz (0) {}
    };

    template <class T, class info = Node <T>>
    class treap {
    protected:
        void new_node (int &p, T val) {
            p = ++cnt;
            t.push_back (info (val));
        }

        void get (info &rt) {
            rt.siz = t[rt.lc].siz + t[rt.rc].siz + 1;
        }
        
        void split (int p, T val, int &l, int &r) {
            if (p == 0) {l = r = 0; return ;}
            else if (t[p].val <= val) {
                l = p;
                split (t[p].rc, val, t[l].rc, r);
                get (t[l]);
            }
            else {
                r = p;
                split (t[p].lc, val, l, t[r].lc);
                get (t[r]);
            }
        }

        int merge (int l, int r) {
            if (l == 0 || r == 0) return l + r;
            else if (t[l].rnd > t[r].rnd) {
                t[l].rc = merge (t[l].rc, r);
                get (t[l]);
                return l;
            }
            else {
                t[r].lc = merge (l, t[r].lc);
                get (t[r]);
                return r;
            }
        }

    public:
        vector <info> t;
        int rt, cnt;
        treap () : t (1, info (0, 0)), rt (0), cnt (0) {t.reserve (MAXN);}

        void insert (T val) {
            int x, y, z;
            split (rt, val, x, y);
            new_node (z, val);
            rt = merge (merge (x, z), y);
        }

        void erase_one (T val) {
            int x, y, z;
            split (rt, val, x, z);
            split (x, val - 1, x, y);
            y = merge (t[y].lc, t[y].rc);
            rt = merge (merge (x, y), z);
        }

        void erase_num (T val) {
            int x, y, z;
            split (rt, val, x, z);
            split (x, val - 1, x, y);
            rt = merge (x, z);
        }

        void erase_kth (int k) {
            T val = qry_kth (k);
            erase_one (val);
        }

        int qry_rank (T val) {
            int x, y;
            split (rt, val - 1, x, y);
            int ans = t[x].siz + 1;
            rt = merge (x, y);
            return ans;
        }

        T qry_kth (int p, int k) {
            auto siz = t[t[p].lc].siz;
            if (k == siz + 1) return t[p].val;
            if (k <= siz) return qry_kth (t[p].lc, k);
            return qry_kth (t[p].rc, k - (siz + 1));
        }

        T qry_kth (int k) {return qry_kth (rt, k);}

        T qry_lst (T val) {
            int x, y;
            split (rt, val - 1, x, y);
            T ans = qry_kth (x, t[x].siz);
            rt = merge (x, y);
            return ans;
        }

        T qry_nxt (T val) {
            int x, y;
            split (rt, val, x, y);
            T ans = qry_kth (y, 1);
            rt = merge (x, y);
            return ans;
        }
    };
}
