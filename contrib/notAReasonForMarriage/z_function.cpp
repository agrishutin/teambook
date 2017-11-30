int z[maxn];
void getZ(const string& s) {
        int n = s.size();
        int l, r;
        l = r = 0;
        for (int i = 1; i < n; ++i)
    {
                z[i] = 0;
                if (i < r)
            z[i] = min(r - i, z[i - l]);
                while (i + z[i] < n && s[i + z[i]] == s[z[i]])
            z[i]++;
                if (i + z[i] > r)
        {
                        l = i;
                        r = i + z[i];
                    
        }
            
    }
        z[0] = n;
}
