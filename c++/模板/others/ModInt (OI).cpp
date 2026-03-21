template <u64 P>
struct m64 {
private:
    u64 x;

public:
    m64 () : x (0) {}
    template <typename T>
    m64 (T _x) {
        if (_x >= 0) x = _x % mod ();
        else x = _x % mod () + mod ();
    }

    inline static u64 mod () {
        return P;
    }

    inline u64 val () const {
        return x;
    }

    m64 inv () const {
        return qpow (*this, mod () - 2);
    }

    m64 & operator *= (const m64 &rhs) & {
        x = u64 (x) * rhs.val () % mod ();
        return *this;
    }

    m64 & operator += (const m64 &rhs) & {
        x += rhs.val ();
        if (x >= mod ()) x -= mod ();
        return *this;
    }

    m64 & operator -= (const m64 &rhs) & {
        x -= rhs.val ();
        if (x >= mod ()) x += mod ();
        return *this;
    }

    m64 & operator /= (const m64 &rhs) & {
        return *this *= rhs.inv ();
    }

    friend m64 operator * (m64 lhs, const m64 &rhs) {
        lhs *= rhs;
        return lhs;
    }

    friend m64 operator + (m64 lhs, const m64 &rhs) {
        lhs += rhs;
        return lhs;
    }

    friend m64 operator - (m64 lhs, const m64 &rhs) {
        lhs -= rhs;
        return lhs;
    }

    friend m64 operator / (m64 lhs, const m64 &rhs) {
        lhs /= rhs;
        return lhs;
    }

    friend istream & operator >> (istream &is, m64 &a) {
        ll v; is >> v;
        a = v;
        return is;
    }

    friend ostream & operator << (ostream &os, const m64 &a) {
        return os << a.val ();
    }
};
