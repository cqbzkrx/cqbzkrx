template <class T = string>
class SA {
public:
    int n;
    vector <int> sa, rk, h;
    SA () {}
    SA (const T &s) {init (s);}

    void init (const T &s) {
        n = s.size ();
        sa.resize (n); iota (all(sa), 0);
        sort (all(sa), [&](int lhs, int rhs)  {return s[lhs] < s[rhs];});
        rk.resize (n); rk[sa[0]] = 0;
        for (int i = 1; i < n; i++) rk[sa[i]] = rk[sa[i - 1]] + (s[sa[i]] != s[sa[i - 1]]);

        int k = 1;
        vector tmp (0, 0), cnt (n, 0); tmp.reserve (n);
        while (rk[sa[n - 1]] != n - 1) {
            tmp.clear ();
            for (int i = 0; i < k; i++) tmp.push_back (n - k + i);
            for (auto v : sa) if (v >= k)
                tmp.push_back (v - k);

            fill (all(cnt), 0);
            for (int i = 0; i < n; i++) cnt[rk[i]]++;
            for (int i = 1; i < n; i++) cnt[i] += cnt[i - 1];
            for (int i = n - 1; i >= 0; i--) sa[--cnt[rk[tmp[i]]]] = tmp[i];
            swap (rk, tmp);

            rk[sa[0]] = 0;
            for (int i = 1; i < n; i++) 
                rk[sa[i]] = rk[sa[i - 1]] + (tmp[sa[i - 1]] < tmp[sa[i]] || sa[i - 1] + k == n || tmp[sa[i - 1] + k] < tmp[sa[i] + k]);
            k <<= 1;
        }

        h.resize (n - 1);
        for (int i = 0, j = 0; i < n; i++) {
            if (rk[i] == 0) j = 0;
            else {
                if (j > 0) j--;
                while (i + j < n && sa[rk[i] - 1] + j < n && s[i + j] == s[sa[rk[i] - 1] + j]) j++;
                h[rk[i] - 1] = j;
            }
        }
    }

    vector <vector <int>> st;
    int lim;

    void get_st () {
        lim = __lg (n);
        st.assign (lim + 1, vector (n - 1, 0));
        for (int i = 0; i < n - 1; i++) st[0][i] = h[i];
        for (int i = 1; i <= lim; i++) for (int j = 0; j < n - 1; j++) {
            if (j + (1 << i) > n - 1) break;
            st[i][j] = min (st[i - 1][j], st[i - 1][j + (1 << i - 1)]);
        }
    }

    int lcp (int i, int j) {
        if (i == n - 1 || j == n - 1 || i == j) return min (n - i, n - j);
        int l = rk[i], r = rk[j];
        if (l > r) swap (l, r);
        int lg = __lg (r - l);
        return min ({n - i, n - j, st[lg][l], st[lg][r - (1 << lg)]});
    }
};
