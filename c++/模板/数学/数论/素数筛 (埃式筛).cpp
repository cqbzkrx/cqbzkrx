vector prime (0, 0);
bitset <N> np;

auto init_prime_Era = [&](int n = N - 1) {
    np[0] = np[1] = 1;
    for (int i = 2; i * i <= n; i++) if (!np[i])
        for (int j = i * i; j <= n; j += i) np[j] = 1;

    for (int i = 2; i <= n; i++) if (!np[i])
        prime.push_back (i);
};
