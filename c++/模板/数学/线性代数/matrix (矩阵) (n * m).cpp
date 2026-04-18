template <int n, int m, typename T = int>
struct matrix {
public:
    vector <vector <T>> val;

    matrix (T x = 0) {
        val.assign (n, vector <T> (m, 0));
        for (int i = 0; i < n; i++) for (int j = 0; j < m; j++)
            val[i][j] = (i == j ? x : 0);
    }

    matrix (const vector <vector <T>> &a) {
        val.assign (n, vector <T> (m, 0));
        for (int i = 0; i < n; i++) for (int j = 0; j < m; j++)
            val[i][j] = a[i][j];
    }

    inline vector <T> & operator [] (int i) {return val[i];}
    inline const vector <T> & operator [] (int i) const {return val[i];}
    inline T & operator () (int i, int j) {return val[i][j];}
    inline const T & operator () (int i, int j) const {return val[i][j];}
    inline T & at (int i, int j) {return val[i][j];}

    matrix <n, m, T> & operator += (const matrix <n, m, T> &rhs) & {
        for (int i = 0; i < n; i++) for (int j = 0; j < m; j++)
            *this[i][j] += rhs[i][j];
        return *this;
    }

    friend matrix <n, m, T> operator + (matrix <n, m, T> lhs, const matrix <n, m, T> &rhs) {
        lhs += rhs;
        return lhs;
    }

    template <int k>
    friend matrix <n, k, T> operator * (const matrix <n, m, T> &lhs, const matrix <m, k, T> &rhs) {
        matrix <n, k, T> ans;
        for (int i = 0; i < n; i++) for (int j = 0; j < k; j++) {
            ans[i][j] = 0;
            for (int x = 0; x < m; x++) ans[i][j] += lhs[i][x] * rhs[x][j];
        }
        return ans;
    }
};
