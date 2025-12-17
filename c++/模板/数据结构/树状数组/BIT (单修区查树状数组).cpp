template <typename T = ll>
class BIT {
public:
    int lowbit (int i) {return (i & -i);}

    vector <T> t;
    
    BIT (int sz = 0) : t (sz + 10) {}
    BIT (const vector <T> &a) : BIT ((int) a.size ()) {
        for (int i = 0; i < a.size (); i++) modify (i, a[i]);
    }

    void modify (int x, T v) {
        x++;
        while (x < t.size ()) {
            t[x] += v;
            x += lowbit(x);
        }
    }

    T qry (int x) {
        x++;
        T ans = 0;
        while (x > 0) {
            ans += t[x];
            x -= lowbit(x);
        }
        return ans + t[0];
    }
    
    T qry (int l, int r) {
        return qry (r) - qry (l - 1);
    }
};
