namespace ACAM {
    constexpr int rt = 0;
    constexpr int MAXN = 26;

    struct Node {
        array <int, MAXN> son;
        int cnt, fail;
        int vis;   // qry_tot
        int id = -1;   // qry_cnt
        int res, in = 0;   // topu
        Node (int _id = -1) : cnt (0), fail (-1) {
            fill (all(son), 0);
            vis = 0;
            id = _id;
            in = 0, res = 0; 
        }
    };

    template <class info = Node>
    class trie {
    public:
        vector <info> t;
        int num = 0, n = 0;
    
        trie () : n (0), t (1, info ()), num (0) {}
        trie (const vector <string> &a) : n (0), num (0) {init (a);};

        void get_fail () {
            queue <int> q;
            t[0].fail = 0;
            for (int i = 0; i < MAXN; i++) if (t[0].son[i]) {
                t[t[0].son[i]].fail = 0;
                q.push (t[0].son[i]);
            }

            while (q.size ()) {
                auto u = q.front (); q.pop ();
                for (int i = 0; i < MAXN; i++) {
                    auto v = t[u].son[i];
                    if (v) {
                        t[v].fail = t[t[u].fail].son[i];
                        t[t[v].fail].in++;
                        q.push (v);
                    }
                    else t[u].son[i] = t[t[u].fail].son[i];
                }
            }
        }

        void init (const vector <string> &a) {
            int len = 0;
            for (const string &str : a) len += str.size ();
            t.reserve (len + 1); t.push_back (info ());
            for (int i = 0; i < (int) a.size (); i++) insert (a[i], i);
            get_fail ();
        }

        int get (char c) {
            return c - 'a';
        }

        void insert (const string &str, int id) {
            n++;
            int p = rt;
            for (auto c : str) {
                auto v = get (c);
                if (t[p].son[v]) p = t[p].son[v];
                else {
                    t.push_back (info ()), t[p].son[v] = ++num;
                    p = num;
                } 
            }
            t[p].cnt++;
            t[p].id = id;
        }

        int qry_tot (const string &str) {      // 总共包含多少模式串
            int p = rt, ans = 0;
            for (auto c : str) {
                p = t[p].son[get (c)];
                for (int i = p; i && !t[i].vis; i = t[i].fail) ans += t[i].cnt, t[i].vis = 1;
            }
            return ans;
        }

        void qry_cnt (const string &str) {      // 模式串出现次数 topu优化
            int p = rt;
            for (auto c : str) {
                p = t[p].son[get (c)];
                t[p].res++;
            }
        }

        vector <int> topu () {     // 模式串出现次数 topu优化 统计答案
            queue <int> q;
            for (int i = 0; i <= num; i++) if (t[i].in == 0)
                q.push (i);

            vector <int> cnt (n, 0);
            while (q.size ()) {
                auto u = q.front (); q.pop ();
                if (t[u].id != -1) cnt[t[u].id] = t[u].res;

                auto v = t[u].fail;
                t[v].res += t[u].res;
                if (--t[v].in == 0) q.push (v);
            }

            return cnt;
        }
    };
}
