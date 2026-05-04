template <typename T>
pair <T, T> exgcd (T a, T b) {
    if (b == 0) return {1, 0};
    auto [x, y] = exgcd (b, a % b);

    auto tmp = x;
    x = y;
    y = tmp - a / b * y;
    
    return {x, y};
}

// ax + by = gcd (a, b) 的整数解
// x的最小正整数解要进行 x = (x % b + b) % b
