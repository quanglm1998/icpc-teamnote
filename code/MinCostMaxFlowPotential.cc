/*
    Complexity: O(VE * ElogN + VE)
    O(VE) phases, O(ElogN) for Dijkstra, O(VE) for the initial SPFA
    Tested: https://open.kattis.com/problems/mincostmaxflow
            https://codeforces.com/problemset/problem/164/C (92ms vs 936ms)

    --> RUN INIT BEFORE MAXFLOW IF WE HAVE NEG-EDGES <--
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

    vector<cost_t> pot;
    vector<cost_t> d;
    vector<int> prev;
    vector<bool> used;
 
    MinCostMaxFlow(int n, int s, int t) : n(n), s(s), t(t), adj(n, vector<int>()), d(n, -1), prev(n, -1), pot(n, 0), used(n, 0) {}
 
    int addEdge(int u, int v, flow_t _c, cost_t _cost) {
        adj[u].push_back(to.size()); 
        to.push_back(v); f.push_back(0); c.push_back(_c); cost.push_back(_cost);
        adj[v].push_back(to.size());
        to.push_back(u); f.push_back(0); c.push_back(0); cost.push_back(-_cost);
        return (int)to.size() - 2;
    }

    bool dijkstra() {
        fill(prev.begin(), prev.end(), -1);
        fill(d.begin(), d.end(), COST_INF);
        fill(used.begin(), used.end(), 0);
        d[s] = 0;
        set<pair<cost_t, int>> ss;
        ss.insert({0, s});
        while (!ss.empty()) {
            int u = ss.begin()->second; ss.erase(ss.begin());
            if (used[u]) continue;
            used[u] = 1;
            for (int id : adj[u]) {
                int v = to[id];
                cost_t now = d[u] + pot[u] - pot[v] + cost[id];
                if (!used[v] && d[v] > now && f[id] < c[id]) {
                    d[v] = now;
                    prev[v] = id;
                    ss.insert({d[v], v});
                }
            }
        }
        for (int i = 0; i < n; i++) pot[i] += d[i];
        return prev[t] != -1;
    }
 
    pair<flow_t, cost_t> maxFlow() {
        flow_t res = 0;
        cost_t minCost = 0;
        while (dijkstra()) {
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

    void init() {
        fill(pot.begin(), pot.end(), COST_INF);
        pot[s] = 0;
        bool changed = 1;
        while (changed) { // be careful for NEG cycle
            changed = 0;
            for (int i = 0; i < n; i++) if (pot[i] < COST_INF) {
                for (int id : adj[i]) {
                    int v = to[id];
                    if (pot[v] > pot[i] + cost[id] && f[id] < c[id]) {
                        pot[v] = pot[i] + cost[id];
                        changed = 1;
                    }
                }
            }
        }
    }
};