vector prime (0, 0), divi (0, 0);
bitset <N> np;

auto init_prime = [&](int n = N - 1) -> void {
    // divi.resize (N);
    np[1] = 1;
    for (int i = 2; i <= n; i++) {
        if (!np[i]){
            prime.push_back (i);
            // divi[i] = i;
        }
        for (auto v : prime){
            if (v * i > n) break;
            np[v * i] = 1;
            // divi[v * i] = v;
            if (i % v == 0) break;
        }
    }
};
