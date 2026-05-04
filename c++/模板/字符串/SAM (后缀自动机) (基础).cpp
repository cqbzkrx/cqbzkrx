namespace SAM {
    static constexpr int MAXN = 1e6 + 7;
    static constexpr int MAXM = 26;
    static constexpr int A = 'a';

    struct Node {
        array <int, MAXM> ch;
        int fa, len;
        Node () : fa (0), len (0) {fill (all(ch), 0);}
    };

    inline int get (char c) {
        return c - A;
    }

    template <class info = Node>
    class SAM {
    public:
        static constexpr int rt = 1;
        vector <info> t;
        int lst, tot;

        SAM () : lst (1), tot (1) {
            t.reserve (MAXN << 1);
            t.emplace_back ();
            t.emplace_back ();
        }
        SAM (const string &str) : SAM () {Insert (str);}

        inline int new_node () {
            t.emplace_back ();
            return ++tot;
        }

        inline void Insert (const string &str) {
            for (auto v : str) Insert (v);
        }

        void Insert (char c) {
            int v = get (c);

            int p = lst, np = lst = new_node ();
            t[np].len = t[p].len + 1;
            for (; p && !t[p].ch[v]; p = t[p].fa) t[p].ch[v] = np;

            if (!p) {t[np].fa = rt; return ;}
            int q = t[p].ch[v];
            if (t[p].len + 1 == t[q].len) {t[np].fa = q; return ;}

            int nq = new_node ();
            t[nq] = t[q]; t[nq].len = t[p].len + 1;
            t[q].fa = t[np].fa = nq;
            for (; p && t[p].ch[v] == q; p = t[p].fa) t[p].ch[v] = nq;
        }

        inline info & operator [] (int i) {return t[i];}
        inline const info operator [] (int i) const {return t[i];}
        inline int & fa (int i) {return t[i].fa;}
        inline int & ch (int i, int j) {return t[i].ch[j];}
        inline int & len (int i) {return t[i].len;}

        vector <vector <int>> e;
        void init_pt () {
            e.assign (tot + 1, vector <int> (0, 0));
            for (int i = 2; i <= tot; i++) e[t[i].fa].push_back (i);
        }
    };
}
