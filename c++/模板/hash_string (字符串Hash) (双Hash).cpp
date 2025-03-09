class hash_string {
public:
    static constexpr ll mod1 = 1000001011;
    static constexpr ll mod2 = 1000000297;
    static constexpr ll B = 131;

    string s;
    vector <ll> b1, b2, h1, h2;
    int n;

    hash_string (const string &c) {init (c);}
    hash_string () : n(0) {}

    void init (const string &c) {
        n = c.size(); s = ' ' + c;

        b1.resize(n + 1);
        b1[0] = 1;
        b2.resize(n + 1);
        b2[0] = 1;

        for (int i = 1; i <= n; i++) b1[i] = b1[i - 1] * B % mod1;
        for (int i = 1; i <= n; i++) b2[i] = b2[i - 1] * B % mod2;

        h1.resize (n + 1);
        h2.resize (n + 1);
        for (int i = 1; i <= n; i++) h1[i] = (h1[i - 1] * B + s[i]) % mod1;
        for (int i = 1; i <= n; i++) h2[i] = (h2[i - 1] * B + s[i]) % mod2;
    }
    
    pair <ll, ll> qry (int l, int r) {
        pair <ll, ll> ans;
        ans.first = (h1[r] - h1[l - 1] * b1[r - l + 1] % mod1 + mod1) % mod1;
        ans.second = (h2[r] - h2[l - 1] * b2[r - l + 1] % mod2 + mod2) % mod2;
        return ans;
    }
};
