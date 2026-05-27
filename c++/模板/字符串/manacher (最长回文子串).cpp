auto manacher = [&](const string &s, vector <int> &p) -> void {
    string t = "#";
    for (auto c : s) t += c, t += '#';

    int n = t.size ();
    p.resize (n);

    int m = 0, r = 0;
    for (int i = 0; i < n; i++) {
        if (i <= r) p[i] = min (r - i + 1, p[(m << 1) - i]);
        else p[i] = 1;
        while (i - p[i] >= 0 && i + p[i] < n && t[i - p[i]] == t[i + p[i]])
            p[i]++;
        if (i + p[i] - 1 > r) m = i, r = i + p[i] - 1;
    }
};
