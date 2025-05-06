auto exgcd = [&](auto &&self, ll a, ll b) -> pair <ll, ll> {
    if (b == 0) return {1ll, 0ll};
    auto [x, y] = self (self, b, a % b);
    auto v = x;
    x = y;
    y = v - a / b * y;
    return {x, y};
};

// ax + by = gcd (a, b) 的整数解
