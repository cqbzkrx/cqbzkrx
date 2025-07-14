namespace Trie {
    struct Node {
        array <int, 26> son;
        array <int, 26> cnt;
        Node () {
            fill (all(son), 0);
            fill (all(cnt), 0);
        }
    };
    
    class Trie {
    public:
        static constexpr int rt = 0;

        vector <Node> t;
        int cnt = 0;

        Trie () : t (1, Node ()) {}
        Trie (const vector <string> &a)  : t (1, Node ()) {init (a);}

        void init (const vector <string> &a) {
            for (const string &str : a) insert (str);
        }

        void insert (const string &str) {
            int p = rt;
            for (auto ch : str) {
                auto v = ch - 'a';
                if (t[p].son[v]) p = t[p].son[v];
                else t.push_back (Node ()), p = t[p].son[v] = ++cnt;
            }
        }

        bool qry (const string &str) {
            int p = rt;
            for (auto ch : str) {
                auto v = ch - 'a';
                if (!t[p].son[v]) return 0;
                p = t[p].son[v];
            }
            return 1;
        }
    };
}
