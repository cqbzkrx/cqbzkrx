#include <bits/stdc++.h>
// #include <bits/extc++.h>
// using namespace __gnu_cxx;
// using namespace __gnu_pbds;
#define all(x) x.begin (), x.end ()
#define x first
#define y second
using namespace std;
using ll = long long;
using u64 = unsigned long long;
using u32 = unsigned int;
using db = double;
using i128 = __int128;
using u128 = unsigned __int128;
using i64 = long long;
const int inf = 1e9 + 7;
const ll INF = 1e18 + 7;
const db eps = 1e-6;
const int mod = 998244353;
const int N = 2e6 + 7;
const int M = 2e3 + 7;

template <class T>
void cmax (T &a, const T &b) {if (a < b) a = b;}
template <class T>
void cmin (T &a, const T &b) {if (a > b) a = b;}

ostream & operator << (ostream &os, const i128 &n) {
    if (n == 0) return os << 0;
    i128 x = (n > 0 ? n : -n);
    string s;
    while (x) {
        s += char ('0' + x % 10);
        x /= 10;
    }
    if (n < 0) s += '-';
    reverse (all(s));
    return os << s;
}

inline char get (void) {
    static char buf[1 << 20], *p1 = buf, *p2 = buf;
    if (p1 == p2) {
        p2 = (p1 = buf) + fread (buf, 1, 1 << 20, stdin);
        if (p1 == p2) return EOF;
    }
    return *p1++;
}

template <class T>
inline void read (T &x) {
    x = 0;
    static char c;
    bool minus = false;
    for (; ! (c >= '0' && c <= '9'); c = get ()) if (c == '-')
        minus = true;
    for (; c >= '0' && c <= '9'; x = x * 10 + c - '0', c = get ());
    if (minus) x = -x;
}

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

template <class T>
constexpr strong_ordering operator <=> (const vector <T> &lhs, const vector <T> &rhs) {
    int len = min (lhs.size (), rhs.size ());
    for (int i = 0; i < len; i++) if (lhs[i] != rhs[i])
        return lhs[i] <=> rhs[i];
    return lhs.size () < rhs.size ();
}

template <class T>
constexpr ostream & operator << (ostream &os, const pair <T, T> &p) {
    return os << "(" << p.x << ", " << p.y << ")";
}

template <class T>
constexpr ostream & operator << (ostream &os, const vector <T> &a) {
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
    };
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

m64 <mod> C (int n, int m) {
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
    for (int i = 1; i <= t; i++) {
        // cout << "Case "<< i << ": ";
        solve ();
    }
}
