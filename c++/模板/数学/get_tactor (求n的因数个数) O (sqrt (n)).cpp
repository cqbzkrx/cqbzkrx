auto get_tactor = [&](ll n) -> ll {
    ll ans = 1;
    for (auto v : prime) {
        if (v * v > n) break;
        ll cnt = 1;
        while (n && n % v == 0) n /= v, cnt++;
        ans *= cnt;
    }

    if (n > 1) ans *= 2;
    return ans;
};
