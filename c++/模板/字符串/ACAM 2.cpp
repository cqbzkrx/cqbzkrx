// https://www.luogu.com.cn/problem/P5357
// https://www.luogu.com.cn/record/280563341

namespace ACAM {
    static constexpr int MAXN = 1e6 + 7;
    static constexpr int MAXM = 26;

    struct Node {
        array <int, MAXM> ch;
        int fail, len;
        Node () : fail (0), len (0) {fill (all(ch), 0);}
    };

    inline int get (char c) {
        return c - 'a';
    }

    template <class info = Node>
    class trie {
    public:
        static constexpr int rt = 1;
        vector <info> t;
        vector <int> id;
        int tot;

        trie () : tot (1), id (0, 0) {
            t.reserve (MAXN);
            t.emplace_back (); t.emplace_back ();
            fill (all (t[0].ch), 1); t[0].len = -1;
        }
        trie (const vector <string> &a) : trie () {
            for (auto &v : a) Insert (v);
        }

        inline int new_node () {
            t.emplace_back ();
            return ++tot;
        }

        int Insert (const string &s) {
            int p = rt;
            for (auto c : s) {
                int v = get (c);
                if (!t[p].ch[v]) {
                    t[p].ch[v] = new_node ();
                    t[t[p].ch[v]].len = t[p].len + 1;
                }
                p = t[p].ch[v];
            }

            id.push_back (p);
            return p;
        }

        void get_fail () {
            queue <int> q; q.push (rt);
            while (q.size ()) {
                auto p = q.front (); q.pop ();
                for (int i = 0; i < MAXM; i++) {
                    if (!t[p].ch[i]) t[p].ch[i] = t[t[p].fail].ch[i];
                    else {
                        t[t[p].ch[i]].fail = t[t[p].fail].ch[i];
                        q.push (t[p].ch[i]);
                    }
                }
            }
        }

        vector <int> calc (const string &s) {
            vector dp (tot + 1, 0);
            int p = 1;
            for (auto c : s) {
                p = t[p].ch[get (c)];
                dp[p]++;
            }

            vector e (tot + 1, vector (0, 0));
            for (int i = 2; i <= tot; i++) e[t[i].fail].push_back (i);

            auto dfs = [&](auto &&self, int u) -> void {
                for (auto v : e[u]) {
                    self (self, v);
                    dp[u] += dp[v];
                }
            };

            dfs (dfs, rt);

            vector ans (id.size (), 0);
            for (int i = 0; i < id.size (); i++) ans[i] = dp[id[i]];
            return ans;
        }

        inline info & operator [] (int i) {return t[i];}
        inline const info operator [] (int i) const {return t[i];}
        inline int & fail (int i) {return t[i].fail;}
        inline const int fail (int i) const {return t[i].fail;}
        inline int & ch (int i, int j) {return t[i].ch[j];}
        inline const int ch (int i, int j) const {return t[i].ch[j];}
        inline int & len (int i) {return t[i].len;}
        inline const int len (int i) const {return t[i].len;}
    };
}

void solve () {
    int n; cin >> n;
    vector a (n, string ());
    for (auto &v : a) cin >> v;

    ACAM :: trie t (a);
    t.get_fail ();

    string s; cin >> s;
    auto ans = t.calc (s);
    for (auto &v : ans) cout << v << '\n';
}
