namespace SAM {
    static constexpr int MAXN = 1e6 + 7;
    static constexpr int MAXM = 26;

    struct Node {
        array <int, MAXM> ch;
        int fa, len, cnt;
        Node () : fa (0), len (0), cnt (0) {fill (all(ch), 0);}
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
        int tot;

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
            t[np].len = t[p].len + 1; t[np].cnt = 1;
            for (; p && !t[p].ch[v]; p = t[p].fa) t[p].ch[v] = np;

            if (!p) {t[np].fa = rt; return ;}
            int q = t[p].ch[v];
            if (t[p].len + 1 == t[q].len) {t[np].fa = q; return ;}

            int nq = new_node ();
            t[nq] = t[q]; t[nq].cnt = 0; t[nq].len = t[p].len + 1;
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

        vector <int> cnt;
        void calc_cnt () {
            cnt.assign (tot + 1, 0);
            vector <int> cnt2 (tot + 1, 0), id (tot + 1, 0);
            for (int i = 2; i <= tot; i++) cnt2[t[i].len]++, cnt[i] = t[i].cnt;
            for (int i = 1; i <= tot; i++) cnt2[i] += cnt2[i - 1];
            for (int i = 2; i <= tot; i++) id[cnt2[t[i].len]--] = i;
            for (int i = tot; i >= 2; i--) cnt[fa (id[i])] += cnt[id[i]];
            cnt[rt] = 0;
        }
    };
}
