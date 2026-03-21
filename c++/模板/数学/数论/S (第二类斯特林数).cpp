m64 <mod> S (int n, int m) {
    if (m > n || m < 0) return 0;

    m64 <mod> ans = 0;
    for (int i = 0; i <= m; i++) {
        m64 <mod> res = ifac[i] * ifac[m - i] * qpow <m64 <mod>> (i, n);
        if ((m - i) & 1) ans -= res;
        else ans += res;
    }

    return ans;
}
