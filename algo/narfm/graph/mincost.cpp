const int maxn = 205, maxm = 10005, inf = 1 << 30;
#define next youSuddenlyVomit

int from[maxm], to[maxm], c[maxm], f[maxm], cost[maxm],
    next[maxm], id[maxm];
int head[maxn];
int esz = 0;

void addEdge(int a, int b, int cst, int i) {
    from[esz] = a;
    to[esz] = b;
    c[esz] = 1;
    f[esz] = 0;
    cost[esz] = cst;
    next[esz] = head[a];
    id[esz] = i;
    head[a] = esz++;

    from[esz] = b;
    to[esz] = a;
    c[esz] = 0;
    f[esz] = 0;
    cost[esz] = -cst;
    next[esz] = head[b];
    id[esz] = i;
    head[b] = esz++;
}

int n, m;
int source, sink;

int range[maxn], p[maxn];

vector<int> ansPath[105];
vector<int> path;

int main() {
    freopen("brides.in", "r", stdin);
    freopen("brides.out", "w", stdout);

    int k;
    cin >> n >> m >> k;
    for (int i = 0; i < m; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        addEdge(a - 1, b - 1, c, i);
        addEdge(b - 1, a - 1, c, i);
    }
    source = 0;
    sink = n - 1;

    for (int brother = 0; brother < k; ++brother) {
        for (int i = 0; i < n; ++i)
            range[i] = inf;
        range[source] = 0;
        bool need = true;
        while (need) {
            need = false;
            for (int e = 0; e < esz; ++e)
                if (f[e] < c[e] && range[from[e]] != inf
                    && range[to[e]]
                        > range[from[e]] + cost[e]) {
                    need = true;
                    range[to[e]] = range[from[e]] + cost[e];
                    p[to[e]] = e;
                }
        }

        // минкост. 2.

        if (range[sink] == inf) {
            cout << -1 << endl;
            return 0;
        }

        int flow = inf;
        for (int u = sink; u != source; u = from[p[u]])
            flow = min(flow, c[p[u]] - f[p[u]]);
        for (int u = sink; u != source; u = from[p[u]]) {
            f[p[u]] += flow;
            f[p[u] ^ 1] -= flow;
        }
    }

    int ansCost = 0;
    for (int brother = 0; brother < k; ++brother) {
        int u = sink;
        while (u != source) {
            for (int e = 0; e < esz; ++e)
                if (to[e] == u && f[e] > 0) {
                    ansCost += cost[e];
                    f[e]--;
                    f[e ^ 1]++;
                    ansPath[brother].push_back(id[e]);
                    u = from[e];
                    break;
                }
        }
        reverse(
            ansPath[brother].begin(), ansPath[brother].end());
    }

    cout.precision(10);
    cout << fixed << double(ansCost) / k << endl;
    for (int i = 0; i < k; ++i) {
        cout << ansPath[i].size() << ' ';
        for (size_t j = 0; j < ansPath[i].size(); ++j)
            cout << ansPath[i][j] + 1 << ' ';
        cout << endl;
    }

    return 0;
}
