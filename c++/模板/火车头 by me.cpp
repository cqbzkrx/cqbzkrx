#include <bits/stdc++.h>
#define all(x) x.begin (), x.end ()
#define x first
#define y second
using namespace std;
using db = double;
using i64 = long long;
using u64 = unsigned long long;
using i32 = int;
using u32 = unsigned int;
using i128 = __int128;
using u128 = unsigned __int128;
const int inf = 1e9 + 7;
const ll INF = 1e17 + 7;
const db eps = 1e-6;
const int mod = 1e9 + 7;
const int N = 2e6 + 7;
const int M = 2e3 + 7;

namespace K {
    namespace Hash {
        struct custom_hash{
            static uint64_t splitmix64 (uint64_t x){
                x += 0x9e3779b97f4a7c15;
                x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
                x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
                return (x ^ (x >> 31));
            }

            size_t operator () (uint64_t x) const{
                static const uint64_t FIXED_RANDOM = chrono::steady_clock::now ().time_since_epoch ().count ();
                return splitmix64 (x + FIXED_RANDOM);
            }
        };
    }

    namespace input {
        inline char get (void){
            static char buf[1 << 20], *p1 = buf, *p2 = buf;
            if (p1 == p2){
                p2 = (p1 = buf) + fread (buf, 1, 1 << 20, stdin);
                if (p1 == p2) return EOF;
            }
            return *p1++;
        }

        template <typename T>
        inline void read (T &x){
            x = 0;
            static char c;
            bool minus = false;
            for (; ! (c >= '0' && c <= '9'); c = get ()) if (c == '-')
                minus = true;
            for (; c >= '0' && c <= '9'; x = x * 10 + c - '0', c = get ());
            if (minus) x = -x;
        }
    }

    namespace math {
        ll qpow (ll x, ll a, int k = mod){
            ll base = x % k, rt = 1;
            while (a){
                if (a & 1) rt *= base, rt %= k;
                base *= base, base %= k;
                a >>= 1;
            }
            return rt;
        }

        int lowbit (int x){ return x & (-x);}

        ll lcm (ll a, ll b){
            ll g = __gcd (a, b);
            return a / g * b;
        }

        vector <ll> fac, ifac;

        ll inv (ll a, ll k = mod){
            if (a < 0) a += k;
            return qpow (a, k - 2, k);
        }

        void init_fac (ll k = mod, int n = N - 1){
            fac.resize (n + 1), ifac.resize (n + 1);
            fac[0] = fac[1] = 1;
            for (int i = 2; i <= n; i++) fac[i] = fac[i - 1] * i % k;
            ifac[n] = inv (fac[n], k);
            for (int i = n - 1; i >= 0; i--) ifac[i] = ifac[i + 1] * (i + 1) % k;
        }

        ll C (int n, int m){
            return fac[n] * ifac[m] % mod * ifac[n - m] % mod;
        }

        vector<int> prime, divi;
        bitset <N> np;

        void init_prime (int n = N - 1){
            // divi.resize (N);
            for (int i = 2; i <= n; i++) {
                if (!np[i]){
                    prime.push_back (i);
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

    
}

// using namespace K;
// using namespace Hash;
// using namespace input;
// using namespace math;

void init () {
    // init_fac ();
    // init_prime ();
}

void solve () {
    
}

int main () {
#ifndef ONLINE_JUDGE
    freopen ("1.in", "r", stdin);
    freopen ("my.out", "w", stdout);
#endif
    ios :: sync_with_stdio (0);
    // ios_base :: sync_with_stdio (0);
    cin.tie (0), cout.tie (0);
    // srand (time (0));

    init ();

    cout << setprecision (15) << fixed;
    cerr << setprecision (2) << fixed;

    int t = 1;
    // cin >> t;
    // read (t);
    while (t--) solve ();
}
