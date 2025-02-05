class SPFA {
    public:
    vector <vector <pair <int, int>>> e;
    vector <int> dis, inq;

    void spfa (int x) {
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
    }

    SPFA () : e(vector (0, vector (0, pair (0, 0)))), dis(vector (0, 0)), inq(vector (0, 0)) {}
    SPFA (int n, const vector <vector <pair <int, int>>> &a) {e = a, dis = vector (n + 1, 0), inq = vector (n + 1, 0);}
};
