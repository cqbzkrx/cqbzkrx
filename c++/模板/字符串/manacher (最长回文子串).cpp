auto manacher = [&](const string &s) -> int {
    string a = "$";
    for (int i = 0; i < (int) s.size (); i++) a += "#", a += s[i];
    a += "#@";

    int siz = a.size (), mid = 0, r = 0;
    vector <int> p (siz, 0);
    for (int i = 0; i < siz; i++) {
        if (i <= r) p[i] = min (r - i + 1, p[(mid << 1) - i]);
        while (i - p[i] >= 0 && i + p[i] < siz && a[i - p[i]] == a[i + p[i]])
            p[i]++;
        if (i + p[i] - 1 >= r) mid = i, r = i + p[i] - 1;
    }

    int ans = 0;
    for (int i = 0; i < siz; i++) cmax (ans, p[i]);
    return ans - 1;
};
