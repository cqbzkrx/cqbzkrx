auto get_nxt = [&](const string &c, vector <int> &nxt) -> void {   // Border
    nxt.resize (c.size() + 1); nxt[0] = -1;
    int i = 0, j = -1;
    while (i < (int) c.size()) {
        if (j == -1 || c[i] == c[j]) i++, j++, nxt[i] = j;
        else j = nxt[j];
    }
};
