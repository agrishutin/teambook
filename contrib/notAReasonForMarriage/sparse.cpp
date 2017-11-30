struct Sparse {
    static const int logn = 18;
    T st[logn][maxn];
    int log2[maxn];
    Sparse() {}
    Sparse(T* src, int n) { build(src, n); }
    void build(T* src, int n) {
        log2[1] = 0;
        for (int i = 2; i <= n; ++i)
            log2[i] = log2[i - 1] + ((2 << log2[i - 1]) < i ? 1 : 0);
        memcpy(st[0], src, sizeof(T) * n);
        for (int i = 1; i < logn; ++i)
            for (int j = 0; j < n; ++j)
                st[i][j] = getmin(j, min(j + (1 << i) - 1, n - 1));
    }
    inline int getmin(int l, int r) {
        int p = log2[r - l + 1];
        return min(st[p][l], st[p][r - (1 << p) + 1]);
    }
};
