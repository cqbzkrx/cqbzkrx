class KMP {
public:
    vector <int> nxt;

    KMP () {}
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
        nxt.resize(s.size() + 1);

        nxt[0] = -1;
        int i = 0, j = -1;
        while (i < n) {
            if (j == -1 || s[i] == s[j]) nxt[++i] = ++j;
            else j = nxt[j];
        }
    }
};
