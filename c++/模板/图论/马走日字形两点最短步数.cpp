auto knightdist = [&](ll x1, ll y1, ll x2, ll y2) -> ll {
    ll dx = llabs (x1 - x2), dy = llabs (y1 - y2);
    if (dx < dy) swap (dx, dy);
    if (dx == 1 && dy == 0) return 3;
    if (dx == 2 && dy == 2) return 4;
    ll d = max ((dx + 1) / 2, (dx + dy + 2) / 3);
    if ((d ^ (dx + dy)) & 1) d++;
    return d;
};
