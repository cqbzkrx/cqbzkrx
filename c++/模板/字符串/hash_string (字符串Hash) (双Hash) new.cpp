namespace Hash {
    static constexpr ll mod1 = 1000001011;
    static constexpr ll mod2 = 1000000297;
    static constexpr ll B = 131;
    int maxn = 0;

    vector <ll> b1 (1, 1ll), b2 (1, 1ll);

    void get (int n) {
        for (int i = maxn + 1; i <= n; i++) {
            b1.push_back ((b1[i - 1] * B) % mod1);
            b2.push_back ((b2[i - 1] * B) % mod2);
        }

        maxn = n;
    };
    
    class hash_string {
    public:
        vector <ll> h1, h2;
        int n;

        hash_string (const string &s) {init (s);}
        hash_string () : n(0) {}

        void init (const string &s) {
            n = s.size();
            if (n > maxn) get (n);

            h1.resize (n + 1); h2.resize (n + 1);
            for (int i = 1; i <= n; i++) {
                h1[i] = (h1[i - 1] * B + s[i - 1]) % mod1;
                h2[i] = (h2[i - 1] * B + s[i - 1]) % mod2;
            }
        }
        
        pair <ll, ll> qry (int l, int r) {
            pair <ll, ll> ans;
            ans.x = (h1[r] - h1[l - 1] * b1[r - l + 1] % mod1 + mod1) % mod1;
            ans.y = (h2[r] - h2[l - 1] * b2[r - l + 1] % mod2 + mod2) % mod2;
            return ans;
        }
    };
}
