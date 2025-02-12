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
const db eps = 1e-6;

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

template <typename T>
struct Node {
    static constexpr T INVALID = -INF;
    T ans, lazy;
    Node () : ans(0), lazy(INVALID) {}
    Node (T as, T lzy = INVALID) {ans = as, lazy = lzy;}

    Node operator + (const Node &a) const {
        Node res;
        res.ans = a.ans + ans;
        return res;
    }
};

template <typename T, class info = Node <T>>
class sgt_lazy {
    static constexpr int rt = 1;
    static constexpr T INVALID = -INF;
    int n;
    
    vector <info> t;

    void build (const vector <T> &a, int p, int cl, int cr) {
        if (cl == cr) {t[p] = info (a[cl]); return ;}
        auto lc = p << 1, rc = lc | 1, mid = (cl + cr) >> 1;
        build (a, lc, cl, mid); build (a, rc, mid + 1, cr);
        t[p] = t[lc] + t[rc];
    }

    void modify (int l, int r, T x, int p, int cl, int cr) {
        if (cl > r || cr < l) return ;

        if (cl >= l && cr <= r) {
            merge (t[p], x, cr - cl + 1);
            return ;
        }

        push_down (p, cl, cr);
        auto lc = p << 1, rc = lc | 1, mid = (cl + cr) >> 1;
        modify (l, r, x, lc, cl, mid);
        modify (l, r, x, rc, mid + 1, cr);
        t[p] = t[lc] + t[rc];
    }

    info qry (int l, int r, int p, int cl, int cr) {
        if (cl > r || cr < l) return info (0);
        if (cl >= l && cr <= r) return t[p];
        push_down (p, cl, cr);
        auto lc = p << 1, rc = lc | 1, mid = (cl + cr) >> 1;
        return qry (l, r, lc, cl, mid) + qry (l, r, rc, mid + 1, cr);
    }

    void merge (info &s, T x, int len = 1) {
        s.ans += x * len;
        s.lazy = (s.lazy == INVALID ? x : s.lazy + x);
    }

    void push_down (int p, int cl, int cr) {
        if (cl == cr || t[p].lazy == INVALID) return ;
        auto lazy = t[p].lazy; t[p].lazy = INVALID;

        auto lc = p << 1, rc = lc | 1, mid = (cl + cr) >> 1;
        merge (t[lc], lazy, mid - cl + 1);
        merge (t[rc], lazy, cr - mid);
    }
    
public:
    sgt_lazy () : n(0), t(vector (0, info (0, INVALID))) {}
    sgt_lazy (const vector <T> &a) {init (a);}
    void modify (int l, int r, T x) {modify (l, r, x, rt, 0, n - 1);}
    info qry (int l, int r) {return qry (l, r, rt, 0, n - 1);}

    void init (const vector <T> &a) {
        n = a.size();
        t.resize (n << 2);
        build (a, rt, 0, n - 1);
    }
};


void init(){
    // init_prime();
    // init_fac();
}

void solve(){
    vector a(10, 0);
    sgt_lazy sgt(a);

    sgt.modify (0, 2, 1);
    sgt.modify (3, 9, 2);
    cout << sgt.qry (0, 3).ans << '\n';
}

int main(){
    // cerr << inv(2) << endl;
    // clock_t st = clock(), ed;
#ifndef ONLINE_JUDGE
    freopen("1.in", "r", stdin);
    freopen("my.out", "w", stdout);
#endif
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    // srand(114514);
    init();
    int t = 1;
    cout << setprecision(15) << fixed;
    cerr << setprecision(2) << fixed;
    // cin >> t;
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