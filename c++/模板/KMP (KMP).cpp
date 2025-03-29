auto get_nxt = [&](const string &c, vector <int> &nxt) -> void {
    nxt.resize (c.size() + 1); nxt[0] = -1;
    int i = 0, j = -1;
    while (i < (int) c.size()) {
        if (j == -1 || c[i] == c[j]) i++, j++, nxt[i] = j;
        else j = nxt[j];
    }
};

auto kmp = [&](const string &c, const string &s, const vector <int> nxt) -> pair <int, int> { // c中找s; first -> T/F, second -> idx
    int i = 0, j = 0;
    while (i < (int) c.size()) {
        if (j == -1 || c[i] == s[j]) {
            i++, j++;
            if (j == (int) s.size()) return {1, i - s.size()};
        }
        else j = nxt[j];
    }
    return {-1, -1};
};
