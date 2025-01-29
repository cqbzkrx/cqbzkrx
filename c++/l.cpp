#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
using namespace std;
using ll = long long;
using db = double;
using ull = unsigned long long;
const int inf = 1e9 + 7;
const ll INF = 1e18 + 7;
const int mod = 1e9 + 7;
const int N = 3e6 + 5;
const int M = 1e6 + 100;
const db eps = 1e-8;

int inv1, inv2;

template<typename T>
void add(T& x, const T& y) {if((x += y) >= mod) x -= mod;}
template<typename T>
void dec(T& x, const T& y) {if((x -= y) < 0) x += mod;}
template<typename T>
void cmax(T& x, const T& y) {if(y > x) x = y;}
template<typename T>
void cmin(T& x, const T& y) {if(y < x) x = y;}

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

int lowbit(int x){ return x & (-x);}

ll lcm(ll a, ll b){
    ll g = __gcd(a, b);
    return a / g * b;
}

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
// unordered_map<int, int, custom_hash> mp;

ll qpow(ll x, ll a, int k = mod){
    ll base = x, rt = 1;
    while (a){
        if (a & 1) rt *= base, rt %= k;
        base *= base, base %= k;
        a >>= 1;
    }
    return rt;
}

vector<ll> fac, ifac;

ll inv(ll a, int k = mod){
    if (a < 0) a += k;
    return qpow(a, k - 2, k);
}

void init_fac(int n = N - 1, int k = mod){
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

void init(){
    // init_prime();
    // init_fac();
}

void solve(){
    
}

int main(){
    // cerr << inv(2) << endl;
    // clock_t st = clock(), ed;
// #ifndef ONLINE_JUDGE
//     freopen("1.in", "r", stdin);
//     freopen("my.out", "w", stdout);
// #endif
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    // srand(114514);
    init();
    int t = 1;
    cout << setprecision(15) << fixed;
    cerr << setprecision(2) << fixed;
    cin >> t;
    // read(t);
    while(t--) {
        solve();
        // assert(a == b);
    }
    // ed = clock();
    // double endtime=(double)(ed-st)/CLOCKS_PER_SEC;
    // cout<<"Total time:"<<endtime<<endl;
    // system("pause");
    return 0;
}