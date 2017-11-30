// минимум на пути через lca на двоичных подъёмах

inline bool ancestor(int a, int b) {
    return in[b] >= in[a] && in[b] <= out[a];
}

int climb(int to, int v) {
    int ans = 1 << 30;
    for (int i = maxk-1; v != to;)
        if (ancestor(to, p[i][v]))
        {
            ans = min(ans, w[i][v]);
            v = p[i][v];
        }
        else
            --i;
    return ans;
}

int getans(int a, int b) {
    if (ancestor(a, b))
        return climb(a, b); // lca=a
    if (ancestor(b, a))
        return climb(b, a); // lca=b
    int lca = a;
    for (int i = maxk-1; !ancestor(p[0][lca], b); )
        if (ancestor(p[i][lca], b))
            --i;
        else
            lca = p[i][lca];
    lca = p[0][lca];
    return min(climb(lca, a), climb(lca, b));
}
