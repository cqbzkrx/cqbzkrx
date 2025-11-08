namespace ACAM {
    constexpr int rt = 0;
    constexpr int MAXN = 26;

    struct Node {
        array <int, MAXN> son;
        int cnt, fail, vis, id = -1;
        Node () : cnt (0), fail (-1), vis (0), id (-1) {fill (all(son), 0);}
        Node (int _id) : cnt (0), fail (-1), vis (0), id (_id) {fill (all(son), 0);}
    };

    template <class info = Node>
    class trie {
        vector <info> t;
        int num = 0, n = 0;
    
    public:
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
                    if (t[u].son[i]) {
                        t[t[u].son[i]].fail = t[t[u].fail].son[i];
                        q.push (t[u].son[i]);
                    }
                    else t[u].son[i] = t[t[u].fail].son[i];
                }
            }
        }

        void init (const vector <string> &a) {
            int len = 0;
            for (const string &str : a) len += str.size ();
            t.reserve (len + 1); t.push_back (info ());
            for (int i = 0; i < n; i++) insert (a[i], i);
            get_fail ();
        }

        int get (char c) {
            return c - 'a';
        }

        void insert (const string &str, int id) {
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
            n++;
        }

        int qry_tot (const string &str) {      // 总共包含多少模式串
            int p = rt, ans = 0;
            for (auto c : str) {
                p = t[p].son[get (c)];
                for (int i = p; i && !t[i].vis; i = t[i].fail) ans += t[i].cnt, t[i].vis = 1;
            }
            return ans;
        }

        vector <int> qry_cnt (const string &str) {      // 模式串出现次数
            int p = rt;
            vector <int> cnt (n, 0);
            for (auto c : str) {
                p = t[p].son[get (c)];
                for (int i = p; i; i = t[i].fail) if (t[i].id != -1)
                    cnt[t[i].id]++;
            }
            return cnt;
        }
    };
}
