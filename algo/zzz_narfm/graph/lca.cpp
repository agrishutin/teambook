// минимум на пути через lca на двоичных подъёмах

inline bool ancestor(int a, int b) {
    return in[b] >= in[a] && in[b] <= out[a];
}

int climb(int to, int v) {
    int ans = 1 << 30;
    for (int i = maxk - 1; v != to;)
        if (ancestor(to, p[i][v])) {
            ans = min(ans, w[i][v]);
            v = p[i][v];
        } else
            --i;
    return ans;
}

int getans(int a, int b) {
    if (ancestor(a, b))
        return climb(a, b); // lca=a
    if (ancestor(b, a))
        return climb(b, a); // lca=b
    int lca = a;
    for (int i = maxk - 1; !ancestor(p[0][lca], b);)
        if (ancestor(p[i][lca], b))
            --i;
        else
            lca = p[i][lca];
    lca = p[0][lca];
    return min(climb(lca, a), climb(lca, b));
}

// через RMQ

pair<int, int> euler[maxn * 2];
int fst[maxn];
int psz = 0;
int lca(int a, int b) {
    if (fst[a] > fst[b])
        swap(a, b);
    pair<int, int> m = getMin(fst[a], fst[b]);
    return m.second;
}

vector<int> edge[maxn];
void dfs(int v, int h) {
    fst[v] = psz;
    euler[psz++] = make_pair(h, v);
    for (size_t i = 0; i < edge[v].size(); ++i) {
        dfs(edge[v][i], h + 1);
        euler[psz++] = make_pair(h, v);
    }
}
