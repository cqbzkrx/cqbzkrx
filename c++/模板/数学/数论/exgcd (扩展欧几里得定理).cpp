auto exgcd = [&](auto &&self, ll a, ll b) -> pair <ll, ll> {
    if (b == 0) return {1ll, 0ll};
    auto [x, y] = self (self, b, a % b);
    auto tmp = x;
    x = y;
    y = tmp - a / b * y;
    return {x, y};
};

// ax + by = gcd (a, b) 的整数解
// x的最小正整数解要进行 x = (x % b + b) % b
