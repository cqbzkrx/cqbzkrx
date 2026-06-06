namespace SAM {
    static constexpr int MAXN = 1e6 + 7;
    static constexpr int MAXM = 26;

    struct Node {
        array <int, MAXM> ch;
        int fa, len, siz, fst, lst;
        Node () : fa (0), len (0), siz (0), fst (-1), lst (-1) {fill (all(ch), 0);}
    };

    inline int get (char c) {
        return c - 'a';
    }

    template <class info = Node>
    class SAM {
        vector <info> t;
        int lst;
    public:
        static constexpr int rt = 1;
        int tot, num;

        SAM () : lst (1), tot (1), num (0) {
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
            t[np].len = t[p].len + 1; t[np].siz = 1;
            for (; p && !t[p].ch[v]; p = t[p].fa) t[p].ch[v] = np;
            t[np].lst = t[np].fst = num++;

            if (!p) {t[np].fa = rt; return ;}
            int q = t[p].ch[v];
            if (t[p].len + 1 == t[q].len) {t[np].fa = q; return ;}

            int nq = new_node ();
            t[nq] = t[q]; t[nq].siz = 0; t[nq].len = t[p].len + 1;
            t[q].fa = t[np].fa = nq;
            for (; p && t[p].ch[v] == q; p = t[p].fa) t[p].ch[v] = nq;
        }

        inline info & operator [] (int i) {return t[i];}
        inline int & fa (int i) {return t[i].fa;}
        inline int & ch (int i, int j) {return t[i].ch[j];}
        inline int & len (int i) {return t[i].len;}

        vector <vector <int>> e;
        void init_pt () {
            e.assign (tot + 1, vector <int> (0, 0));
            for (int i = 2; i <= tot; i++) e[t[i].fa].push_back (i);
        }

        void calc_cnt () {
            vector <int> cnt (tot + 1, 0), id (tot + 1, 0);
            for (int i = 2; i <= tot; i++) cnt[t[i].len]++;
            for (int i = 1; i <= tot; i++) cnt[i] += cnt[i - 1];
            for (int i = 2; i <= tot; i++) id[cnt[t[i].len]--] = i;
            for (int i = tot; i >= 2; i--) t[fa (id[i])].siz += t[id[i]].siz;
            t[rt].siz = 0;
        }

        void calc_pos () {
            vector <int> cnt (tot + 1, 0), id (tot + 1, 0);
            for (int i = 2; i <= tot; i++) cnt[t[i].len]++;
            for (int i = 1; i <= tot; i++) cnt[i] += cnt[i - 1];
            for (int i = 2; i <= tot; i++) id[cnt[t[i].len]--] = i;
            for (int i = tot; i >= 2; i--) {
                cmax (t[fa (i)].lst, t[i].lst);
                cmin (t[fa (i)].fst, t[i].fst);
            }

            t[rt].lst = t[rt].fst = -1;
        }
    };
}
