vector <m64 <mod>> inv;

void init_inv () {
    inv.resize (N + 1);
    inv[0] = 0; inv[1] = 1;
    for (int i = 2; i <= N; i++) inv[i] = mod - inv[mod % i] * (mod / i);
}
