auto get_nxt = [&](const string &c, vector <int> &nxt) -> void {   // != Border
    nxt.resize (c.size() + 1); nxt[0] = -1;
    int i = 0, j = -1;
    while (i < (int) c.size()) {
        if (j == -1 || c[i] == c[j]) {
            i++, j++;
            if (c[i] == c[j]) nxt[i] = nxt[j];
            else nxt[i] = j;
        }
        else j = nxt[j];
    }
};

auto kmp = [&](const string &c, const string &s, const vector <int> nxt) -> vector <int> {   // c中找s; nxt -> s_nxt
    int i = 0, j = 0;
    vector ans (0, 0);
    while (i < (int) c.size()) {
        if (j == -1 || c[i] == s[j]) {
            i++, j++;
            if (j == (int) s.size()) ans.push_back (i - s.size ()), j = nxt[j];
        }
        else j = nxt[j];
    }
    return ans;
};
