// Floyd
vector e(n + 1, vector (n + 1, inf));

void Floyd (int n) {
	for (int k = 1; k <= n; k++) for (int i = 1; i <= n; i++)
	for (int j = 1; j <= n; j++) e[i][j] = min(e[i][j], e[i][k] + e[k][j]);
}

// SPFA
vector e(n + 1, vector (pair (0, 0)));
vector dis(n + 1, 0), inq(n + 1, 0);

auto spfa = [&](int x) -> void {
	fill (all(dis), inf); dis[x] = 0;
	queue <int> q; q.push(x);

	while (q.size()) {
		inq[q.front()] = 0;
		auto u = q.front(); q.pop();
		for (auto &i : e[u]) if (dis[u] + i.second < dis[i.first]) {
			dis[i.first] = dis[u] + i.second;
			if (inq[i.first] == 0) inq[i.first] = 1, q.push(i.first);
		}
	}
};

// dijkstra
struct Node {int v, w;};
vector e(n + 1, vector (0, Node (0, 0)));
vector dis(n + 1, 0), vis(n + 1, 0);

auto dij = [&](int s) -> void {
	fill(all(dis), inf); dis[s] = 0;
	fill(all(vis), 0);
	priority_queue <pair <int, int>, vector <pair <int, int>>, greater <pair <int, int>>> pq;
	pq.push({0, s});
	while(pq.size()) {
		auto u = pq.top().second; pq.pop();
		if (vis[u]) continue; vis[u] = 1;
		for (auto &i : e[u]) if (dis[u] + i.w < dis[i.v]) {
			dis[i.v] = dis[u] + i.w;
			pq.push({dis[i.v], i.v});
		}
	}
};