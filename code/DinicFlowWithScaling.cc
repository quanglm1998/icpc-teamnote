/*
    U = max capacity
    Complexity: O(V * E * log(U))
    O(min(E^{1/2}, V^{2/3}) * E) if U = 1
    O(V^{1/2} * E)$ for bipartite matching.
    Tested: https://vn.spoj.com/problems/FFLOW/
    --> CHANGE LIM TO MAX CAPACITY<--
*/
template <typename flow_t = int>
struct DinicFlow {
    const flow_t INF = numeric_limits<flow_t>::max() / 2; // 1e9
 
    int n, s, t;
    vector<vector<int>> adj;
    vector<int> d, cur;
    vector<int> to;
    vector<flow_t> c, f;
 
    DinicFlow(int n, int s, int t) : n(n), s(s), t(t), adj(n, vector<int>()), d(n, -1), cur(n, 0) {}
 
    int addEdge(int u, int v, flow_t _c) {
        adj[u].push_back(to.size()); 
        to.push_back(v); f.push_back(0); c.push_back(_c);
        adj[v].push_back(to.size());
        to.push_back(u); f.push_back(0); c.push_back(0);
        return (int)to.size() - 2;
    }
 
    bool bfs(flow_t lim) {
        fill(d.begin(), d.end(), -1);
        d[s] = 0;
        queue<int> q;
        q.push(s);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (auto edgeId : adj[u]) {
                int v = to[edgeId];
                if (d[v] == -1 && lim <= c[edgeId] - f[edgeId]) {
                    d[v] = d[u] + 1;
                    if (v == t) return 1;
                    q.push(v);
                }
            }
        }
        return d[t] != -1;
    }
 
    flow_t dfs(int u, flow_t res) {
        if (u == t || !res) return res;
        for (int &i = cur[u]; i < adj[u].size(); i++) {
            int edgeId = adj[u][i];
            int v = to[edgeId];
            if (d[v] == d[u] + 1 && res <= c[edgeId] - f[edgeId]) {
                flow_t foo = dfs(v, res);
                if (foo) {
                    f[edgeId] += foo;
                    f[edgeId ^ 1] -= foo;
                    return foo;
                }
            }
        }
        return 0;
    }
 
    flow_t maxFlow() {
        flow_t res = 0;
        flow_t lim = (flow_t)1 << int(round(log2(INF))); // change this to max capacity
        while (lim >= 1) {
            if (!bfs(lim)) {
                lim >>= 1;
                continue;
            }
            fill(cur.begin(), cur.end(), 0);
            while (flow_t aug = dfs(s, lim)) res += aug;
        }
        return res;
    }
};

