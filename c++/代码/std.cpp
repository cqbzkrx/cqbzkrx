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
        template <typename T>
        struct Node {
            static constexpr T INVALID = -INF;
            T ans, l, r, lazy;
            Node () : ans(0), l(INVALID), r(INVALID), lazy(INVALID) {}
            Node (T as, T cl = INVALID, T cr = INVALID, T lzy = INVALID) {ans = as, l = cl, r = cl, lazy = lzy;}

            Node operator + (const Node &a) const {
                Node ret;
                ret.ans = a.ans + ans - (a.r == l);
                ret.l = a.l; ret.r = r;
                return ret;
            }
        };

        template <typename T, class info = Node <T>>
        class sgt_lazy {
        protected:
            static constexpr int rt = 1;
            static constexpr T INVALID = -INF;

            int n;
            vector <info> t;

            void build (const vector <T> &a, int p, int cl, int cr) {
                if (cl == cr) {t[p] = info (1, a[cl], a[cl]); return ;}
                auto lc = p << 1, rc = lc | 1, mid = (cl + cr) >> 1;
                build (a, lc, cl, mid); build (a, rc, mid + 1, cr);
                t[p] = t[lc] + t[rc];
            }

            void modify (int l, int r, T x, int p, int cl, int cr) {
                if (cl > r || cr < l) return ;
                if (cl >= l && cr <= r) {merge (t[p], x, cr - cl + 1); return ;}
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
                s.ans = 1;
                s.lazy = s.l = s.r = x;
            }

            void push_down (int p, int cl, int cr) {
                if (cl == cr || t[p].lazy == INVALID) return ;
                auto lazy = t[p].lazy; t[p].lazy = INVALID;

                auto lc = p << 1, rc = lc | 1, mid = (cl + cr) >> 1;
                merge (t[lc], lazy, mid - cl + 1);
                merge (t[rc], lazy, cr - mid);
            }

        public:
            sgt_lazy () : n(0), t(vector (0, info (0, 0, 0))) {}
            sgt_lazy (const vector <T> &a) {init(a);}
            
            void modify (int l, int r, T x) {modify (l, r, x, rt, 0, n - 1);}
            info qry (int l, int r) {return qry (l, r, rt, 0, n - 1);}

            void init (const vector <T> &a) {
                n = a.size();
                t.resize(n << 2);
                build (a, rt, 0, n - 1);
            }
        };

        template <typename T>
        class HPD {
        public:
            vector <int> dep, dfn, top, son, f, siz;
            vector <T> s;
            vector <vector <int>> e;
            sgt_lazy <T> sgt;
            int n, cnt;

            HPD () : n(0), cnt(0), dep(vector (0, 0)), dfn(vector (0, 0)), top(vector (0, 0)), son(vector (0, 0)), 
                f(vector (0, 0)), siz(vector (0, 0)), s(vector (0, T(0))), e(vector (0, vector (0, 0))) {}
            HPD (int sz, int rt, const vector <vector <int>> &a, const vector <T> &c)  {init (sz, rt, a, c);}

            void dfs1 (int v, int fa) {
                dep[v] = dep[fa] + 1; f[v] = fa;
                siz[v] = 1; son[v] = -1;
                
                int maxn = 0;
                for (auto &u : e[v]) if (u != fa) {
                    dfs1 (u, v);
                    siz[v] += siz[u];
                    if (maxn < siz[u]) maxn = siz[u], son[v] = u;
                }
            }

            void dfs2 (int v, int head) {
                dfn[v] = ++cnt;
                top[v] = head;
                if (son[v] != -1) dfs2 (son[v], head);

                for (auto &u : e[v]) if (u != son[v] && u != f[v])
                    dfs2(u, u);
            }

            void init (int sz, int rt, const vector <vector <int>> &a, const vector <T> &c) {
                e = a, n = sz, cnt = 0;
                dep = dfn = top = son = f = siz = vector (n + 1, 0);
                s.resize(n + 1);

                dep[rt] = 1;
                dfs1(rt, 0);
                dfs2(rt, rt);

                for (int i = 1; i <= n; i++) s[dfn[i]] = c[i];
                for (int i = 1; i <= n; i++) cerr << dfn[i] << ' ' << f[i] << ' ' << top[i] << ' ' << siz[i] << '\n';
                sgt.init (s);
            }

            void modify (int v, int u, T x) {
                while (top[v] != top[u]) {
                    if (dep[top[v]] > dep[top[u]]) sgt.modify (dfn[top[u]], dfn[u], x), u = f[top[u]];
                    else sgt.modify (dfn[top[v]], dfn[v], x), v = f[top[v]];
                }

                if (dep[v] > dep[u]) swap (v, u);
                sgt.modify (dfn[v], dfn[u], x);
            }

            T qry (int v, int u) {
                Node <T> ans;
                while (top[v] != top[u]) {
                    if (dep[top[v]] > dep[top[u]]) ans = ans + sgt.qry (dfn[top[u]], dfn[u]), u = f[top[u]];
                    else ans = ans + sgt.qry (dfn[top[v]], dfn[v]), v = f[top[v]];
                }

                if (dep[v] > dep[u]) swap (v, u);
                ans = ans + sgt.qry (dfn[v], dfn[u]);
                return ans.ans;
            }
        };
    }
}

using namespace K;
// using namespace Hash;
// using namespace math;
using namespace exstd;

void init () {
    // init_fac ();
    // init_prime ();
}

void solve () {
    int n, m; cin >> n >> m;
    vector a(n + 1, 0ll);
    for (int i = 1; i <= n; i++) cin >> a[i];

    vector e(n + 1, vector (0, 0));
    for (int i = 1; i < n; i++) {
        int v, u; cin >> v >> u;
        e[v].push_back (u);
        e[u].push_back (v);
    }

    HPD <ll> K(n, 1, e, a);

    for (int i = 1; i <= m; i++) {
        char c; cin >> c;
        if (c == 'Q') {
            int v, u; cin >> v >> u;
            cout << K.qry (v, u) << '\n';
        }
        else {
            int v, u; ll x; cin >> v >> u >> x;
            K.modify (v, u, x);
        }
    }
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
    while (t--) solve ();
}