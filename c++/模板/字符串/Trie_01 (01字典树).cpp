namespace Trie_01 {
    const int rt = 0;
    const int MAXN = 2;
    const int MAXM = 29;

    struct Node {
        array <int, MAXN> son;
        Node () {fill (all(son), 0);}
        Node (const array <int, MAXN> &s) : son (s) {}
    };

    template <typename T, class info = Node>
    class trie {
    public:
        vector <info> t;
        int num = 0;

        trie () : num (0), t (1, info ()) {}
        trie (const vector <T> &a) {init (a);}
        void init (const vector <T> &a) {
            t.assign (1, info ());
            num = 0;
            for (auto v : a) insert (v);
        }
        
        void insert (T x) {
            int p = rt;
            for (int i = MAXM; i >= 0; i--) {
                int v = (x >> i) & 1;
                if (!t[p].son[v]) {
                    t[p].son[v] = ++num;
                    t.emplace_back (info ());
                }
                p = t[p].son[v];
            }
        }

        T qry (T x) {   // 最大异或
            int p = rt;
            T ans = 0;
            for (int i = MAXM; i >= 0; i--) {
                int v = (x >> i) & 1;
                if (t[p].son[v ^ 1]) p = t[p].son[v ^ 1], ans |= (1 << i);
                else p = t[p].son[v];
            }
            return ans;
        }
    };
}
