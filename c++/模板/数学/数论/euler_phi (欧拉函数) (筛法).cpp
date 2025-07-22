// 1 : 埃氏筛 O (nloglogn);
vector phi (N, 0), prime (N, 1);
fill (all(prime), 1);
iota (all(phi), 0);

vector phi (n + 1, 0), np (n + 1, 0), prime (0, 0);
iota (all(phi), 0);
np[0] = np[1] = 1;
for (int i = 2; i <= n; i++) if (np[i] == 0) {
    prime.push_back (i);
    for (int j = i; j <= n; j += i) phi[j] -= phi[j] / i, np[j] = (j != i);
}

// 2 : 线性筛 O (n)
vector phi (N + 1, 0), np (N + 1, 0);
np[0] = np[1] = phi[1] = 1;
for (int i = 2; i <= N; i++) {
    if (!np[i]) {
        prime.push_back (i);
        phi[i] = i - 1;
    }
    for (auto v : prime) {
        if (i * v > N) break;
        np[i * v] = 1;
        if (i % v == 0) {phi[i * v] = phi[i] * v; break;}
        else phi[i * v] = phi[i] * (v - 1);
    }
}
