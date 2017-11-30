int gauss(vector<vector<ld>> v, vector<ld>& ret) {
    int n = v.size();
    int m = n;
    vector<int> p(m), dist(m, 0);
    for (int i = 0; i < m; ++i)
        p[i] = i;
    for (int row = 0, col = 0; row < n && col < m; ++col) {
        int sr = row, sc = col;
        for (int i = row; i < n; ++i)
            for (int j = col; j < m; ++j) {
                if (abs(v[i][j]) > abs(v[sr][sc])) {
                    sr = i;
                    sc = j;
                }
            }
        if (abs(v[sr][sc]) < eps)
            break;
        swap(v[row], v[sr]);
        for (int i = 0; i < n; ++i)
            swap(v[i][col], v[i][sc]);
        swap(p[col], p[sc]);
        dist[col] = 1;
        for (int i = 0; i < n; ++i)
            if (i != row) {
                ld c = v[i][col] / v[row][col];
                for (int j = col; j <= m; ++j)
                    v[i][j] -= v[row][j] * c;
            }
        ++row;
    }
    ret.assign(m, 0);
    for (int i = 0; i < m; ++i)
        if (dist[p[i]])
            ret[i] = v[p[i]][m] / v[p[i]][p[i]];
    for (int i = 0; i < m; ++i) {
        ld sum = 0;
        for (int j = 0; j < m; ++j)
            sum += ret[j] * v[i][p[j]];
        if (abs(sum - v[i][m]) > eps)
            return 0;
    }
    for (int i = 0; i < m; ++i)
        if (!dist[i])
            return -1;
    return 1;
}
