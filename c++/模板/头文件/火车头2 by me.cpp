#include <bits/stdc++.h>
#define all(x) x.begin (), x.end ()
#define x first
#define y second
using namespace std;
using ll = long long;
using db = double;
using u32 = unsigned int;
using i128 = __int128;
using u64 = unsigned long long;
using u128 = unsigned __int128;
const int inf = 1e9 + 7;
const ll INF = (ll) (1e18) + 7;
const int mod = 1e9 + 7;
const ll N = 2e5 + 7;
const ll M = 1e3 + 7;

template <typename T>
inline void cmax (T &a, const T &b) {if (a < b) a = b;}
template <typename T>
inline void cmin (T &a, const T &b) {if (a > b) a = b;}

struct custom_hash {
    static uint64_t splitmix64 (uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return (x ^ (x >> 31));
    }

    size_t operator () (uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now ().time_since_epoch ().count ();
        return splitmix64 (x + FIXED_RANDOM);
    }
};

inline char get (void) {
    static char buf[1 << 20], *p1 = buf, *p2 = buf;
    if (p1 == p2) {
        p2 = (p1 = buf) + fread (buf, 1, 1 << 20, stdin);
        if (p1 == p2) return EOF;
    }
    return *p1++;
}

template <typename T>
inline void read (T &x) {
    x = 0;
    static char c;
    bool minus = false;
    for (; ! (c >= '0' && c <= '9'); c = get ()) if (c == '-')
        minus = true;
    for (; c >= '0' && c <= '9'; x = x * 10 + c - '0', c = get ());
    if (minus) x = -x;
}

ostream & operator << (ostream &os, const i128 &n) {
    if (n == 0) return os << 0;
    i128 x = (n < 0 ? -n : n);
    string ans;
    while (x) {
        ans += (char) ('0' + x % 10);
        x /= 10;
    }
    if (n < 0) ans += '-';
    reverse (all(ans));
    return os << ans;
}

i128 sqrt (i128 n) {
    i128 l = 0, r = 1e16, ans = 0;
    while (l <= r) {
        i128 mid = (l + r) >> 1;
        if (mid * mid <= n) ans = mid, l = mid + 1;
        else r = mid - 1;
    }
    return ans;
}

i128 gcd (i128 a, i128 b) {
    while (b) {
        a %= b;
        swap (a, b);
    }
    return a;
}

template <class T>
constexpr vector <T> operator += (vector <T> &lhs, const vector <T> &rhs) {
    lhs.insert (lhs.end (), all(rhs));
    return lhs;
}

template <class T>
constexpr vector <T> operator + (vector <T> lhs, const vector <T> &rhs) {
    lhs += rhs;
    return lhs;
}

template <typename T, typename U>
ostream & operator << (ostream &os, const pair <T, U> &a) {
    os << '(' << a.x << ", " << a.y << ')';
    return os;
}

template <typename T>
ostream & operator << (ostream &os, const vector <T> &a) {
    for (auto &v : a) os << v << " ";
    return os;
}

namespace ModInt {
    template <class T>
    constexpr T qpow (T a, ll b, T res = 1) {
        while (b) {
            if (b & 1) res *= a;
            a *= a;
            b >>= 1;
        }
        return res;
    }

    template <u32 P>
    constexpr u32 mul_mod (u32 a, u32 b) {
        return u64 (a) * b % P;
    }

    template <u64 P>
    constexpr u64 mul_mod (u64 a, u64 b) {
        u64 res = a * b - u64 (1.L * a * b / P - 0.5L) * P;
        res %= P;
        return res;
    }

    template <unsigned_integral U, U P>
    struct mod_int {
    private:
        U x;

    public:
        constexpr mod_int () : x (0) {}
        template <unsigned_integral T>
        constexpr mod_int (T _x) : x (_x % mod ()) {}
        template <signed_integral T>
        constexpr mod_int (T _x) {
            using S = make_signed_t <U>;
            S v = _x % S (mod ());
            if (v < 0) v += mod ();
            x = v;
        }

        constexpr static U mod () {
            return P;
        }

        constexpr U val () const {
            return x;
        }

        constexpr mod_int operator - () const {
            mod_int res;
            res.x = (x == 0 ? 0 : mod () - x);
            return res;
        }

        constexpr mod_int inv () const {
            return qpow (*this, mod () - 2);
        }

        constexpr mod_int &operator *= (const mod_int &rhs) & {
            x = mul_mod <mod ()> (x, rhs.val ());
            return *this;
        }

        constexpr mod_int &operator += (const mod_int &rhs) & {
            x += rhs.val ();
            if (x >= mod ()) x -= mod ();
            return *this;
        }

        constexpr mod_int &operator -= (const mod_int &rhs) & {
            x -= rhs.val ();
            if (x >= mod ()) x += mod ();
            return *this;
        }

        constexpr mod_int &operator /= (const mod_int &rhs) & {
            return *this *= rhs.inv ();
        }

        friend constexpr mod_int operator * (mod_int lhs, const mod_int &rhs) {
            lhs *= rhs;
            return lhs;
        }

        friend constexpr mod_int operator + (mod_int lhs, const mod_int &rhs) {
            lhs += rhs;
            return lhs;
        }

        friend constexpr mod_int operator - (mod_int lhs, const mod_int &rhs) {
            lhs -= rhs;
            return lhs;
        }

        friend constexpr mod_int operator / (mod_int lhs, const mod_int &rhs) {
            lhs /= rhs;
            return lhs;
        }

        friend constexpr istream &operator >> (istream &is, mod_int &a) {
            ll i;
            is >> i;
            a = i;
            return is;
        }

        friend constexpr ostream &operator << (ostream &os, const mod_int &a) {
            return os << a.val ();
        }

        friend constexpr strong_ordering operator <=> (const mod_int &lhs, const mod_int &rhs) {
            return lhs.val () <=> rhs.val ();
        }

        friend constexpr bool operator == (const mod_int &lhs, const U &rhs) {
            if (rhs < 0) return lhs.val () == (rhs % mod () + mod ()) % mod ();
            return lhs.val () == rhs % mod ();
        }
    };
}

inline ll lcm (ll a, ll b) {
    return a / gcd (a, b) * b;
}

template <u32 P>
using m32 = ModInt :: mod_int <u32, P>;
template <u64 P>
using m64 = ModInt :: mod_int <u64, P>;

vector <m64 <mod>> fac, ifac;

void init_fac () {
    fac.resize (N + 1), ifac.resize (N + 1);
    fac[0] = ifac[0] = 1;
    for (int i = 1; i <= N; i++) fac[i] = fac[i - 1] * i;
    ifac[N] = fac[N].inv ();
    for (int i = N - 1; i >= 1; i--) ifac[i] = ifac[i + 1] * (i + 1);
};

inline m64 <mod> C (int n, int m) {
    if (m > n || m < 0) return 0;
    return fac[n] * ifac[m] * ifac[n - m];
}

vector <int> prime, divi, np;

void init_prime () {
    np.resize (N + 1);
    // divi.resize (N + 1);
    np[1] = np[0] = 1;
    for (int i = 2; i <= N; i++) {
        if (!np[i]) {
            prime.push_back (i);
            // divi[i] = i;
        }
        for (auto v : prime) {
            if (v * i > N) break;
            np[v * i] = 1;
            // divi[v * i] = v;
            if (i % v == 0) break;
        }
    }
}

// ifstream fin ("1.in", ios_base :: in);
// ofstream fout ("my.out", ios_base :: out);

void init () {
    
}

void solve () {
    
}

int main () {
#ifndef ONLINE_JUDGE
    freopen ("1.in", "r", stdin);
    freopen ("my.out", "w", stdout);
#endif
    ios :: sync_with_stdio (0);
    cin.tie (0), cout.tie (0);

#ifdef TIME
    // clock_t st = clock(), ed;
    auto st = chrono :: high_resolution_clock :: now ();
#endif

    init ();

    int t = 1;
    // cin >> t;
    while (t--) solve ();

#ifdef TIME
    // ed = clock ();
    // db endtime = (db) (ed - st) / CLOCKS_PER_SEC;
    auto ed = chrono :: high_resolution_clock :: now ();
    db endtime = chrono :: duration <db, milli> (ed - st).count ();
    cerr << "Total time: " << endtime << " milliseconds" << endl;
    // system ("pause");
#endif
    return 0;
}
