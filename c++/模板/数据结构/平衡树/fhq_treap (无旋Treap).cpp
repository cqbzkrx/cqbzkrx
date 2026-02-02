namespace BST {
    static constexpr int MAXN = 1e5 + 7;
    mt19937 rd (time (0));
    
    template <typename T>
    struct Node {
        T val;
        int lc, rc, siz, rnd;
        Node () : val (0), lc (0), rc (0), siz (0), rnd (0) {}
        Node (T x, int _siz = 1, int _lc = 0, int _rc = 0) : val (x), lc (_lc), rc (_rc), siz (_siz), rnd (rd ()) {}
    };

    template <typename T, class info = Node <T>>
    class fhq_treap {
        vector <info> t;
        int rt, num;
        
        int new_node (T x) {
            t.emplace_back (x);
            return ++num;
        }

        void get (int p) {
            t[p].siz = t[t[p].lc].siz + t[t[p].rc].siz + 1;
        }

        void split (int p, T val, int &l, int &r) {
            if (p == 0) {l = r = 0; return ;}
            if (t[p].val <= val) {
                l = p;
                split (t[p].rc, val, t[p].rc, r);
            }
            else {
                r = p;
                split (t[p].lc, val, l, t[p].lc);
            }
            get (p);
        }

        int merge (int l, int r) {
            if (l == 0 || r == 0) return l + r;
            if (t[l].rnd > t[r].rnd) {
                t[l].rc = merge (t[l].rc, r);
                get (l);
                return l;
            }
            else {
                t[r].lc = merge (l, t[r].lc);
                get (r);
                return r;
            }
        }

    public:
        fhq_treap (int n) {init (n);}
        fhq_treap () {init (MAXN);}
        void init (int n) {
            rt = 0, num = 0;
            t.reserve (n + 10);
            t.emplace_back ();
        }

        void insert (T val) {
            int x, y, z;
            split (rt, val, x, y);
            z = new_node (val);
            rt = merge (merge (x, z), y);
        }

        void erase_node (T val) {
            int x, y, z;
            split (rt, val, x, z);
            split (x, val - 1, x, y);
            rt = merge (merge (x, merge (t[y].lc, t[y].rc)), z);
        }

        void erase (T val) {
            int x, y, z;
            split (rt, val, x, z);
            split (x, val - 1, x, y);
            rt = merge (x, z);
        }

        void erase_kth (int k) {
            erase_node (qry_kth (k));
        }

        int qry_rank (T val) {
            int x, y;
            split (rt, val - 1, x, y);
            int ans = t[x].siz + 1;
            rt = merge (x, y);
            return ans;
        }

        T qry_kth (int k) {return qry_kth (rt, k);}
        T qry_kth (int p, int k) {
            if (k == t[t[p].lc].siz + 1) return t[p].val;
            if (k <= t[t[p].lc].siz) return qry_kth (t[p].lc, k);
            else return qry_kth (t[p].rc, k - t[t[p].lc].siz - 1);
        }

        int size () {return t[rt].siz;}
    };
}
