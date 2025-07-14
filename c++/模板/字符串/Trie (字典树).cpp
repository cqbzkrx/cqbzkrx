namespace Trie {
    struct Node {
        array <int, 26> son;
        array <int, 26> cnt;
        Node () {
            fill (all(son), 0);
            fill (all(cnt), -1);
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

        int get (char c) {
            return c - 'a';
        }

        void insert (const string &str) {
            int p = rt, len = str.size ();
            for (int i = 0; i < len; i++) {
                auto v = get (str[i]);
                if (t[p].son[v]) p = t[p].son[v];
                else {
                    t.push_back (Node ()), t[p].son[v] = ++cnt;
                    if (i != len - 1) p = cnt;
                }
            }
            t[p].cnt[get (str[len - 1])] = 1;
        }

        int qry (const string &str) {
            int p = rt, len = str.size ();
            for (int i = 0; i < len; i++) {
                auto v = get (str[i]);
                if (!t[p].son[v]) return 0;
                if (i != len - 1) p = t[p].son[v];
            }
            if (t[p].cnt[get (str[len - 1])] == -1) return 0;
            return 1;
        }
    };
}
