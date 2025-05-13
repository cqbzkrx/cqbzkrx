namespace BIT {
int lowbit (int i) {return (i & -i);}

template <typename T = ll>
class _BIT {
public:
    int n;
    vector <T> t;
    
    _BIT (int sz = 0) : n (sz), t (sz + 1) {}
    _BIT (const vector <T> &a) : _BIT ((int) a.size ()) {
        for (int i = 1; i <= n; i++) modify (i, a[i - 1]), modify (i + 1, -a[i - 1]);
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

template <typename T = ll>
class BIT {
public:
    _BIT <T> bit0, bit1;
    vector <T> sum;

    BIT (int sz = 0) : bit0 (sz + 1), bit1 (sz + 1) {}
    BIT (const vector <T> &a) : sum (a.size () + 1), bit0 ((int) a.size () + 1), bit1 ((int) a.size () + 1) {
        for (int i = 1; i <= (int) a.size (); i++) sum[i] = sum[i - 1] + a[i - 1];
    }

    void modify (int l, int r, T x) {
        if (l > r) return ;
        l++, r++;
        bit0.modify (l, x);
        bit0.modify (r + 1, -x);
        bit1.modify (l, x * l);
        bit1.modify (r + 1, -x * (r + 1));
    }

    T qry (int l, int r) {
        l++, r++;
        auto calc = [&] (int r) -> T {
            return sum[r] + (r + 1) * bit0.qry (r) - bit1.qry (r);
        };

        return calc (r) - calc (l - 1);
    }

    T qry (int l) {return qry (l, l);}
    void modify (int l, T x) {modify (l, l, x);}
};
}
