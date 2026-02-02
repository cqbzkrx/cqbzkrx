namespace BST {
    static constexpr int MAXN = 3e5 + 7;
    static constexpr db alpha = 0.75;

    template <typename T>
    struct Node {
        T val;
        int lc, rc, tot, siz, del;
        Node () : val (0), lc (0), rc (0), tot (1), siz (0), del (0) {}
        Node (T x) : val (x), lc (0), rc (0), tot (1), siz (1), del (1) {}
        void clear () {
            lc = rc = 0;
            tot = siz = del = 1;
        }
    };

    template <typename T, class info = Node <T>>
    class BST {
        vector <info> t;
        vector <int> q, s;
        int rt, num;
        
        int new_node (T x) {
            if (s.size ()) {
                auto p = s.back (); s.pop_back ();
                t[p] = info (x);
                return p;
            }
            else {
                t.emplace_back (x);
                return ++num;
            }
        }

        void merge (int p) {
            t[p].siz = t[t[p].lc].siz + t[t[p].rc].siz + t[p].del;
            t[p].tot = t[t[p].lc].tot + t[t[p].rc].tot + 1;
        }

        bool check (int p) {
            return (db) t[p].siz * alpha <= (db) max <db> (t[t[p].lc].siz, t[t[p].rc].siz);
        }

        void rebuild (int &p) {
            auto inorder = [&](auto &&self, int p) -> void {
                if (!p) return ;
                self (self, t[p].lc);
                if (t[p].del) q.push_back (p);
                else s.push_back (p);
                self (self, t[p].rc);
            };

            auto build = [&](auto &&self, int &p, int cl, int cr) -> void {
                auto mid = (cl + cr) >> 1;
                p = q[mid];
                if (cl == cr) {t[p].clear (); return ;}
                if (cl < mid) self (self, t[p].lc, cl, mid - 1);
                else if (cl == mid) t[p].lc = 0;
                self (self, t[p].rc, mid + 1, cr);
                merge (p);
            };

            inorder (inorder, p);
            if (q.size ()) build (build, p, 0, q.size () - 1);
            else p = 0;
            q.clear ();
        }
        
    public:
        BST () {init (MAXN);}
        BST (int n) {init (n);}
        void init (int n) {
            s.reserve (n + 10);
            q.reserve (n + 10);
            t.reserve (n + 10);
            t.emplace_back (); num = 0;
            rt = 0;
        }

        void insert (T x) {insert (rt, x);}
        void insert (int &p, T x) {
            if (!p) {p = new_node (x); return ;}
            t[p].siz++, t[p].tot++;
            if (t[p].val >= x) insert (t[p].lc, x);
            else insert (t[p].rc, x);
            if (check (p)) rebuild (p);
        }

        int qry_rank (T x) {return qry_rank (rt, x) + 1;}
        int qry_rank (int p, T x) {
            if (!p) return 0;
            if (x > t[p].val) return t[t[p].lc].siz + t[p].del + qry_rank (t[p].rc, x);
            else return qry_rank (t[p].lc, x);
        }

        T qry_kth (int k) {return qry_kth (rt, k);}
        T qry_kth (int p, int k) {
            if (!p) return 0;
            if (t[p].del && t[t[p].lc].siz + 1 == k) return t[p].val;
            if (t[t[p].lc].siz >= k) return qry_kth (t[p].lc, k);
            else return qry_kth (t[p].rc, k - t[t[p].lc].siz - t[p].del);
        }

        void erase_kth (int k) {erase_kth (rt, k);}
        void erase_kth (int &p, int k) {
            t[p].siz--;
            if (t[p].del && t[t[p].lc].siz + 1 == k) {t[p].del = 0; return ;}
            if (t[t[p].lc].siz + t[p].del >= k) erase_kth (t[p].lc, k);
            else erase_kth (t[p].rc, k - t[t[p].lc].siz - t[p].del);
        }

        void erase_node (T x) {
            erase_kth (qry_rank (x));
            if (t[rt].tot * alpha >= t[rt].siz) rebuild (rt);
        }
    };
}
