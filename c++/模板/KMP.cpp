class KMP {
    public:

    int n;
    vector <int> nxt;

    KMP () : n(0), nxt(vector (0, 0)) {}
    KMP (const string &s) {get_nxt (s);}

    bool kmp (const string &a, const string &b, const vector <int> &nxt) {
        int i = 0, j = 0;
        while (i < (int) a.size()) {
            if (j == -1 || a[i] == b[i]) {
                i++, j++;
                if (j == (int) b.size()) return 1;
            }
            else j = nxt[j];
        }
        return 0;
    }

    void get_nxt (const string &s) {
        n = s.size();
        nxt.resize(n + 1);

        nxt[0] = -1;
        int i = 0, j = -1;
        while (i < n) {
            if (j == -1 || s[i] == s[j]) nxt[++i] = ++j;
            else j = nxt[j];
        }
    }
};
