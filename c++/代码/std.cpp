#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
using namespace std;
using ll = long long;
using db = double;
using ull = unsigned long long;
const int inf = 1e9 + 7;
const ll INF = 1e18 + 7;
const db eps = 1e-6;
const int mod = 1e9 + 7;
const int N = 2e6 + 7;

namespace K {
    namespace Hash {
        struct custom_hash{
            static uint64_t splitmix64(uint64_t x){
                x += 0x9e3779b97f4a7c15;
                x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
                x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
                return (x ^ (x >> 31));
            }

            size_t operator()(uint64_t x) const{
                static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
                return splitmix64(x + FIXED_RANDOM);
            }
        };
    }

    namespace print {
        inline char get(void){
            static char buf[1 << 20], *p1 = buf, *p2 = buf;
            if (p1 == p2){
                p2 = (p1 = buf) + fread(buf, 1, 1 << 20, stdin);
                if (p1 == p2) return EOF;
            }
            return *p1++;
        }

        template <typename T>
        inline void read(T &x){
            x = 0;
            static char c;
            bool minus = false;
            for (; !(c >= '0' && c <= '9'); c = get()) if (c == '-')
                minus = true;
            for (; c >= '0' && c <= '9'; x = x * 10 + c - '0', c = get());
            if (minus) x = -x;
        }
    }

    namespace math {
        static constexpr int N = 6e3 + 7;

        ll qpow(ll x, ll a, int k = mod){
            ll base = x, rt = 1;
            while (a){
                if (a & 1) rt *= base, rt %= k;
                base *= base, base %= k;
                a >>= 1;
            }
            return rt;
        }

        int lowbit(int x){ return x & (-x);}

        ll lcm(ll a, ll b){
            ll g = __gcd(a, b);
            return a / g * b;
        }

        vector <ll> fac, ifac;

        ll inv(ll a, ll k = mod){
            if (a < 0) a += k;
            return qpow(a, k - 2, k);
        }

        void init_fac(ll k = mod, int n = N - 1){
            fac.resize(n + 1), ifac.resize(n + 1);
            fac[0] = fac[1] = 1;
            for (int i = 2; i <= n; i++) fac[i] = fac[i - 1] * i % k;
            ifac[n] = inv(fac[n], k);
            for (int i = n - 1; i >= 0; i--) ifac[i] = ifac[i + 1] * (i + 1) % k;
        }

        ll C(int n, int m){
            return fac[n] * ifac[m] % mod * ifac[n - m] % mod;
        }

        vector<int> prime, divi;
        bitset <N> np;

        void init_prime(int n = N - 1){
            // divi.resize(N);
            for (int i = 2; i <= n; i++) {
                if (!np[i]){
                    prime.push_back(i);
                    // divi[i] = i;
                }
                for (auto v : prime){
                    if (v * i > n) break;
                    np[v * i] = 1;
                    // divi[v * i] = v;
                    if (i % v == 0) break;
                }
            }
        }
    }

    namespace exstd {
        class DSU {
            public:
            
            vector <int> fa, siz;
            vector <vector <int>> e;

            DSU () : fa(vector (0, 0)), siz(vector (0, 0)), e(vector (0, vector (0, 0))) {}
            DSU (int n) {init (n);}

            int find (int x) {
                return fa[x] == x ? x : fa[x] = find(fa[x]);
            }

            bool merge (int v, int u) {
                auto fv = find(v), fu = find(u);
                if (fv == fu) return 0;
                if (siz[fv] > siz[fu]) swap (fv, fu);

                fa[fv] = fu, siz[fu] += siz[fv];
                // for (auto &x : e[fv]) e[fu].push_back(x);
                return 1;
            }

            protected:

            void init (int n) {
                fa.clear(), fa.resize (n + 1);
                iota (all(fa), 0);
                siz.clear(), siz.resize(n + 1);
                fill (all(siz), 1);

                // e.clear(), e.resize(n + 1);
                // for (int i = 1; i <= n; i++) e[i].clear(), e[i].push_back(i);
            }
        };

        class LCA {
            protected:

            void dfs (int v, int fa) {
                dep[v] = dep[fa] + 1;
                f[0][v] = fa;

                for (auto &u : e[v]) if (u != fa)
                    dfs (u, v);
            }

            public:

            static constexpr int N = 4e5 + 5;
            vector <vector <int>> f, e;
            vector <int> dep;
            int n, lim;
            LCA () : n(0), lim(0), f(vector (__lg(N) + 1, vector (N, 0))), e(vector (N, vector (0, 0))), dep(N, 0) {}
            LCA (int sz, int rt) {init (sz, rt);}
            
            int lca (int v, int u) {
                if (dep[v] > dep[u]) swap (v, u);

                for (int i = lim; i >= 0; i--) if (dep[u] - (1 << i) >= dep[v])
                    u = f[i][u];
                
                if (v == u) return v;
                for (int i = lim; i >= 0; i--) {
                    if (f[i][u] == 0) continue;
                    if (f[i][v] != f[i][u]) v = f[i][v], u = f[i][u];
                }
                
                return f[0][u];
            }

            void init (int sz, int rt) {
                n = sz, lim = __lg(sz);
                dep[rt] = 1; dfs (rt, 0);
                for (int i = 1; i <= lim; i++) for (int j = 1; j <= n; j++)
                    f[i][j] = f[i - 1][f[i - 1][j]];
            }
        };
    }
}

void init () {
    // K :: math :: init_fac ();
    // K :: math :: init_prime ();
}

void solve () {
    int n; cin >> n;
    vector a(n + 1, vector (n + 1, 0));
    for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++)
        cin >> a[i][j];
    
    for (int i = 1; i <= n; i++) for (int j = n - 1; j >= 1; j--)
        a[i][j] += a[i][j + 1];

    
}

int main () {
#ifndef ONLINE_JUDGE
    freopen("1.in", "r", stdin);
    freopen("my.out", "w", stdout);
#endif
    ios :: sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    // srand (time (0));

    init ();

    cout << setprecision(15) << fixed;
    cerr << setprecision(2) << fixed;

    int t = 1;
    cin >> t;
    while (t--) solve ();
}