namespace SAM {
    static constexpr int MAXN = 1e5 + 7;
    static constexpr int MAXM = 26;    

    struct Node {
        array <int, MAXM> ch;
        int fa, len;
        Node () : fa (-1), len (0) {fill (all(ch), -1);}
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
            t[np].len = t[p].len + 1;
            for (; p != -1 && t[p].ch[v] == -1; p = t[p].fa) t[p].ch[v] = np;

            if (p == -1) {t[np].fa = rt; return ;}
            int q = t[p].ch[v];
            if (t[p].len + 1 == t[q].len) {t[np].fa = q; return ;}

            int nq = new_node (t[q]);
            t[nq].len = t[p].len + 1;
            t[q].fa = t[np].fa = nq;
            for (; p != -1 && t[p].ch[v] == q; p = t[p].fa) t[p].ch[v] = nq;
        }

        info & operator [] (int i) {return t[i];}
        const info operator [] (int i) const {return t[i];}
    };
}
