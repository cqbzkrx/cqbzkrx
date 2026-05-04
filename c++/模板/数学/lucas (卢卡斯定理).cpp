// C (n, m) % k

void solve () {
    ll n, m, k; cin >> n >> m >> k;
    vector fac (k, 0ll); fac[0] = 1;
    for (int i = 1; i < k; i++) fac[i] = fac[i - 1] * i % k;

    auto qpow = [&](ll a, ll b) -> ll {
        ll ans = 1;
        while (b) {
            if (b & 1) ans = ans * a % k;
            a = a * a % k;
            b >>= 1;
        }
        return ans;
    };

    auto inv = [&](ll x) -> ll {
        return qpow (x, k - 2);
    };

    auto lucas = [&](auto &&self, ll n, ll m) -> ll {
        if (m == 0) return 1;
        if (m % k > n % k) return 0;
        ll c = fac[n % k] * inv (fac[m % k]) % k * inv (fac[n % k - m % k]) % k;
        return c * self (self, n / k, m / k) % k;
    };

    auto C = [&](ll n, ll m) -> ll {
        return lucas (lucas, n, m);
    };

    cout << C (n, m) << '\n';
}
