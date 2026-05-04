template <u64 P, class T = ModInt :: mll <P>>
class _fac {
public:
    vector <T> fac, ifac;

    void init (int n) {
        fac.resize (n + 1), ifac.resize (n + 1);
        fac[0] = fac[1] = 1;
        for (int i = 2; i <= n; i++) fac[i] = fac[i - 1] * i;
        ifac[n] = fac[n].inv ();
        for (int i = n - 1; i >= 0; i--) ifac[i] = ifac[i + 1] * (i + 1);
    }
    
    T C (int n, int m) {
        return fac[n] * ifac[m] * ifac[n - m];
    }

    _fac (int n = N - 1) {init (n);}
};
