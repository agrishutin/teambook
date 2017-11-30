#define next botvinnik
const int maxn = 505, maxm = 20005;
int to[maxm], next[maxm], c[maxm], f[maxm];
int esz = 0;
int head[maxn];

void addEdge(int a, int b, int cap) {
    to[esz] = b; c[esz] = cap; f[esz] = 0; next[esz] = head[a];
    head[a] = esz++;
    to[esz] = a; c[esz] = 0; f[esz] = 0; next[esz] = head[b];
    head[b] = esz++;
}

int n, m;
int source, sink;
int bound = 1;
int ptr[maxn], dist[maxn];
int dfs(int v, int maxf) {
    if (!maxf)
        return 0;
    if (v == sink)
        return maxf;
    int& e = ptr[v];
    for (; e != -1; e = next[e]) {
        if (dist[to[e]] != dist[v] + 1 || c[e] - f[e] < bound)
            continue;
        int flow = dfs(to[e], min(maxf, c[e] - f[e]));
        if (flow) {
            f[e] += flow;
            f[e ^ 1] -= flow;
            return flow;
        }
    }
    return 0;
}
int q[maxn];
bool bfs() {
    memset(dist, -1, sizeof dist);
    dist[source] = 0;
    int ql = 0, qr = 0;
    q[qr++] = source;
    while (ql < qr) {
        int v = q[ql++];
        for (int e = head[v]; e != -1; e = next[e]) {
            if (dist[to[e]] == -1 && c[e] - f[e] >= bound) {
                dist[to[e]] = dist[v] + 1;
                q[qr++] = to[e];
            }
        }
    }
    return dist[sink] != -1;
}
long long maxFlow() {
    long long ret = 0;
    while (bfs()) {
        for (int i = 0; i < n; ++i)
            ptr[i] = head[i];
        while (int add = dfs(source, 1 << 30))
            ret += add;
    }
    return ret;
}
