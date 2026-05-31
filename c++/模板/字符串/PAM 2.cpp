// https://www.luogu.com.cn/record/279820700

namespace PAM {
    static constexpr int MAXN = 1e6 + 7;
    static constexpr int MAXM = 26;

    struct Node {
        array <int, MAXM> ch;
        int fail, cnt, len;  // cnt -> 前缀包含当前点的回文串个数
        Node (int _len = 0) : len (_len), cnt (0), fail (0) {fill (all(ch), 0);}
    };

    inline int get (char c) {
        return c - 'a';
    }

    template <class info = Node>
    class PAM {
    public:
        vector <info> t;
        string s;
        int num, lst;

        PAM () : num (1), lst (0) {
            t.reserve (MAXN);
            t.emplace_back (0);
            t.emplace_back (-1);
            t[0].fail = t[1].fail = 1;
            s = string ();
        }
        PAM (const string &s) : PAM () {Insert (s);}

        inline int new_node (int len = 0) {
            t.emplace_back (len);
            return ++num;
        }

        void Insert (const string &s) {
            for (auto v : s) Insert (v);
        }

        int find (int p) {
            while (s.size () - t[p].len - 1 <= 0 || *(s.rbegin () + t[p].len + 1) != *(s.rbegin ())) p = t[p].fail;
            return p;
        }

        void Insert (char c) {
            s += c;
            int v = get (c), p = find (lst);
            if (!t[p].ch[v]) {
                int np = new_node (t[p].len + 2);
                t[np].fail = t[find (t[p].fail)].ch[v];
                t[p].ch[v] = np;
                t[np].cnt = t[t[np].fail].cnt + 1;
            }
            lst = t[p].ch[v];
        }

        inline info & operator [] (int i) {return t[i];}
        inline const info operator [] (int i) const {return t[i];}
        inline int & fail (int i) {return t[i].fail;}
        inline const int fail (int i) const {return t[i].fail;}
        inline int & ch (int i, int j) {return t[i].ch[j];}
        inline const int ch (int i, int j) const {return t[i].ch[j];}
        inline int & len (int i) {return t[i].len;}
        inline const int len (int i) const {return t[i].len;}
        inline int & cnt (int i) {return t[i].cnt;}
        inline const int cnt (int i) const {return t[i].cnt;}
    };
}
