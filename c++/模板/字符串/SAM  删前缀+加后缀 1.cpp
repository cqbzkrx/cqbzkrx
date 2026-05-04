// https://codeforces.com/contest/235/problem/C
// https://codeforces.com/contest/235/submission/373401019

namespace SAM {
    static constexpr int MAXN = 1e6 + 7;
    static constexpr int MAXM = 26;

    struct Node {
        array <int, MAXM> ch;
        int fa, len, siz;
        Node () : fa (0), len (0), siz (0) {fill (all(ch), 0);}
    };

    inline int get (char c) {
        return c - 'a';
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
            t[np].len = t[p].len + 1; t[np].siz = 1;
            for (; p && !t[p].ch[v]; p = t[p].fa) t[p].ch[v] = np;

            if (!p) {t[np].fa = rt; return ;}
            int q = t[p].ch[v];
            if (t[p].len + 1 == t[q].len) {t[np].fa = q; return ;}

            int nq = new_node ();
            t[nq] = t[q]; t[nq].siz = 0; t[nq].len = t[p].len + 1;
            t[q].fa = t[np].fa = nq;
            for (; p && t[p].ch[v] == q; p = t[p].fa) t[p].ch[v] = nq;
        }

        inline info & operator [] (int i) {return t[i];}
        inline const info operator [] (int i) const {return t[i];}
        inline int fa (int i) {return t[i].fa;}
        inline int ch (int i, int j) {return t[i].ch[j];}
        inline int len (int i) {return t[i].len;}
        inline int siz (int i) {return t[i].siz;}

        vector <vector <int>> e;
        vector <int> ans;
        void init_pt () {
            e.assign (tot + 1, vector <int> (0, 0));
            for (int i = 2; i <= tot; i++) e[t[i].fa].push_back (i);
            ans.assign (tot + 1, -1);
        }

        void calc_siz () {
            vector <int> cnt (tot + 1, 0), id (tot + 1, 0);
            for (int i = 2; i <= tot; i++) cnt[t[i].len]++;
            for (int i = 1; i <= tot; i++) cnt[i] += cnt[i - 1];
            for (int i = 2; i <= tot; i++) id[cnt[t[i].len]--] = i;
            for (int i = tot; i >= 2; i--) t[t[id[i]].fa].siz += t[id[i]].siz;
        }

        ll calc (const string &s, int tim) {
            int u = rt, len = 0, n = s.size ();

            auto add = [&](char c) -> void {   // 加后缀
                auto v = get (c);
                while (u && !t[u].ch[v]) u = t[u].fa, len = t[u].len;
                if (t[u].ch[v]) len++, u = t[u].ch[v];
            };

            auto del = [&]() -> void {  // 删前缀
                if (len > n && --len == t[t[u].fa].len) u = t[u].fa;
            };

            for (auto v : s) add (v);

            ll res = 0;
            for (int i = 0; i < n; i++) {
                if (len == n && ans[u] < tim) res += t[u].siz, ans[u] = tim;
                add (s[i]);
                del (); 
            }

            return res;
        }
    };
}

void solve () {
    string s; cin >> s;
    SAM :: SAM sam (s);
 
    sam.init_pt ();
    sam.calc_siz ();
 
    int n; cin >> n;
    for (int i = 0; i < n; i++) {
        string c; cin >> c;
        cout << sam.calc (c, i) << '\n';
    }
}
