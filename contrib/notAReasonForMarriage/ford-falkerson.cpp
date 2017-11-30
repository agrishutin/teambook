struct Edge {
    int to, f, c;
    Edge() {}
    Edge(int to, int f, int c)
        : to(to)
        , f(f)
        , c(c) {}
};

const int maxn;

vector<Edge> edgelist;
vector<vector<int>> edge;
int p[maxn], used[maxn];
int source, sink;
int bound, q = 0;

int dfs(int v, int w) {
    p[v] = w;
    used[v] = q;
    if (v == sink)
        return 1 << 30;
    for (size_t i = 0; i < edge[v].size(); ++i) {
        int e = edge[v][i];
        int u = edgelist[e].to;
        if (used[u] != q && edgelist[e].c - edgelist[e].f >= bound) {
            int d = dfs(u, e);
            if (d)
                return min(d, edgelist[e].c - edgelist[e].f);
        }
    }
    return 0;
}

foreach (a->b)
    edge[a - 1].push_back(edgelist.size());
edgelist.push_back(Edge(b - 1, 0, c));

int ans = 0;
p[source] = -1;
memset(used, -1, sizeof used);
q = -1;
for (bound = 1 << 30; bound > 0;) {
    ++q;
    int flow = dfs(source, -1);
    if (!flow) {
        bound >>= 1;
        continue;
    }
    ans += flow;
    for (int cur = p[sink]; cur != -1; cur = p[edgelist[cur ^ 1].to]) {
        edgelist[cur].f += flow;
        edgelist[cur ^ 1].f -= flow;
    }
}

// Another try:

nt to[maxe], cap[maxe], nxt[maxe];
int ecnt = 0;
int head[maxv];

inline void addEdge(int a, int b, int c) {
    nxt[ecnt] = head[a];
    to[ecnt] = b;
    cap[ecnt] = c;
    head[a] = ecnt++;
    nxt[ecnt] = head[b];
    to[ecnt] = a;
    cap[ecnt] = 0;
    head[b] = ecnt++;
}

int source, sink;
int used[maxv];
int qused = 1;

int dfs(int v, int maxf) {
    if (v == sink || !maxf)
        return maxf;
    used[v] = qused;
    for (int e = head[v]; e != -1; e = nxt[e]) {
        int u = to[e], c = min(cap[e], maxf);
        if (used[u] == qused || !c)
            continue;
        int f = dfs(u, c);
        if (f) {
            cap[e] -= f;
            cap[e ^ 1] += f;
            return f;
        }
    }
    return 0;
}

int maxFlow() {
    memset(used, 0, sizeof used);
    int ret = 0, d;
    while (d = dfs(source, 1 << 30)) {
        ret += d;
        ++qused;
    }
    return ret;
}
