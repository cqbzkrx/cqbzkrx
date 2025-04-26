inline char get(void) {
    static char buf[1 << 20], *p1 = buf, *p2 = buf;
    if (p1 == p2) {
        p2 = (p1 = buf) + fread(buf, 1, 1 << 20, stdin);
        if (p1 == p2) return EOF;
    }
    return *p1++;
}

template<typename T>
inline void read(T &x) {
    x = 0; static char c; bool minus = false;
    for (; !(c >= '0' && c <= '9'); c = get()) if (c == '-') minus = true;
    for (; c >= '0' && c <= '9'; x = x * 10 + c - '0', c = get()); if (minus) x = -x;
}

// usage
void func() {
    int32_t t; read(t);
    int64_t x; read(x);
    uint32_t tt; read(tt);
    uint64_t xx; read(xx);
}