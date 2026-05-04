// https://www.luogu.com.cn/problem/P3975
// https://www.luogu.com.cn/record/276506422

namespace SAM {
    static constexpr int MAXN = 1e6 + 7;
    static constexpr int MAXM = 26;
    static constexpr int A = 'a';

    struct Node {
        array <int, MAXM> ch;
        int fa, len, siz;
        Node () : fa (0), len (0), siz (0) {fill (all(ch), 0);}
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
        inline int & fa (int i) {return t[i].fa;}
        inline int & ch (int i, int j) {return t[i].ch[j];}
        inline int & len (int i) {return t[i].len;}
        inline int & siz (int i) {return t[i].siz;}

        vector <vector <int>> e;
        vector <ll> dp;
        vector <int> vis;
        void init_pt () {
            e.assign (tot + 1, vector <int> (0, 0));
            for (int i = 2; i <= tot; i++) e[t[i].fa].push_back (i);
            dp.assign (tot + 1, 0ll);
            vis.assign (tot + 1, 0);
        }

        void calc_siz () {
            vector <int> cnt (tot + 1, 0), id (tot + 1, 0);
            for (int i = 2; i <= tot; i++) cnt[t[i].len]++;
            for (int i = 1; i <= tot; i++) cnt[i] += cnt[i - 1];
            for (int i = 2; i <= tot; i++) id[cnt[t[i].len]--] = i;
            for (int i = tot; i >= 2; i--) t[t[id[i]].fa].siz += t[id[i]].siz;
            t[rt].siz = 0;
        }

        ll calc_dp (int u = rt) {
            if (vis[u]) return dp[u]; vis[u] = 1;
            for (int i = 0; i < MAXM; i++) if (t[u].ch[i])
                dp[u] += calc_dp (t[u].ch[i]);
            return dp[u];
        }

        void qry (int u, ll k, string &ans) {
            if (k > dp[u]) {ans = "-1"; return ;}
            if (k <= t[u].siz) return ;
            k -= t[u].siz;
            for (int i = 0; i < MAXM; i++) if (t[u].ch[i]) {
                auto v = t[u].ch[i];
                if (k > dp[v]) k -= dp[v];
                else {
                    ans.push_back (char (A + i));
                    qry (v, k, ans);
                    return ;
                }
            }
        }
    };
}

void solve () {
    string s; cin >> s;
    SAM :: SAM sam (s);
    sam.init_pt ();

    int t; ll k; cin >> t >> k; 
    if (t == 0) {  // 相同的算一个
        for (int i = 2; i <= sam.tot; i++) sam.dp[i] = sam.siz (i) = 1;
    }
    else {  // 相同的算多个
        sam.calc_siz ();
        for (int i = 2; i <= sam.tot; i++) sam.dp[i] = sam.siz (i);
    }
    sam.calc_dp ();

    string ans;
    sam.qry (sam.rt, k, ans);
    cout << ans << '\n';
}
