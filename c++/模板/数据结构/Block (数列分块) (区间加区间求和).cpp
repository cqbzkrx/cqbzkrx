template <class T>
class block {
public:
    vector <T> a, sum, tag;
    vector <int> L, R, p;
    int n, sq;

    block (int _n = 0) {init (vector <T> (_n, T (0)));}
    block (const vector <T> &s) {init (s);}

    void init (const vector <T> &s) {
        n = s.size ();
        sq = sqrt (n + 0.5);
        a = s;
        L.resize (sq + 5);
        R.resize (sq + 5);
        tag.resize (sq + 5);
        sum.resize (sq + 5);
        p.resize (n + 1);

        for (int i = 0; i < (n + sq - 1) / sq; i++) {
            L[i] = min (i * sq, n - 1);
            R[i] = min ((i + 1) * sq - 1, n - 1);
        }

        for (int i = 0; i < (n + sq - 1) / sq; i++)
            for (int j = L[i]; j <= R[i]; j++) {
                p[j] = i;
                sum[i] += a[j];
            }
    }

    void modify (int l, int r, T c) {
        if (p[l] == p[r]) {
            for (int i = l; i <= r; i++) a[i] += c;
            sum[p[l]] += c * (r - l + 1);
        }
        else {
            for (int i = l; i <= R[p[l]]; i++) a[i] += c;
            sum[p[l]] += c * (R[p[l]] - l + 1);
            for (int i = r; i >= L[p[r]]; i--) a[i] += c;
            sum[p[r]] += c * (r - L[p[r]] + 1);
            for (int i = p[l] + 1; i < p[r]; i++) tag[i] += c;
        }
    }

    T qry (int l, int r) {
        T ans = 0;
        if (p[l] == p[r]) {
            for (int i = l; i <= r; i++) ans += a[i];
            ans += tag[p[l]] * (r - l + 1);
        }
        else {
            for (int i = l; i <= R[p[l]]; i++) ans += a[i];
            ans += tag[p[l]] * (R[p[l]] - l + 1);
            for (int i = r; i >= L[p[r]]; i--) ans += a[i];
            ans += tag[p[r]] * (r - L[p[r]] + 1);
            for (int i = p[l] + 1; i < p[r]; i++) ans += sum[i] + tag[i] * (R[i] - L[i] + 1);
        }
        return ans;
    }
};
