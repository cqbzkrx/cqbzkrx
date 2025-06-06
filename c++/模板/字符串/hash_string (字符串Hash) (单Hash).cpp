class hash_string {
public:
    static constexpr ll mod = 1000001011;
    static constexpr ll B = 131;

    string s;
    vector <ll> b, h;
    int n;

    hash_string (const string &c) {init (c);}
    hash_string () : n(0) {}

    void init (const string &c) {
        n = c.size(); s = ' ' + c;

        b.resize(n + 1);
        b[0] = 1;
        for (int i = 1; i <= n; i++) b[i] = b[i - 1] * B % mod;

        h.resize (n + 1);
        for (int i = 1; i <= n; i++) h[i] = (h[i - 1] * B + s[i]) % mod;
    }
    
    ll qry (int l, int r) {
        return (h[r] - h[l - 1] * b[r - l + 1] % mod + mod) % mod;
    }
};
