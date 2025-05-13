template <typename T = ll>
class BIT {
public:
    int lowbit (int i) {return (i & -i);}

    int n;
    vector <T> t;
    
    BIT (int sz = 0) : n (sz), t (sz + 1) {}
    BIT (const vector <T> &a) : BIT ((int) a.size ()) {
        for (int i = 1; i <= n; i++) modify (i, a[i - 1]);
    }

    void modify (int i, T x) {
        for (; i <= n; i += lowbit (i)) t[i] += x;
    }

    T qry (int r) {
        T ans = 0;
        for (; r > 0; r -= lowbit (r)) ans += t[r];
        return ans;
    }
    
    T qry (int l, int r) {
        return qry (r) - qry (l - 1);
    }
};
