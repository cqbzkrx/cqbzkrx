namespace Trie {
    constexpr int rt = 0;

    struct Node {
        array <int, 26> son;
        int cnt = -1;
        Node () : cnt (-1) {fill (all(son), -1);}
    };

    template <class info = Node>
    class trie {
        vector <info> t;
        int num = 0;
    
    public:
        trie () : t (1, info ()), num (0) {}
        trie (const vector <string> &a) : trie () {for (const string &str : a) insert (str);};
        trie (const int n) {t.reserve ((n + 1) * 26 + 1); t.push_back (info ());}

        int get (char c) {
            return c - 'a';
        }

        void insert (const string &str) {
            int p = rt, len = str.size ();
            for (int i = 0; i < len; i++) {
                auto v = get (str[i]);
                if (t[p].son[v] != -1) p = t[p].son[v];
                else {
                    t.push_back (info ()), t[p].son[v] = ++num;
                    p = num;
                } 
            }
            cmax (t[p].cnt, 0); t[p].cnt++;
        }

        int qry (const string &str) {
            int p = rt, len = str.size ();
            for (int i = 0; i < len; i++) {
                auto v = get (str[i]);
                if (t[p].son[v] == -1) return -1;
                p = t[p].son[v];
            }
            if (t[p].cnt == -1) return -1;
            return t[p].cnt;
        }
    };
}
