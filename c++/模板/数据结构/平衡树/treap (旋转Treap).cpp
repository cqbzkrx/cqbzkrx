namespace BST {
    static constexpr int MAXN = 3e5 + 7;
    mt19937 rd (time (0));
    
    template <typename T>
    struct Node {
        T val;
        int lc, rc, siz, rnd;
        Node () : val (0), lc (0), rc (0), siz (0), rnd (0) {}
        Node (T x, int _siz = 1, int _lc = 0, int _rc = 0) : val (x), lc (_lc), rc (_rc), siz (_siz), rnd (rd ()) {}
    };

    template <typename T, class info = Node <T>>
    class treap {
        vector <info> t;
        int rt, num;

        int new_node (T x) {
            t.emplace_back (x);
            return ++num;
        }

        void get (int p) {
            t[p].siz = t[t[p].lc].siz + t[t[p].rc].siz + 1;
        }

        void rotate (int &p, int d) {
            int k;
            if (d == 1) {   // left
                k = t[p].rc;
                t[p].rc = t[k].lc;
                t[k].lc = p;
            }
            else {   // right
                k = t[p].lc;
                t[p].lc = t[k].rc;
                t[k].rc = p;
            }
            t[k].siz = t[p].siz;
            get (p);
            p = k;
        }

    public:
        treap (int n) {init (n);}
        treap () {init (MAXN);}
        void init (int n) {
            rt = 0, num = 0;
            t.reserve (n + 10);
            t.emplace_back ();
        }

        void insert (T val) {insert (rt, val);}
        void insert (int &p, T val) {
            if (p == 0) {p = new_node (val); return ;}
            t[p].siz++;
            if (val >= t[p].val) insert (t[p].rc, val);
            else insert (t[p].lc, val);
            if (t[p].lc && t[p].rnd > t[t[p].lc].rnd) rotate (p, 0);
            if (t[p].rc && t[p].rnd > t[t[p].rc].rnd) rotate (p, 1);
            get (p);
        }

        void erase_node (T val) {erase_node (rt, val);}
        void erase_node (int &p, T val) {
            t[p].siz--;
            if (t[p].val == val) {
                if (t[p].lc == 0 && t[p].rc == 0) {p = 0; return ;}
                if (t[p].lc == 0 || t[p].rc == 0) {p = t[p].lc + t[p].rc; return ;}
                if (t[t[p].rc].rnd > t[t[p].lc].rnd) {
                    rotate (p, 0);
                    erase_node (t[p].rc, val);
                    return ;
                }
                else {
                    rotate (p, 1);
                    erase_node (t[p].lc, val);
                    return ;
                }
            }
            if (val > t[p].val) erase_node (t[p].rc, val);
            else erase_node (t[p].lc, val);
            get (p);
        }

        int qry_rank (T x) {return qry_rank (rt, x) + 1;}
        int qry_rank (int p, T x) {
            if (!p) return 0;
            if (x > t[p].val) return t[t[p].lc].siz + 1 + qry_rank (t[p].rc, x);
            else return qry_rank (t[p].lc, x);
        }

        T qry_kth (int k) {return qry_kth (rt, k);}
        T qry_kth (int p, int k) {
            if (!p) return 0;
            if (t[t[p].lc].siz + 1 == k) return t[p].val;
            if (t[t[p].lc].siz >= k) return qry_kth (t[p].lc, k);
            else return qry_kth (t[p].rc, k - t[t[p].lc].siz - 1);
        }

        int size () {return t[rt].siz;}
    };
}
