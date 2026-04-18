template <int n, typename T = int>
struct matrix {
public:
    vector <vector <T>> val;

    matrix (T x = 0) {
        val.assign (n, vector <T> (n, 0));
        for (int i = 0; i < n; i++) for (int j = 0; j < n; j++)
            val[i][j] = (i == j ? x : 0);
    }

    matrix (const vector <vector <T>> &a) {
        val.assign (n, vector <T> (n, 0));
        for (int i = 0; i < n; i++) for (int j = 0; j < n; j++)
            val[i][j] = a[i][j];
    }

    inline vector <T> & operator [] (int i) {return val[i];}
    inline const vector <T> & operator [] (int i) const {return val[i];}
    inline T & operator () (int i, int j) {return val[i][j];}
    inline const T & operator () (int i, int j) const {return val[i][j];}
    inline T & at (int i, int j) {return val[i][j];}

    matrix <n, T> & operator += (const matrix <n, T> &rhs) & {
        for (int i = 0; i < n; i++) for (int j = 0; j < n; j++)
            *this[i][j] += rhs[i][j];
        return *this;
    }

    friend matrix <n, T> operator + (matrix <n, T> lhs, const matrix <n, T> &rhs) {
        lhs += rhs;
        return lhs;
    }

    friend matrix <n, T> operator * (const matrix <n, T> &lhs, const matrix <n, T> &rhs) {
        matrix <n, T> ans;
        for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) {
            ans[i][j] = 0;
            for (int x = 0; x < n; x++) ans[i][j] += lhs[i][x] * rhs[x][j];
        }
        return ans;
    }

    matrix <n, T> & operator *= (const matrix <n, T> &rhs) & {
        *this = *this * rhs;
        return *this;
    }
};
