namespace SAM {
    static constexpr int MAXN = 1e5 + 7;
    static constexpr int MAXM = 26;    

    struct Node {
        array <int, MAXM> ch;
        int fa, len, siz;
        Node () : fa (-1), len (0), siz (0) {fill (all(ch), -1);}
    };

    inline int get (char c) {
        return c - 'a';
    }

    template <class info = Node>
    class SAM {
    public:
        static constexpr int rt = 0;
        vector <info> t;
        int lst, tot;

        SAM () : t (1, info ()), lst (0), tot (0) {}
        SAM (const string &str) : SAM () {Insert (str);}

        int new_node (const info &s = info ()) {
            t.push_back (s);
            return ++tot;
        }

        void Insert (const string &str) {
            for (auto v : str) Insert (v);
        }

        void Insert (char c) {
            int v = get (c);

            int p = lst, np = lst = new_node ();
            t[np].len = t[p].len + 1; t[np].siz = 1;
            for (; p != -1 && t[p].ch[v] == -1; p = t[p].fa) t[p].ch[v] = np;

            if (p == -1) {t[np].fa = rt; return ;}
            int q = t[p].ch[v];
            if (t[p].len + 1 == t[q].len) {t[np].fa = q; return ;}

            int nq = new_node (t[q]); t[nq].siz = 0;
            t[nq].len = t[p].len + 1;
            t[q].fa = t[np].fa = nq;
            for (; p != -1 && t[p].ch[v] == q; p = t[p].fa) t[p].ch[v] = nq;
        }

        info & operator [] (int i) {return t[i];}
        const info operator [] (int i) const {return t[i];}
        int fa (int i) {return t[i].fa;}
        int ch (int i, int j) {return t[i].ch[j];}
        int len (int i) {return t[i].len;}
        int siz (int i) {return t[i].siz;}

        vector <vector <int>> e;
        void init_pt () {
            e.assign (tot + 1, vector <int> (0, 0));
            for (int i = 1; i <= tot; i++) e[t[i].fa].push_back (i);
        }

        void dfs (int u = rt) {
            for (auto v : e[u]) {
                dfs (v);
                t[u].siz += t[v].siz;
            }
        }
    };
}
