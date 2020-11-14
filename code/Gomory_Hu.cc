// a weighted tree that represents the minimum s-t cuts for all s-t pairs in the graph
vector<pair<pair<int, int>, flow_t> > gomory_hu() {
    vector<pair<pair<int, int>, flow_t> > tree;
    vector<int> p(n);
    for (int u = 1; u < n; u++) {
        tree.push_back(make_pair(make_pair(p[u], u), maxflow(u, p[u])));
        for (int v = u + 1; v < n; ++v) {
            if (lev[v] && p[v] == p[u]) {
                p[v] = u;
            }
        }
    }
    return tree;
}