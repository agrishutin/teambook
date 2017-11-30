void buildSuffixArray(int * src, int n, int * p)
{
    static int s[maxn], scale[maxn], cnt[maxn], color[maxn], start[maxn];
    static int pp[maxn], cc[maxn];
    memcpy(s, src, sizeof(int) * n);
    memcpy(scale, src, sizeof(int) * n);
    sort(scale, scale + n);
    
    int csz = int(unique(scale, scale+n) - scale);
    for (int i = 0; i < n; ++i)
        s[i] = int(lower_bound(scale, scale+csz, s[i]) - scale + 1);
    s[n++] = 0;
    csz++;
        
    memset(cnt, 0, sizeof cnt);
    for (int i = 0; i < n; ++i)
        cnt[s[i]]++;
    start[0] = 0;
    for (int i = 1; i < csz; ++i)
        start[i] = start[i-1] + cnt[i-1];
    for (int i = 0; i < n; ++i)
        p[start[s[i]]++] = i;
    color[p[0]] = 0;
    for (int i = 1; i < n; ++i)
        color[p[i]] = color[p[i-1]] + (s[p[i-1]] == s[p[i]] ? 0 : 1);
        
    for (int k = 1; k < n; k <<= 1)
    {
        memset(cnt, 0, sizeof(int) * n);
        for (int i = 0; i < n; ++i)
            cnt[color[i]]++;
        start[0] = 0;
        for (int i = 1; i < n; ++i)
            start[i] = start[i-1] + cnt[i-1];
            
        for (int i = 0; i < n; ++i)
            p[i] = (p[i]-k+n)%n;
        for (int i = 0; i < n; ++i)
            pp[start[color[p[i]]]++] = p[i];
        memcpy(p, pp, sizeof(int) * n);
        cc[p[0]] = 0;
        for (int i = 1; i < n; ++i)
            cc[p[i]] = cc[p[i-1]] + 
(color[p[i]] == color[p[i-1]] && color[(p[i]+k)%n] == color[(p[i-1]+k)%n] ? 0 : 1);
        memcpy(color, cc, sizeof(int) * n);
    }
    for (int i = 0; i+1 < n; ++i)
        p[i] = p[i+1];
}

void buildLcp(int * s, int * sa, int n, int * lcp)
{
    static int p[maxn];
    for (int i = 0; i < n; ++i)
        p[sa[i]] = i;
    for (int i = 0; i < n; ++i)
    {
        if (p[i]+1 == n)
            continue;
        int j = (i ? max(0, lcp[p[i-1]] - 1) : 0);
        while (sa[p[i]]+j < n 
            && sa[p[i]+1]+j < n 
            && s[sa[p[i]]+j] == s[sa[p[i]+1]+j])
            ++j;
        lcp[p[i]] = j;
    }
}
