auto floyd = [&](const vector <vector <ll>> &e) -> vector <vector <ll>> {
	vector s = e;
	for (int k = 1; k <= n; k++) for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++) s[i][j] = min(e[i][j], s[i][k] + s[k][j]);
	return s;
};
