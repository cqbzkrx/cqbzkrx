auto read = [&](int k = mod) -> ll {
    ll x = 0, f = 1;
    char ch = getchar ();
    while (ch < '0' || ch > '9') {
        if (ch == '-') f = -1;
        ch = getchar ();
    }

    while (ch >= '0' && ch <= '9') {
        x = x * 10 + ch - '0';
        x %= k;
        ch = getchar ();
    }
    return x;
};
