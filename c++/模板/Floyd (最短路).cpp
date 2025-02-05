vector e(n + 1, vector (n + 1, inf));

void Floyd (int n) {
	for (int k = 1; k <= n; k++) for (int i = 1; i <= n; i++)
	for (int j = 1; j <= n; j++) e[i][j] = min(e[i][j], e[i][k] + e[k][j]);
}
