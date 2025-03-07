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
const int N = 1e6 + 7;
const int M = 2e3 + 7;

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

        template <typename T = ll>
        class hash_string {
        public:
            static constexpr T mod = 998244353;
            static constexpr T B = 131;

            string s;
            vector <T> b, h;
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
            
            T qry (int l, int r) {
                return (h[r] - h[l - 1] * b[r - l + 1] % mod + mod) % mod;
            }

            bool same (int l1, int r1, int l2, int r2) {
                return qry (l1, r1) == qry (l2, r2);
            }
        };
    }

    namespace input {
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
        namespace segment_tree {
            static constexpr ll INVALID = -INF;

            template <typename T>
            struct Node {
                T sum, lazy;
                Node (T _sum = 0, T _lazy = INVALID) : sum (_sum), lazy (_lazy) {}

                Node operator + (const Node &a) const {
                    Node ret;
                    ret.sum = sum + a.sum;
                    return ret;
                };
            };

            template <typename T, class info = Node <T>>
            class segtree_lazy {
                static constexpr int rt = 1;

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
                    if (cl >= l && cr <= r) {get (t[p], x, cr - cl + 1); return ;}
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

                void get (info &s, T x, int len = 1) {
                    s.sum += x * len;
                    s.lazy = (s.lazy == INVALID ? 0 : s.lazy) + x;
                }

                void push_down (int p, int cl, int cr) {
                    if (cl == cr || t[p].lazy == INVALID) return ;
                    auto lazy = t[p].lazy; t[p].lazy = INVALID;

                    auto lc = p << 1, rc = lc | 1, mid = (cl + cr) >> 1;
                    get (t[lc], lazy, mid - cl + 1);
                    get (t[rc], lazy, cr - mid);
                }

            public:
                segtree_lazy () : n(0) {}
                segtree_lazy (const vector <T> &a) {init (a);}
                void modify (int l, int r, T x) {modify (l, r, x, rt, 0, n - 1);}
                void modify (int p, T x) {modify (p, p, x, rt, 0, n - 1);}
                info qry (int l, int r) {return qry (l, r, rt, 0, n - 1);}
                info qry (int x) {return qry (x, x, rt, 0, n - 1);}

                void init (const vector <T> &a) {
                    n = a.size ();
                    t.resize (n << 2);
                    build (a, rt, 0, n - 1);
                }
            };
        }

        class LCA {
        public:
            static constexpr int N = 2e5 + 7;
            vector <vector <int>> f, e;
            vector <int> dep;
            int n, lim;

            LCA () : n(0), lim(0) {clear ();}
            LCA (int sz, int rt, const vector <vector <int>> &a) : n(sz), lim(__lg(sz)), e(a)
                {clear (); init (sz, rt);}
            
            void dfs (int v, int fa) {
                dep[v] = dep[fa] + 1;
                f[0][v] = fa;
                for (auto u : e[v]) if (u != fa)
                    dfs (u, v);
            }

            void init (int sz, int rt) {
                dfs (rt, 0);

                for (int i = 1; i <= lim; i++) for (int j = 1; j <= n; j++)
                    f[i][j] = f[i - 1][f[i - 1][j]];
            }

            void clear () {
                f = vector (__lg(N) + 1, vector (N, 0));
                dep = vector (N, 0);
            }

            int lca (int v, int u) {
                if (dep[v] > dep[u]) swap (v, u);
                
                for (int i = lim; i >= 0; i--) if (dep[u] - (1 << i) >= dep[v])
                    u = f[i][u];
                    
                if (v == u) return v;
                for (int i = lim; i >= 0; i--) {
                    if (f[i][u] == 0) continue;
                    if (f[i][u] != f[i][v]) v = f[i][v], u = f[i][u];
                }

                return f[0][u];
            }

            int len (int v, int u) {
                return dep[v] + dep[u] - dep[lca (v, u)] * 2;
            }
        };

        class DSU {
        public:
            vector <int> fa, siz;

            DSU () {}
            DSU (int n) {init (n);}

            void init (int n) {
                fa.resize (n + 1);
                iota (all(fa), 0);
                siz.resize (n + 1);
                fill (all(siz), 1);
            }

            int find (int x) {
                return fa[x] == x ? x : fa[x] = find (fa[x]);
            }

            bool merge (int v, int u) {
                auto fv = find (v), fu = find (u);
                if (fv == fu) return 0;
                if (siz[fv] > siz[fu]) swap (fv, fu);
                siz[fu] += siz[fv]; fa[fv] = fu;
                return 1;
            }

            bool same (int v, int u) {
                auto fv = find (v), fu = find (u);
                return fv == fu;
            }
        };
        
        class KMP {
        public:
            vector <int> nxt;
            string s;

            KMP () {}
            KMP (const string &c) : s(c) {get_nxt (c);}

            void get_nxt (const string &c) {
                nxt.resize (c.size() + 1);
                nxt[0] = -1;

                int i = 0, j = -1;
                while (i < (int) c.size()) {
                    if (j == -1 || c[i] == c[j]) {
                        i++, j++;
                        nxt[i] = j;
                    }
                    else j = nxt[j];
                }
            }

            pair <int, int> kmp (const string &c) { // c中找s; first -> T/F, second -> idx
                int i = 0, j = 0;
                while (i < (int) c.size()) {
                    if (j == -1 || c[i] == s[j]) {
                        i++, j++;
                        if (j == (int) s.size()) return {1, i - s.size()};
                    }
                    else j = nxt[j];
                }
                return {-1, -1};
            }
        };
    }
}

// using namespace K;
// using namespace Hash;
// using namespace input;
// using namespace math;
// using namespace exstd;
// using namespace segment_tree;

void init () {
    // init_fac ();
    // init_prime ();
}

void solve () {

}

int main () {
#ifndef ONLINE_JUDGE
    freopen("1.in", "r", stdin);
    freopen("my.out", "w", stdout);
#endif
    ios :: sync_with_stdio(0);
    // ios_base :: sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    // srand (time (0));

    init ();

    cout << setprecision(15) << fixed;
    cerr << setprecision(2) << fixed;

    int t = 1;
    // cin >> t;
    // read (t);
    while (t--) solve ();
    // cout << format ("");
}
