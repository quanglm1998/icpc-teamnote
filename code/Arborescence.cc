namespace Arborescence {
    const int maxv = 2550;
    const int maxe = maxv * maxv;
    const long long INF = (long long) 1e18;

    struct edge_t {
        int u, v;
        long long w;
        edge_t(int u = 0, int v = 0, long long w = 0) : u(u), v(v), w(w) {}
    } edge[maxe];

    int ec;
    int id[maxv], pre[maxv];
    long long in[maxv];
    int vis[maxv];

    void init() {
        ec = 0;
    }

    void add(int u, int v, int w) {
        // 1-indexed
        edge[++ec] = edge_t(u, v, w);
    }

    long long mst(int n, int rt) {
        long long res = 0;
        int idx;
        while (1) {
            for (int i = 1; i <= n; i++) {
                in[i] = INF, vis[i] = -1, id[i] = -1;
            }
            for (int i = 1; i <= ec; i++) {
                int u = edge[i].u, v = edge[i].v;
                if (u == v || in[v] <= edge[i].w) continue;
                in[v] = edge[i].w, pre[v] = u;
            }
            pre[rt] = rt, in[rt] = 0;
            for (int i = 1; i <= n; i++) {
                res += in[i];
                if (in[i] == INF) return -1;
            }

            idx = 0;
            for (int i = 1; i <= n; i++) {
                if (vis[i] != -1) continue;
                int u = i, v;
                while (vis[u] == -1) {
                    vis[u] = i;
                    u = pre[u];
                }
                if (vis[u] != i || u == rt) continue;
                for (v = u, u = pre[u], idx++; u != v; u = pre[u]) id[u] = idx;
                id[v] = idx;
            }
            if (idx == 0) return res;
            for (int i = 1; i <= n; i++) if (id[i] == -1) id[i] = ++idx;
            for (int i = 1; i <= ec; i++) {
                int u = edge[i].u, v = edge[i].v;
                edge[i].u = id[u], edge[i].v = id[v];
                edge[i].w -= in[v];
            }
            n = idx, rt = id[rt];
        }
        return res;
    }
}
