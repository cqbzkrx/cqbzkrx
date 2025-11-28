namespace Trie {
    static constexpr int rt = 0;
    static constexpr int MAXN = 26;

    int get (char c) {
        return c - 'a';
    }

    struct Node {
        array <int, MAXN> son;
        int cnt;
        Node () : cnt (0) {fill (all(son), 0);}
    };

    template <class info = Node>
    class trie {
    public:
        vector <info> t;
        int num = 0, n = 0;

        trie () : n (0), num (0), t (1, info ()) {}
        trie (const vector <string> &a) : n (0), num (0), t (1, info ()) {init (a);}
        void init (const vector <string> &a) {for (auto &str : a) insert (str);}

        int new_node () {
            t.push_back (info ());
            return ++num;
        }

        void insert (const string &str) {
            int p = rt;
            for (auto c : str) {
                auto v = get (c);
                if (!t[p].son[v]) p = new_node (); 
                p = t[p].son[v];
            }
            t[p].cnt++;
        }

        int qry (const string &str) {
            int p = rt;
            for (auto c : str) {
                auto v = get (c);
                if (t[p].son[v]) p = t[p].son[v];
                else return 0;
            }
            return t[p].cnt;
        }
    };
}
