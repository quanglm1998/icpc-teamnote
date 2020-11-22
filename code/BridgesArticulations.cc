void dfs(int u, int p) {
    num[u] = low[u] = ++cnt;
    st.push_back(u);
    for (auto v : adj[u]) {
        if (!num[v]) {
            if (u == 1) nChild++; // root = 1
            dfs(v, u);
            if (low[v] >= num[u]) { // u is articulation point, EXCEPT for 1
                isArticulation[u] = 1;
                numComp++;
                while (!st.empty()) {
                    int x = st.back();
                    st.pop_back();
                    ls[numComp].push_back(x);
                    if (x == v) break;
                }
                ls[numComp].push_back(u);
            }
            if (low[v] > num[u]) { // u - v bridge
                nBridge++;
            }
            low[u] = min(low[u], low[v]);
        } else if (v != p) {
            low[u] = min(low[u], num[v]);
        }
    }
}
if (nChild <= 1) isArticulation[1] = 0;