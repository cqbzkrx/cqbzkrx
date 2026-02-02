namespace BST {
    constexpr int MAXN = 3e5 + 7;
    mt19937 rd (time (0));

    template <typename T>
    struct Node {
        T val;
        int lc, rc, siz, lazy, rnd;
        Node () : val (0), lc (0), rc (0), siz (0), lazy (0), rnd (0) {}
        Node (T x, int _siz = 1, int _lc = 0, int _rc = 0) : val (x), siz (_siz), lc (_lc), rc (_rc), rnd (rd ()), lazy (0) {}
    };

    template <typename T, class info = Node <T>>
    class fhq_treap {
        vector <info> t;
        int rt, num;

        inline int new_node (T x) {
            t.emplace_back (x);
            return ++num;
        }

        inline void get (int p) {
            t[p].siz = t[t[p].lc].siz + t[t[p].rc].siz + 1;
        }

        inline void push_down (int p) {
            if (!t[p].lazy) return ;
            swap (t[p].lc, t[p].rc);
            t[t[p].lc].lazy ^= 1; t[t[p].rc].lazy ^= 1;
            t[p].lazy = 0;
        }

        void split (int p, int val, int &l, int &r) {
            if (p == 0) {l = r = 0; return ;}
            push_down (p);
            if (t[t[p].lc].siz < val) {
                l = p;
                split (t[p].rc, val - t[t[p].lc].siz - 1, t[p].rc, r);
            }
            else {
                r = p;
                split (t[p].lc, val, l, t[p].lc);
            }
            get (p);
        }

        int merge (int l, int r) {
            if (l == 0 || r == 0) return l + r;
            push_down (l); push_down (r);
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

        void insert (T x) {rt = merge (rt, new_node (x));}
        
        fhq_treap (const vector <T> &a) {init (a);}
        void init (const vector <T> &a) {
            init (a.size ());
            for (auto v : a) rt = merge (rt, new_node (v));
        }

        void reverse (int l, int r) {
            int x, y, z;
            split (rt, l - 1, x, y); split (y, r - l + 1, y, z);
            t[y].lazy ^= 1;
            rt = merge (merge (x, y), z);
        }

        vector <T> dfs () {
            vector <T> ans (0, T ());
            dfs (rt, ans);
            return ans;
        }
        
        void dfs (int p, vector <T> &ans) {
            if (p == 0) return ;
            push_down (p);
            dfs (t[p].lc, ans);
            ans.push_back (t[p].val);
            dfs (t[p].rc, ans);
        }
    };
}

void solve () {
    int n, m; cin >> n >> m;
    vector a (n, 0); iota (all(a), 1);
    BST :: fhq_treap <int> bst (a);

    // BST :: fhq_treap <int> bst (n);
    // for (int i = 1; i <= n; i++) bst.insert (i);
    
    while (m--) {
        int l, r; cin >> l >> r;
        bst.reverse (l, r);
    }

    vector ans = bst.dfs ();
    for (auto &v : ans) cout << v << ' ';
    cout << '\n';
}
