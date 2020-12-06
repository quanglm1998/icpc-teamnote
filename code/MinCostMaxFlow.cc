
/*
    Complexity: O(V^2 * E^2)
    O(VE) phases, O(VE) for SPFA
    Tested: https://open.kattis.com/problems/mincostmaxflow
*/
template <typename flow_t = int, typename cost_t = int>
struct MinCostMaxFlow {
    const flow_t FLOW_INF = numeric_limits<flow_t>::max() / 2; // 1e9
    const cost_t COST_INF = numeric_limits<cost_t>::max() / 2; // 1e9
 
    int n, s, t;
    vector<vector<int>> adj;
    vector<int> to;
    vector<flow_t> f, c;
    vector<cost_t> cost;
 
    vector<cost_t> d;
    vector<bool> inQueue;
    vector<int> prev;
 
    MinCostMaxFlow(int n, int s, int t) : n(n), s(s), t(t), adj(n, vector<int>()), d(n, -1), inQueue(n, 0), prev(n, -1) {}
 
    int addEdge(int u, int v, flow_t _c, cost_t _cost) {
        adj[u].push_back(to.size()); 
        to.push_back(v); f.push_back(0); c.push_back(_c); cost.push_back(_cost);
        adj[v].push_back(to.size());
        to.push_back(u); f.push_back(0); c.push_back(0); cost.push_back(-_cost);
        return (int)to.size() - 2;
    }
 
    pair<flow_t, cost_t> maxFlow() {
        flow_t res = 0;
        cost_t minCost = 0;
        while (1) {
            fill(prev.begin(), prev.end(), -1);
            fill(d.begin(), d.end(), COST_INF);
            d[s] = 0;
            inQueue[s] = 1;
            queue<int> q;
            q.push(s);
            while (!q.empty()) {
                int u = q.front();
                q.pop();
                inQueue[u] = 0;
                for (int id : adj[u]) {
                    int v = to[id];
                    if (d[v] > d[u] + cost[id] && f[id] < c[id]) {
                        d[v] = d[u] + cost[id];
                        prev[v] = id;
                        if (!inQueue[v]) {
                            inQueue[v] = 1;
                            q.push(v);
                        }
                    }
                }
            }
            if (prev[t] == -1) break;
            int x = t;
            flow_t now = FLOW_INF;
            while (x != s) {
                int id = prev[x];
                now = min(now, c[id] - f[id]);
                x = to[id ^ 1];
            }
            x = t;
            while (x != s) {
                int id = prev[x];
                minCost += cost[id] * now;
                f[id] += now;
                f[id ^ 1] -= now;
                x = to[id ^ 1];
            }
            res += now;
        }
        return {res, minCost};
    }
};