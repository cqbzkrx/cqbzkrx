namespace kmpam {
    constexpr int MAXM = 26;

    inline int get (char c) {
        return c - 'a';
    }

    void get_nxt (const string &c, vector <int> &nxt) {
        nxt.resize (c.size() + 1); nxt[0] = -1;
        int i = 0, j = -1;
        while (i < (int) c.size()) {
            if (j == -1 || c[i] == c[j]) i++, j++, nxt[i] = j;
            else j = nxt[j];
        }
    }

    vector <array <int, MAXM>> build (const string &s, const vector <int> &nxt) {
        vector <array <int, MAXM>> t (s.size () + 1);
        for (int i = 0; i <= s.size (); i++) for (int j = 0; j < MAXM; j++) {
            if (i < s.size () && j == get (s[i])) t[i][j] = i + 1;
            else t[i][j] = (i == 0 ? 0 : t[nxt[i]][j]);
        }
        return t;
    }

    vector <int> kmp (const string &c, const string &s, const vector <array <int, MAXM>> &t) {
        vector ans (0, 0);
        int p = 0;
        for (int i = 0; i < c.size (); i++) {
            p = t[p][get (c[i])];
            if (p == s.size ()) ans.push_back (i - s.size () + 1);
        }

        return ans;
    }
}
