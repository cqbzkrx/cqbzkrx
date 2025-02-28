void gauss (int n, vector <vector <db>> &a) {
    for (int i = 0; i < n; i++) {
        int maxi = i;
        for (int j = 0; j < n; j++) {
            if (j < i && fabs (a[j][j]) > eps) continue;
            if (fabs (a[j][i]) > fabs (a[maxi][i])) maxi = j;
        }

        for (int j = 0; j <= n; j++) swap (a[i][j], a[maxi][j]);
        if (fabs (a[i][i]) < eps) continue;

        for (int j = 0; j < n; j++) {
            if (i == j) continue;
            db v = a[j][i] / a[i][i];
            for (int k = i; k <= n; k++) a[j][k] -= v * a[i][k];
        }
    }

    for (int i = 0; i < n; i++) {
        if (fabs (a[i][i]) < eps) continue;
        a[i][n] /= a[i][i];
        a[i][i] = 1.0;
    }
}
