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
            void dfs (int v, int fa) {
                dep[v] = dep[fa] + 1;
                f[0][v] = fa;

                for (auto &u : e[v]) if (u != fa)
                    dfs (u, v);
            }

            public:

            static constexpr int N = 4e5 + 5;
            int n, lim;
            vector <vector <int>> f, e;
            vector <int> dep;
            
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

        template <typename T>
        class st {
            protected:

            static constexpr int N = 2e5 + 7;
            vector <vector <T>> f;
            int n, lim;

            public:

            void init (const vector <T> &a) {
                n = a.size(), lim = __lg(n) + 1;
                for (int i = 0; i < n; i++) f[0][i] = a[i];
                for (int i = 1; i < lim; i++) for (int j = 0; j < n; j++) {
                    if (j + (1 << i) > n) break;
                    f[i][j] = max (f[i - 1][j], f[i - 1][j + (1 << (i - 1))]);
                }
            }

            st () : n(0), lim(0), f(vector (__lg(N) + 1, vector (N, 0))) {}
            st (const vector <T> &a) {init (a);}

            T qry (int l, int r) {
                int lg = __lg (r - l + 1);
                return max(f[lg][l], f[lg][r - (1 << lg) + 1]);
            }
        };

        class KMP {
            public:

            int n;
            vector <int> nxt;

            KMP () : n(0), nxt(vector (0, 0)) {}
            KMP (const string &s) {get_nxt (s);}

            bool kmp (const string &a, const string &b, const vector <int> &nxt) {
                int i = 0, j = 0;
                while (i < (int) a.size()) {
                    if (j == -1 || a[i] == b[i]) {
                        i++, j++;
                        if (j == (int) b.size()) return 1;
                    }
                    else j = nxt[j];
                }
                return 0;
            }

            void get_nxt (const string &s) {
                n = s.size();
                nxt.resize(n + 1);

                nxt[0] = -1;
                int i = 0, j = -1;
                while (i < n) {
                    if (j == -1 || s[i] == s[j]) nxt[++i] = ++j;
                    else j = nxt[j];
                }
            }
        };

        class LCA_tarjan {
            class DSU_LCA_tarjan {
                public:

                vector <int> fa;

                void init (int n) {
                    fa.resize(n + 1);
                    iota (all(fa), 0);
                }

                int find (int x) {
                    return fa[x] == x ? x : fa[x] = find(fa[x]);
                }

                void merge (int v, int u) {
                    auto fv = find(v), fu = find(u);
                    if (fv == fu) return ;
                    fa[fv] = fu;
                }

                DSU_LCA_tarjan () : fa(vector (0, 0)) {}
                DSU_LCA_tarjan (int n) {init (n);}
            };

            public:

            vector <vector <int>> e;
            vector <vector <pair <int, int>>> eq;
            vector <int> vis, ans;
            int n, q;
            DSU_LCA_tarjan dsu;
            
            LCA_tarjan () : n(0), q(0) {}
            LCA_tarjan (int sz, int k) {init (sz, k);}

            void dfs (int v, int fa) {
                for (auto &u : e[v]) if (u != fa) {
                    dfs (u, v);
                    dsu.merge (u, v);
                }

                vis[v] = 1;

                for (auto &[u, idx] : eq[v]) if (vis[u])
                    ans[idx] = dsu.find (u);
            }

            void init (int sz, int k) {
                n = sz, q = k;
                dsu.init (sz);
                vis.resize(sz + 1);
                ans.resize(k);
                eq.resize(sz + 1);
                e.resize(sz + 1);
            }
        };

        template <typename T>
        class sgt_lazy {
            static constexpr int rt = 1;
            static constexpr T INVALID = -INF;
            int n;

            struct Node {
                T ans, lazy;
                Node () : ans(0), lazy(INVALID) {}
                Node (T as, T inv = INVALID) {ans = as, lazy = inv;}

                Node operator + (const Node &a) const {
                    Node res;
                    res.ans = a.ans + ans;
                    return res;
                }
            };
            vector <Node> t;

            void build (const vector <T> &a, int p, int cl, int cr) {
                if (cl == cr) {t[p] = Node (a[cl]); return ;}
                auto lc = p << 1, rc = lc | 1, mid = (cl + cr) >> 1;
                build (a, lc, cl, mid); build (a, rc, mid + 1, cr);
                t[p] = t[lc] + t[rc];
            }

            void init (const vector <T> &a) {
                n = a.size();
                t.resize (n << 2);
                build (a, rt, 0, n - 1);
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

            Node qry (int l, int r, int p, int cl, int cr) {
                if (cl > r || cr < l) return Node (0);
                if (cl >= l && cr <= r) return t[p];
                push_down (p, cl, cr);
                auto lc = p << 1, rc = lc | 1, mid = (cl + cr) >> 1;
                return qry (l, r, lc, cl, mid) + qry (l, r, rc, mid + 1, cr);
            }

            void merge (Node &s, T x, int len = 1) {
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

            sgt_lazy () : n(0), t(vector (0, Node (0, INVALID))) {}
            sgt_lazy (const vector <T> &a) {init (a);}
            void modify (int l, int r, T x) {modify (l, r, x, rt, 0, n - 1);}
            Node qry (int l, int r) {return qry (l, r, rt, 0, n - 1);}
        };
    }
}

// using namespace K;
// using namespace Hash;
// using namespace math;
// using namespace exstd;

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
    cin.tie(0), cout.tie(0);
    // srand (time (0));

    init ();

    cout << setprecision(15) << fixed;
    cerr << setprecision(2) << fixed;

    int t = 1;
    // cin >> t;
    while (t--) solve ();
}
