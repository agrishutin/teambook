bool dfs(int v) {
    if (vis[v]) return false;
    vis[v] = true;
    for (int i = 0; i < (int)e[v].size(); i++) {
        if (mt[e[v][i]] == -1) {
            mt[e[v][i]] = v;
            return true;
        }
    }
    for (int i = 0; i < (int)e[v].size(); i++) {
        if (dfs(mt[e[v][i]])) {
            mt[e[v][i]] = v;
            return true;
        }
    }
    return false;
}

...

fill(pair, -1);
for (int run = 1; run; ) {
  run = 0, fill(used, 0);
  forn(i, n)
    if (pair[i] == -1 && dfs(i))
      run = 1;
}