// 1 : 
auto get_euler_phi = [&](int n) -> int {
    int ans = n;
    for (int i = 2; i * i <= n; i++) if (n % i == 0) {
        ans = ans / i * (i - 1);
        while (n % i == 0) n /= i;
    }
    if (n > 1) ans = ans / n * (n - 1);
    return ans;
};

// 2 : prime
auto get_euler_phi = [&](int n) -> int {
    int ans = n;
    for (auto v : prime) {
        if (v * v > n) break;
        if (n % v == 0) ans -= ans / v;
        while (n && n % v == 0) n /= v;
    }

    if (n > 1) ans -= ans / n;
    return ans;
};
