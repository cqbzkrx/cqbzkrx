auto calc = [&](int n) -> int {
    int ans = 1;
    for (auto p : prime) {
        if (p * p * p > n) break;
        int cnt = 1;
        while (n && n % p == 0) cnt++, n /= p;
        ans = ans * cnt;
    }

    int sq = sqrt (n + 0.5);

    if (!np[n]) ans *= 2;
    else if (!np[sq] && sq * sq == n) ans *= 3;
    else if (n != 1) ans *= 4;

    return ans;
};  // n ^ (1 / 3)
