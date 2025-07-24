namespace ModInt {
    template <class T>
    constexpr T power (T a, ll b, T res = 1) {
        while (b) {
            if (b & 1) res *= a;
            a *= a;
            b >>= 1;
        }
        return res;
    }

    template <u32 P>
    constexpr u32 mul_mod (u32 a, u32 b) {
        return u64 (a) * b % P;
    }

    template <u64 P>
    constexpr u64 mul_mod (u64 a, u64 b) {
        u64 res = a * b - u64 (1.L * a * b / P - 0.5L) * P;
        res %= P;
        return res;
    }

    constexpr safe_mod (ll x, ll m) {
        x %= m;
        if (x < 0) x += m;
        return x;
    }

    template <unsigned_integral U, U P>
    class mod_int {
    public:
        U x;

        constexpr mod_int () : x (0) {}
        template <unsigned_integral T>
        constexpr mod_int (T _x) : x (_x % mod ()) {}
        template <signed_integral T>
        constexpr mod_int (T _x) {
            using S = make_signed_t <U>;
            S v = _x % S (mod ());
            if (v < 0) v += mod ();
            x = v;
        }

        constexpr static U mod () {
            return P;
        }

        constexpr U val () const {
            return x;
        }

        constexpr mod_int operator - () const {
            mod_int res;
            res.x = (x == 0 ? 0 : mod () - x);
            return res;
        }

        constexpr mod_int inv () const {
            return power (*this, mod () - 2);
        }

        constexpr mod_int &operator *= (const mod_int &rhs) & {
            x = mul_mod <mod ()> (x, rhs.val ());
            return *this;
        }

        constexpr mod_int &operator += (const mod_int &rhs) & {
            x += rhs.val ();
            if (x >= mod ()) x -= mod ();
            return *this;
        }

        constexpr mod_int &operator -= (const mod_int &rhs) & {
            x -= rhs.val ();
            if (x >= mod ()) x += mod ();
            return *this;
        }

        constexpr mod_int &operator /= (const mod_int &rhs) & {
            return *this *= rhs.inv ();
        }

        friend constexpr mod_int operator * (mod_int lhs, const mod_int &rhs) {
            lhs *= rhs;
            return lhs;
        }

        friend constexpr mod_int operator + (mod_int lhs, const mod_int &rhs) {
            lhs += rhs;
            return lhs;
        }

        friend constexpr mod_int operator - (mod_int lhs, const mod_int &rhs) {
            lhs -= rhs;
            return lhs;
        }

        friend constexpr mod_int operator / (mod_int lhs, const mod_int &rhs) {
            lhs /= rhs;
            return lhs;
        }

        friend constexpr istream &operator >> (istream &is, mod_int &a) {
            ll i;
            is >> i;
            a = i;
            return is;
        }

        friend constexpr ostream &operator << (ostream &os, const mod_int &a) {
            return os << a.val ();
        }

        friend constexpr bool operator == (const mod_int &lhs, const mod_int &rhs) {
            return lhs.val () == rhs.val ();
        }

        friend constexpr bool operator < (const mod_int &lhs, const mod_int &rhs) {
            return lhs.val () < rhs.val ();
        }

        friend constexpr bool operator <= (const mod_int &lhs, const mod_int &rhs) {
            return lhs.val () <= rhs.val ();
        }

        friend constexpr bool operator > (const mod_int &lhs, const mod_int &rhs) {
            return lhs.val () > rhs.val ();
        }

        friend constexpr bool operator >= (const mod_int &lhs, const mod_int &rhs) {
            return lhs.val () >= rhs.val ();
        }
    };

    template <u32 P>
    using mint = mod_int <u32, P>;
    template <u64 P>
    using mll = mod_int <u64, P>;
}
