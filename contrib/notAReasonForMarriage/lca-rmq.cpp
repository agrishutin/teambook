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
